#include "stdafx.h"
#include "Application.h"
#include "Layer/LayerStack.h"
#include "Layer/Layer.h"
#include "Layer/UiLayer.h"
#include "Layer/RenderLayer.h"
#include "Event/Event.h"
#include "Window/Window.h"
#include "Event/ApplicationEvent.h"

Application* Application::s_instance = nullptr;


double Application::_fps = 0.0;

class Application::ApplicationPrivate
{
	SELF(ApplicationPrivate);
public:


	Application* _self;
	LayerStack   _layerStack;
	UiLayer*     _uiLayer;

	bool _running;
	bool _isMinimized;

	double _lastFrameTime;

	Window* _window;


	ApplicationPrivate(Application* self);
	~ApplicationPrivate();

	void pushLayer(Layer* layer);
	void run();
	void onEvent(Event& e);
	void addGuiLayer(UiLayer* layer);
	void registerWindow(Window* window);
	bool onWindowClose(WindowCloseEvent& event);

	GLFWwindow* windowHandle() const;
};

Application::ApplicationPrivate::ApplicationPrivate(Application* self)
	:_self(self)
{
	_running = true;
	_isMinimized = false;
	_lastFrameTime = 0.0;

}

Application::ApplicationPrivate::~ApplicationPrivate()
{
	if (_uiLayer)
	{
		_uiLayer->onDetach();
		delete _uiLayer;
		_uiLayer = nullptr;
	}

	if (_window)
	{
		delete _window;
		_window = nullptr;
	}

	if (_self)
	{
		delete _self;
		_self = nullptr;
	}
}

void Application::ApplicationPrivate::pushLayer(Layer* layer)
{
	_layerStack.pushLayer(layer);
	layer->onAttach();
}

void Application::ApplicationPrivate::run()
{
	double time = 0.0;
	double timestep = 0.0;

	while (_running)
	{
		if (_isMinimized)
		{
			continue;
		}

		static int frameCount = 0;

	    // 计算帧率
		// _lastFrameTime = glfwGetTime();

		
		time = glfwGetTime();
		timestep = time - _lastFrameTime;
		_lastFrameTime = time;

#if 0
		if (timestep > 0.25)
		{
			_fps = (double)frameCount / timestep;
			frameCount = 0;
		}
#endif
		glClearColor(0.f, 0.f, 0.f, 1.0f);

		for (Layer* layer : _layerStack)
		{
			layer->onUpdate(timestep);
		}

		_uiLayer->begin();
		_uiLayer->onUpdate(timestep);
		_uiLayer->end();

		_window->onUpdate();

		// 事件循环
		glfwPollEvents();

		frameCount++;
	}
}

void Application::ApplicationPrivate::onEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::ApplicationPrivate::onWindowClose, this, std::placeholders::_1));


	for (auto iter = _layerStack.end(); iter != _layerStack.begin(); )
	{
		(*--iter)->onEvent(e);
		if (e.handled())
		{
			break;
		}
	}
}

void Application::ApplicationPrivate::addGuiLayer(UiLayer* layer)
{
	_uiLayer = layer;
	_uiLayer->onAttach();
}

void Application::ApplicationPrivate::registerWindow(Window* window)
{
	_window = window;
	_window->setEventCallback(std::bind(&Application::ApplicationPrivate::onEvent, this, std::placeholders::_1));
}

bool Application::ApplicationPrivate::onWindowClose(WindowCloseEvent& event)
{
	_running = false;
	return true;
}

GLFWwindow* Application::ApplicationPrivate::windowHandle() const
{
	return _window->windowHandle();
}

void Application::addGuiLayer(UiLayer* layer)
{
	pImpl->addGuiLayer(layer);
}

void Application::addLayer(Layer* layer)
{
	pImpl->pushLayer(layer);
}

void Application::registerWindow(Window* window)
{
	pImpl->registerWindow(window);
}

const std::string& Application::applicationDir()
{
	long ret = 0;
	// 获取程序根目录
	static CHAR exePathBuf[MAX_PATH];
	ret = ::GetModuleFileNameA(NULL, exePathBuf, MAX_PATH);
	if (ret == 0)
	{
		APP_ERROR("Fail to get application root directory");
		return std::string();
	}

	std::string exePath(exePathBuf);
	static std::string appDir = exePath.substr(0, exePath.find_last_of('\\'));
	return appDir;
}

const std::string& Application::textureDir()
{
	static std::string texturePath = Self::applicationDir() + "\\Asset\\Texture\\";
	return texturePath;
}

const std::string& Application::assetDir()
{
	static std::string assetDir = Self::applicationDir() + std::string("\\Asset");
	return assetDir;
}

Application::Application()
	: pImpl(new ApplicationPrivate(this))
{
}

Application::~Application()
{
	if (pImpl)
	{
		delete pImpl;
		pImpl = nullptr;
	}
}

void Application::pushLayer(Layer* layer)
{
	pImpl->pushLayer(layer);
}

void Application::run()
{
	pImpl->run();
}

void Application::onEvent(Event& e)
{
	pImpl->onEvent(e);
}

GLFWwindow* Application::windowHandle() const
{
	return pImpl->windowHandle();
}

Window* Application::window() const
{
	return pImpl->_window;
}

double Application::fps() const
{
	return _fps;
}

