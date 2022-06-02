#ifndef APPLICATIONBASE_H
#define APPLICATIONBASE_H
#include "Core/pch.h"
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <EASTL/string.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include "Render/Platforms/OpenGL/OpenGLRenderSystem.h"
#include "Event/EventSystem.h"
#include "ApplciationState.h"
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include <functional>
#ifdef _DEBUG
#define DBG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif
namespace TinyCore
{
	#define BIND_FUNCTION(x) std::bind(&ApplicationBase::x,this,std::placeholders::_1);
	template <typename Derived>
	class ApplicationBase
	{

	public:
		ApplicationBase()
		{

			
			if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			{
				std::exit(1);
			}
			m_pRenderSystem = new OpenGLRenderSystem();
			m_isRunning = true;
		}

		~ApplicationBase()
		{
			delete m_pRenderSystem;
			SDL_Quit();
			_CrtDumpMemoryLeaks();
		}

		void Run()
		{
			StartUp();
			while (m_isRunning)
			{

				ProcessEvent();
				// start the Dear ImGui frame
				m_pRenderSystem->Setup();
				Update();
				// rendering
				m_pRenderSystem->Draw();
			}
		}

		void StartUp()
		{

			SDL_AddEventWatch(
				[](void *data, SDL_Event *event) {
					SDL_Event &ev = *event;
					if (ev.type == SDL_QUIT || ev.key.keysym.sym == SDLK_ESCAPE)
					{
						static_cast<ApplicationBase*>(data)->SetRunning(false);
						return 1;
					}
					return 0;
				},
				this);
			static_cast<Derived *>(this)->StartUp();
		}

		void Update()
		{
			static_cast<Derived *>(this)->Update();
		}

		void ProcessEvent()
		{
			m_pRenderSystem->ProcessEvent();
		}
		
		void SetRunning(bool value)
		{
			m_isRunning = value;
		}

		void GetRunning()
		{
			return m_isRunning;
		}

	private:
		bool m_isRunning = false;
		RenderSystem *m_pRenderSystem = nullptr;
		ApplicationStateData m_structState;
		friend Derived;
	};

}

#endif
