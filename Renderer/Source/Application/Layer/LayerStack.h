#pragma once

FORWARD_DECL(Layer);

class LayerStack
{
public:
	LayerStack();
	~LayerStack();

	void pushLayer(Layer* layer);
	void popLayer(Layer* layer);

	std::vector<Layer*>::iterator begin();
	std::vector<Layer*>::iterator end();

private:
	class LayerStackPrivate;
	LayerStackPrivate* pImpl;
};

