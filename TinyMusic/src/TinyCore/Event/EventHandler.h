#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

namespace TinyCore{

    template <typename ReturnT,typename... ArgumentsT>
    class EventHandlerBase {
        public:
        virtual ReturnT process(ArgumentsT&&... arg) = 0;
    };

    template<typename TargetT,typename ReturnT,typename... ArgumentsT>
    class EventHandler:public EventHandlerBase<ReturnT,ArgumentsT&& ...>{
        private:
            typedef ReturnT (TargetT::*method_t)(ArgumentsT&&...);
        public:
            EventHandler() {}

        ReturnT process(ArgumentsT&&... arg) override
        {
            return (m_pTarget->*m_pMethod)(arg);
        }
        private:
        TargetT* m_pTarget;
        method_t m_pMethod;
    };

}

#endif