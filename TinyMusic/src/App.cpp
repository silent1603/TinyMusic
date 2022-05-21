#include "App.h"

namespace TinyMusic
{
    void Application::Update()
    {
        ImGui::Begin("AAA");
        ImGui::Button("Hello", {150, 100});
        ImGui::End();
        ImGui::Begin("Another Window"); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        ImGui::Button("Close Me");
        ImGui::End();
    }

    void Application::StartUp()
    {
    }
} // namespace TinyMusic
