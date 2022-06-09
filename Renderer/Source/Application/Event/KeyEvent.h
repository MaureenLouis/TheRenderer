#pragma once
#include "Application/Device/Keyboard/KeyCode.h"

class KeyEvent : public Event
{
	EVENT_CATEGORY(EventCategory::Keyboard | EventCategory::Input);
public:
	Keyboard::KeyCode getKeyCode() const { return _keyCode; }

protected:
	KeyEvent(const Keyboard::KeyCode keyCode);

	Keyboard::KeyCode _keyCode;
};

class KeyPressedEvent : public KeyEvent
{
	EVENT_TYPE(EventType::KeyPressed);
public:
	KeyPressedEvent(const Keyboard::KeyCode keyCode, unsigned short repeatCount);

private:
	unsigned short _repeatCount;
};


class KeyReleasedEvent : public KeyEvent
{
	EVENT_TYPE(EventType::KeyReleased);
public:
	KeyReleasedEvent(const Keyboard::KeyCode keyCode);
};