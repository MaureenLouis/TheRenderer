#pragma once
#include "Event.h"
#include "Application/Device/Mouse/MouseCode.h"
#include "Fundation/Type/Bitset.h"

class MouseMoveEvent : public Event
{
	EVENT_TYPE(EventType::MouseMoved);
	EVENT_CATEGORY(EventCategory::Mouse | EventCategory::Input);

public:
	MouseMoveEvent(const double x, const double y)
		: _x(x), _y(y)
	{
		
	}

	PointD cursorPos() const { return PointD(_x, _y); }

	bool leftButtonPressed()
	{
		return _keys.isSet(0);
	}

	void addKeyPressed(const MouseCode& button)
	{
		if (button == MouseCode::ButtonLeft)
		{
			_keys.set(0);    
		}
		else if (button == MouseCode::ButtonRight)
		{
			_keys.set(1);
		}
		
	}

private:
	double _x;
	double _y;

	Bitset<8> _keys;
};

class MouseScrollEvent : public Event
{
	EVENT_CATEGORY(EventCategory::Mouse | EventCategory::Input);
	EVENT_TYPE(EventType::MouseScrolled);

public:
	MouseScrollEvent(const double xOffset, const double yOffset)
		: _xOffset(xOffset), _yOffset(yOffset)
	{

	}
	
	double xOffset() const { return _xOffset; }
	double yOffset() const { return _yOffset; }



private:
	double _xOffset, _yOffset;
};

class MouseButtonEvent : public Event
{
	EVENT_CATEGORY(EventCategory::Mouse | EventCategory::Input | EventCategory::MouseButton);
protected:
	MouseButtonEvent(const MouseCode mouseCode, const PointD& cursorPos)
		: Event()
	{
		_mouseCode = mouseCode;
		_cursorPos = cursorPos;
	}

	MouseCode mouseCode() const
	{
		return _mouseCode;
	}

public:
	PointD cursorPos() const
	{
		return _cursorPos;
	}



private:
	MouseCode  _mouseCode;
	PointD     _cursorPos;
};

class MousePressEvent : public MouseButtonEvent
{
	EVENT_TYPE(EventType::MouseButtonPressed);

public:
	MousePressEvent(const MouseCode mouseCode, const PointD& cursorPos)
		: MouseButtonEvent(mouseCode, cursorPos)
	{
	}

};

class MouseReleaseEvent : public MouseButtonEvent
{
	EVENT_TYPE(EventType::MouseButtonReleased);

public:
	MouseReleaseEvent(const MouseCode mouseCode, const PointD& cursorPos)
		: MouseButtonEvent(mouseCode, cursorPos)
	{
	}

};