#include "stdafx.h"
#include "Application/Application.h"
#include "Application/Window/Window.h"
#include "Application/Layer/UiLayer.h"
#include "Application/Layer/RenderLayer.h"

struct Var
{
	double operator() (double v) { return v; }
};

struct Constant
{
	double c;
	Constant(double d) : c(d) {}
	double operator()(double) { return c; }
};

template <class L, class H, class OP>
struct DBinaryExpression
{
	L l_;
	H h_;
	DBinaryExpression(L l, H h) : l_(l), h_(h) {}

	double operator()(double d) 
	{ 
		return OP::apply(l_(d), h_(d)); 
	}
};

struct Add
{
	static double apply(double l, double h) 
	{ 
		l + h; 
	};
};


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
