#ifndef EVENTSYSTEM_H
#define EVENTSYSTEm_H
#include <list>
#include <map>
#include <iterator>
#include "EventHandler.h"
namespace TinyCore{


    enum class EventType{
    EVENT_UPDATE,
    EVENT_RENDER,
    EVENT_WINDOW_RESIZE,
    EVENT_WINDOW_FULL,
    EVENT_WINDOW_MINIMUM,
    EVENT_MOUSEUP,
    EVENT_MOUSEDOWN,
    EVENT_MOUSEMOVE,
    EVENT_MOUSEDRAGED,
    EVENT_SCROLLED,
    EVENT_KEYDOWN,
    EVENT_KEYUP
    };

    enum EventCategory
    {

    };
    

    template<typename ReturnT,typename... ArgumentsT>
    class Event{
        private:
        typedef EventHandler<ReturnT, ArgumentsT&& ...>*  EventHandlerPointer;
        typedef std::multimap< int, EventHandlerPointer  > eventMap;
        typedef typename eventMap::iterartor eventMapIterator;
        static eventMap m_svEventMap;
        static eventMapIterator m_pEventMapIterator;

        public:

        Event(){

        }
        ~Event(){
            for(m_pEventMapIterator = m_svEventMap.find(id); m_pEventMapIterator != m_svEventMap.end();m_pEventMapIterator = m_svEventMap.find(id))
			{
				delete m_pEventMapIterator->second;
				mapper.erase(m_pEventMapIterator);
			}
        }
        
    };


    class EventSystem{
        protected:
        public:

        template<typename TargetT,typename ReturnT,typename ParamT>
        void Register(){
            
        }
    };
}

#endif