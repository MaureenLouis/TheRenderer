#pragma once
#include "Application/Event/Event.h"


FORWARD_DECL(OpenGLContext);

class Window
{
	SELF(Window);
public:
	Window();
	~Window();

	void setFullScreen(bool enable);
	void shutdown();
	void onUpdate();

	GLFWwindow* windowHandle() const;

	int width() const;
	int height() const;

	void setEventCallback(std::function<void(Event&)>  func);

	Rect<int> viewportRect();
	Point3D<float> windowCoordToNormDevCoord(const Point3D<float>& p);
	Line3<float> viewLineFromWindow(const Point3D<float>& p);
	Point3D<float> viewPoint();

	void setDefaultVideoMode();
	void configRenderer();

private:
	class WindowCallback;


	int          _antiAliasingLevel;
	bool         _fullScreenMode;
	const GLFWvidmode* _videoModes;
	int          _videoModeCount;
	GLFWmonitor* _primaryMonitor;
	int          _currentWindowWidth;
	int          _currentWindowHeight;
	GLFWwindow*  _window;
	OpenGLContext* _context;

	struct WindowData
	{
	    std::function<void(Event&)> _callback;
	} _windowData;
};