#pragma once


#include "Event.h"

namespace FireFly
{
	class FF_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) : m_MoveX(x), m_MoveY(y) {}
		inline float GetX() const { return m_MoveX; }
		inline float GetY() const { return m_MoveY; }
		
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Moved: " << m_MoveX << ", " << m_MoveY;
			return ss.str();
		}

		EVENT_TYPE_FUNCTION(MouseMoved)
		EVENT_CATEGORY_FUNCTION( (int)EventCategory::EventMouse | (int)EventCategory::EventInput)
	private:
		float m_MoveX;
		float m_MoveY;
	};

	class FF_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float x, float y) : m_OffsetX(x), m_OffsetY(y) {}
		inline float GetX() const { return m_OffsetX; }
		inline float GetY() const { return m_OffsetY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Scrolled: " << m_OffsetX << ", " << m_OffsetY;
			return ss.str();
		}

		EVENT_TYPE_FUNCTION(MouseScrolled)
		EVENT_CATEGORY_FUNCTION((int)EventCategory::EventMouse | (int)EventCategory::EventInput)
	private:
		float m_OffsetX;
		float m_OffsetY;
	};

	class FF_API MouseButtonEvent : public Event
	{
	public:
		inline int GetButton() const { return m_Button; }
		EVENT_CATEGORY_FUNCTION((int)EventCategory::EventMouse | (int)EventCategory::EventInput)
	protected:
		MouseButtonEvent(int button): m_Button(button) {}
		virtual ~MouseButtonEvent(){}
		int m_Button;
	};

	class FF_API MousePressedEvent : public MouseButtonEvent
	{
	public:
		MousePressedEvent(int button) : MouseButtonEvent(button) {}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MousePressed: " << m_Button;
			return ss.str();
		}
		EVENT_TYPE_FUNCTION(MousePressed)
	};

	class FF_API MouseReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseReleasedEvent(int button) : MouseButtonEvent(button) {}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseReleased: " << m_Button;
			return ss.str();
		}
		EVENT_TYPE_FUNCTION(MouseReleased)
	};
}