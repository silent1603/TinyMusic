#include "App.h"

namespace TinyMusic
{
    void Application::Update()
    {
        ImGui::Begin("AAA");
        ImGui::Button("Hello", { 150,100 });
        ImGui::End();
    }

    void Application::StartUp()
    {
        
    }
} // namespace TinyMusic
