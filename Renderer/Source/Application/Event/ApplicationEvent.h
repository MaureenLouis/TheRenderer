#pragma once
#include "Event.h"

class WindowCloseEvent : public Event
{
public:
	EVENT_TYPE(EventType::WindowClose);
	EVENT_CATEGORY(EventCategory::Application);
};

  