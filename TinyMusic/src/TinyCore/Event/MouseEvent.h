#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H
#include "Event.h"
#include <SDL2/SDL.h>
namespace TinyCore{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(const float x, const float y)
			: m_MouseX(x), m_MouseY(y) {}

		float GetX() const { return m_MouseX; }
		float GetY() const { return m_MouseY; }

		eastl::string ToString() const override
		{
			eastl::string ss;
			ss.append("MouseMovedEvent: "); 
            ss.append_convert(m_MouseX);
            ss.append(", ");
            ss.append_convert(m_MouseY);
			return ss;
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		float GetXOffset() const { return m_XOffset; }
		float GetYOffset() const { return m_YOffset; }

		eastl::string  ToString() const override
		{
			eastl::string ss;
			ss.append("MouseScrolledEvent: ");
            ss.append_convert(GetXOffset());
            ss.append(", ");
            ss.append_convert(GetYOffset());
			return ss;
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		Uint32 GetMouseButton() { return SDL_GetMouseState(&m_ux,&m_uy); }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)
	protected:
		MouseButtonEvent(int x , int y )
			: m_ux(x),m_uy(y) {}

		int m_ux ;
        int m_uy ;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const MouseCode button)
			: MouseButtonEvent(button) {}

		eastl::string ToString() const override
		{
			eastl::string ss;
			ss.append("MouseButtonPressedEvent: ");
            ss.append_convert(m_Button);
			return ss;
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const MouseCode button)
			: MouseButtonEvent(button) {}

		eastl::string ToString() const override
		{
			eastl::string ss;
			ss.append("MouseButtonReleasedEvent: ");
            ss.append_convert(m_Button);
			return ss;
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}
#endif