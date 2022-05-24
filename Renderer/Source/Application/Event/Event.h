#pragma once

#include "Fundation/Type/Enumerate.h"
#include "Fundation/Bitwise/Bitwise.h"
#include "Core/Preprocessor/PreprocessorUtils.h"

Enumerate(EventCategory, uint8_t,
	None = 0,
	Application = BIT(0),
	Input = BIT(1),
	Keyboard = BIT(2),
	Mouse = BIT(3),
	MouseButton = BIT(4));



Enumerate(EventType, uint32_t,
	None = 0,
	WindowClose,
	WindowResize,
	WindowFocus,
	WindowLostFocus,
	WindowMoved,
	AppTick,
	AppUpdate,
	AppRender,
	MouseButtonPressed,
	MouseButtonReleased,
	MouseMoved,
	MouseScrolled);

class Event
{
	friend class EventDispatcher;
public:
	Event()
		: _handled(false) 
	{

	}

	virtual EventType eventType() const = 0;
	virtual const char* name() const = 0;
	virtual EventCategory eventCategory() const = 0;

	const bool handled() const 
	{
		return _handled; 
	}

	bool isInCategory(EventCategory category)
	{
		return category & eventCategory();
	}

protected:
	bool _handled;
};

#define EVENT_TYPE(type)	 																\
public:                                                                                     \
    static EventType staticType() { return type; }								            \
    virtual EventType eventType() const override { return staticType(); }					\
    virtual const char* name() const override { return STRINGIFY(type); }					\

#define EVENT_CATEGORY(category)                                                            \
public:                                                                                     \
    virtual EventCategory eventCategory() const override { return category; }   


class EventDispatcher
{
public:
	EventDispatcher(Event& e)
		: _e(e)
	{}

	template <typename EventType>
	void dispatch(std::function<bool(EventType&)> eventCallBack)
	{
		if (EventType::staticType() == _e.eventType())
		{
			_e._handled = eventCallBack(*(EventType*)(&_e));
		}
	}

private:
	Event& _e;
};

#define EVENT_CALLBACK(x) std::bind(x, this, std::placeholders::_1)