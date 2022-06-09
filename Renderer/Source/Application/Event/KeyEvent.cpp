#include "stdafx.h"
#include "KeyEvent.h"

KeyEvent::KeyEvent(const Keyboard::KeyCode keyCode)
    : _keyCode(keyCode)
{

}

KeyPressedEvent::KeyPressedEvent(const Keyboard::KeyCode keyCode, unsigned short repeatCount)
    : KeyEvent(keyCode),
    _repeatCount(repeatCount)
{
}

KeyReleasedEvent::KeyReleasedEvent(const Keyboard::KeyCode keyCode)
	: KeyEvent(keyCode)
{

}

