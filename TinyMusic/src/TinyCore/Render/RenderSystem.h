#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H
#include "Core/pch.h"
#include <SDL2/SDL.h>
namespace TinyCore
{
    class RenderSystem
    {
    public:
        RenderSystem();
        virtual  ~RenderSystem();
        virtual void ProcessEvent() = 0;
        virtual void Setup() = 0;
        virtual void Draw() = 0;
        void SetWindowSize(int w, int h);
    private:


    protected:
        int m_iWindowWidth = 800;
        int m_iWindowHeight = 600;
        SDL_Window *m_pWindow = nullptr;
        SDL_WindowFlags m_sWindowFlags = SDL_WINDOW_RESIZABLE;
    };
}

#endif