#pragma once


#include "Event.h"

namespace FireFly
{
	class FF_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}
		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Window Resize: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CATEGORY_FUNCTION( (int)EventCategory::EventWindow )
		EVENT_TYPE_FUNCTION(WindowResize)
	private:
		unsigned int m_Width;
		unsigned int m_Height;
	};

	class FF_API WindowMovedEvent : public Event
	{
	public:
		WindowMovedEvent(float x, float y) : m_MoveX(x), m_MoveY(y) {}
		inline float GetX() const { return m_MoveX; }
		inline float GetY() const { return m_MoveY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Window Moved: " << m_MoveX << ", " << m_MoveY;
			return ss.str();
		}

		EVENT_CATEGORY_FUNCTION((int)EventCategory::EventWindow)
		EVENT_TYPE_FUNCTION(WindowMoved)
	private:
		float m_MoveX;
		float m_MoveY;
	};

	class FF_API WindowCloseEvent : public Event
	{
	public:
		EVENT_CATEGORY_FUNCTION((int)EventCategory::EventWindow)
		EVENT_TYPE_FUNCTION(WindowClose)
	};

	class FF_API WindowFocusEvent : public Event
	{
	public:
		EVENT_CATEGORY_FUNCTION((int)EventCategory::EventWindow)
		EVENT_TYPE_FUNCTION(WindowFocus)
	};

	class FF_API WindowLostFocusEvent : public Event
	{
	public:
		EVENT_CATEGORY_FUNCTION((int)EventCategory::EventWindow)
		EVENT_TYPE_FUNCTION(WindowLostFocus)
	};
}