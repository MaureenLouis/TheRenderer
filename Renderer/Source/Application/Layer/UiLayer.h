#pragma once
#include "Layer.h"

class ImGuiLabel
{
public:
	ImGuiLabel(const std::string& text)
		: _text(std::move(text))
	{}
	
	void paint() {};

private:
	std::string _text;
};

class UiLayer : public Layer
{
public:
	UiLayer();

	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onUpdate(double deltaTime) override;
	virtual void onEvent(Event& event) override;

	virtual void begin();
	virtual void end();

private:
	GLFWwindow* _windowHandle;
	int _width, _height;
};
