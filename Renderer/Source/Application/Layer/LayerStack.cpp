#include "stdafx.h"
#include "LayerStack.h"
#include "layer.h"

class LayerStack::LayerStackPrivate
{
public:
	LayerStack* _self;

	std::vector<Layer*>           _layers;
	std::vector<Layer*>::iterator _iter;

	LayerStackPrivate(LayerStack* self);
	~LayerStackPrivate();

	void pushLayer(Layer* layer);
	void popLayer(Layer* layer);

	std::vector<Layer*>::iterator begin();
	std::vector<Layer*>::iterator end();
};

LayerStack::LayerStackPrivate::LayerStackPrivate(LayerStack* self)
	: _self(self)
{
	_iter = _layers.begin();
}

LayerStack::LayerStackPrivate::~LayerStackPrivate()
{
	for (auto layer : _layers)
	{
		if (layer)
		{
			delete layer;
		}
	}

	if (_self)
	{
		delete _self;
		_self = nullptr;
	}
}

void LayerStack::LayerStackPrivate::pushLayer(Layer* layer)
{
	_iter = _layers.emplace(_iter, layer);
}

void LayerStack::LayerStackPrivate::popLayer(Layer* layer)
{
	auto it = std::find(_layers.begin(), _layers.end(), layer);

	if (it != _layers.end())
	{
		_layers.erase(it);
		_iter --;
	}
}

std::vector<Layer*>::iterator LayerStack::LayerStackPrivate::begin()
{
	return _layers.begin();
}

std::vector<Layer*>::iterator LayerStack::LayerStackPrivate::end()
{
	return _layers.end();
}

LayerStack::LayerStack()
	: pImpl(new LayerStackPrivate(this))
{

}

LayerStack::~LayerStack()
{


	if (pImpl)
	{
		delete pImpl;
		pImpl = nullptr;
	}
}

void LayerStack::pushLayer(Layer* layer)
{
	pImpl->pushLayer(layer);
}

void LayerStack::popLayer(Layer* layer)
{
	pImpl->popLayer(layer);
}

std::vector<Layer*>::iterator LayerStack::begin()
{
	return pImpl->begin();
}

std::vector<Layer*>::iterator LayerStack::end()
{
	return pImpl->end();
}

