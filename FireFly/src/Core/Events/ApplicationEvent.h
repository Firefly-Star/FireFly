#pragma once

#include "Event.h"

namespace FireFly
{
	class FF_API AppTickEvent : public Event
	{
	public:
		EVENT_CATEGORY_FUNCTION((int)EventCategory::EventApplication)
		EVENT_TYPE_FUNCTION(AppTick)
	};

	class FF_API AppUpdateEvent : public Event
	{
	public:
		EVENT_CATEGORY_FUNCTION((int)EventCategory::EventApplication)
		EVENT_TYPE_FUNCTION(AppUpdate)
	};

	class FF_API AppRenderEvent : public Event
	{
	public:
		EVENT_CATEGORY_FUNCTION((int)EventCategory::EventApplication)
		EVENT_TYPE_FUNCTION(AppRender)
	};
}