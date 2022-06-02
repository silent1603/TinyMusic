#ifndef EVENT_H
#define EVENT_H
#include "Core/pch.h"
#include "EASTL/string.h"

namespace TinyCore{
    
    enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication    = BIT(0),
		EventCategoryInput          = BIT(1),
		EventCategoryKeyboard       = BIT(2),
		EventCategoryMouse          = BIT(3),
		EventCategoryMouseButton    = BIT(4)
	};
    

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


    class Event{
		public:

		virtual ~Event() = default;
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual eastl::string ToString() const { return GetName();}
		inline void SetHandle(bool value) { m_bHandled  |= value;}
		inline bool HasHandled() { return m_bHandled;}
		private:
		bool m_bHandled = false;
    };


	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString().c_str();
	}
}

#endif