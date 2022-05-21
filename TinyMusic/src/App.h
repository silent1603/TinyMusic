#ifndef APP_H
#define APP_H

#include "TinyCore/Core/ApplicationBase.h"

namespace TinyMusic
{
    class Application : public TinyCore::ApplicationBase<Application>
    {
        public:
        Application() = default;
        ~Application()= default;

        void Update();
        void StartUp();
        private:
     
    };
    
} // namespace TinyMusic

#endif // !APP_H