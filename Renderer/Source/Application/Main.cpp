#include "stdafx.h"
#include "Application/Application.h"
#include "Application/Window/Window.h"
#include "Application/Layer/UiLayer.h"
#include "Application/Layer/RenderLayer.h"



int main()
{

	Log::init();

	Application* app = Application::getPtr();

	app->registerWindow(new Window);
	app->addGuiLayer(new UiLayer);
	app->addLayer(new RenderLayer);

	app->run();

	return 0;
}
