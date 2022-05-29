#include "stdafx.h"
#include "Window.h"
#include "Fundation/Log/Log.h"
#include "Application/Context/OpenGLContext.h"
#include "Application/Event/ApplicationEvent.h"
#include "Application/Event/MouseEvent.h"

namespace Diff
{
	namespace SD
	{
		class A {};
	}
}


class Window::WindowCallback
{
public:
	static void glfwErrorCallback(int errorCode, const char* errorMsg)
	{
		CORE_ERROR("{0}, Error code = {1}", errorMsg, errorCode);
	}
};

Window::Window()
{
	glfwSetErrorCallback(WindowCallback::glfwErrorCallback);
	int ret = 0;

	ret = glfwInit();
	if (ret != GLFW_TRUE)
	{
		APP_ERROR("Fail to initialize GLFW");
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_primaryMonitor = glfwGetPrimaryMonitor();
	if (_primaryMonitor == nullptr)
	{
		APP_ERROR("Fail to get primary monitor information");
		return;
	}

	_videoModes = glfwGetVideoModes(_primaryMonitor, &_videoModeCount);
	if (_videoModeCount == 0 || _videoModes == nullptr)
	{
		APP_ERROR("Fail to get video modes information");
		return;
	}


	Config::get().setVideoModes(_videoModes, _videoModeCount);

	Self::setDefaultVideoMode();

	_window = glfwCreateWindow(_currentWindowWidth, _currentWindowHeight, "The Render", nullptr, nullptr);
	if (_window == nullptr)
	{
		APP_ERROR("Fail to create the window.");
		return ;
	}


	glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		});


	_context = new OpenGLContext(_window);
	_context->init();


	setAntiAliasing(16);
}

Window::~Window()
{
	delete _context;
}

void Window::setAntiAliasing(int level)
{
	glfwWindowHint(GLFW_SAMPLES, level);
}

void Window::setFullScreen(bool enable)
{
	_fullScreenMode = enable;
}

void Window::shutdown()
{
	if (_window)
	{
	    glfwDestroyWindow(_window);
	}
}

void Window::onUpdate()
{
	
#if 0
	int display_w, display_h;
	glfwGetFramebufferSize(Self::windowHandle(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	//glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
#endif

	_context->swapBuffers();

	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

GLFWwindow* Window::windowHandle() const
{
	return _window;
}

int Window::width() const
{
	return _currentWindowWidth;
}

int Window::height() const
{
	return _currentWindowHeight;
}

void Window::setEventCallback(std::function<void(Event&)> func)
{
	_windowData._callback = func;
	glfwSetWindowUserPointer(_window, &_windowData);

	glfwSetWindowCloseCallback(_window, [](GLFWwindow* window) {
		WindowData* windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		WindowCloseEvent e;
		windowData->_callback(e);
	});

	glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods) {
		WindowData* windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);


		switch (action)
		{
			case GLFW_PRESS:
			{
				MousePressEvent e(button, PointD(xPos, yPos));
				windowData->_callback(e);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseReleaseEvent e(button, PointD(xPos, yPos));
				windowData->_callback(e);
				break;
			}
		}
	});

	glfwSetScrollCallback(_window, [](GLFWwindow* window, double xOffset, double yOffset) {
		WindowData* windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		MouseScrollEvent e(xOffset, yOffset);
		windowData->_callback(e);
	});

	glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double x, double y) {
		WindowData* windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		MouseMoveEvent e(x, y);
		int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		if (state == GLFW_PRESS)
		{
		    e.addKeyPressed(MouseCode::ButtonLeft);
		}

		state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
		if (state == GLFW_PRESS)
		{
			e.addKeyPressed(MouseCode::ButtonRight);
		}

		windowData->_callback(e);
	});
}

Rect<int> Window::viewportRect()
{
	int viewport[4] = { 0 };
	glGetIntegerv(GL_VIEWPORT, (GLint*)viewport);
	return Rect<int>(viewport);
}

Point3D<float> Window::windowCoordToNormDevCoord(const Point3D<float>& p) 
{
	Point3D<float> a;
	Rect<int> rect = Self::viewportRect();

	a[0] = (p.x() - (float)rect.x()) / ((float)rect.w() / 2.f) - 1;
	a[1] = (p.y() - (float)rect.y()) / ((float)rect.h() / 2.f) - 1.f;
	a[2] = (2.f * p.z() - 2.f);

	return a;
}

Line3<float> Window::viewLineFromWindow(const Point3D<float>& p)
{
	return Line3<float>();
}

Point3D<float> Window::viewPoint()
{
	return Point3D<float>();
}

void Window::setDefaultVideoMode()
{
	int defaultVideoMode = Config::get().defaultVideoMode();

	_currentWindowWidth = _videoModes[defaultVideoMode].width;
	_currentWindowHeight = _videoModes[defaultVideoMode].height;
}

