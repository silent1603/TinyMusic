#ifndef OPENGLRENDERSYSTEM_H
#define OPENGLRENDERSYSTEM_H
#include "Render/RenderSystem.h"

namespace TinyCore
{
    class OpenGLRenderSystem : public RenderSystem
    {
    public:
        OpenGLRenderSystem();
        ~OpenGLRenderSystem();
        virtual void ProcessEvent() override;
        virtual void Setup() override;
        virtual void Draw()override;

    private:
        SDL_GLContext m_pContext = nullptr;
    };
}
#endif