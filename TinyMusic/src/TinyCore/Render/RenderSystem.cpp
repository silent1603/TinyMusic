#include "RenderSystem.h"
#include <imgui_impl_sdl.h>
namespace TinyCore
{
    RenderSystem::RenderSystem()
    {
    }
    
    RenderSystem::~RenderSystem()
    {
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
        SDL_DestroyWindow(m_pWindow);
    }


    void RenderSystem::SetWindowSize(int w, int h)
    {
        m_iWindowWidth = w;
        m_iWindowHeight = h;
    }
}