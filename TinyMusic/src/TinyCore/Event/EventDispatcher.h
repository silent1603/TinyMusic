#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H
#include "Event.h"
namespace TinyCore
{
    class EventDispacher{
        public:

        EventDispacher(Event& event): m_Event(event)
        {

        }

        template<typename Event, typename Function>
        bool Dispatch(const Function& function)
        {
            if(m_event.GetEventType() == Event::GetStaticType())
            {
                m_event.SetHandle(function(static_cast<Event&>(m_Event)));
                return true;
            }
            return false;
        }

        private:
        Event& m_Event;
    };
}
#endif