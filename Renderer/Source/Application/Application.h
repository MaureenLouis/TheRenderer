#pragma once
#include "Fundation/Ref/Unique.h"
#include "Core/OO/Singleton.h"
#include "Window/Window.h"

FORWARD_DECL(UiLayer);
FORWARD_DECL(Layer);
FORWARD_DECL(Event);
FORWARD_DECL(Window);


class Application
{
	SELF(Application);

public:

	virtual ~Application();

	void pushLayer(Layer* layer);

	void run();
	void onEvent(Event& e);

	GLFWwindow* windowHandle() const;
	Window* window() const;

	double fps() const;

	static Application* getPtr()
	{
		if (!s_instance)
		{
			s_instance = new Application;
		}
		return s_instance;
	}

	static Application& get()
	{
		return *getPtr();
	}

	void addGuiLayer(UiLayer* layer);
	void addLayer(Layer* layer);
	void registerWindow(Window* window);

	static const TCHAR* applicationDir();
	static const std::string& textureDir();
	
private:
	Application();

private:
	class ApplicationPrivate;
	ApplicationPrivate* pImpl;

	static Application* s_instance;

	static double _fps;

};