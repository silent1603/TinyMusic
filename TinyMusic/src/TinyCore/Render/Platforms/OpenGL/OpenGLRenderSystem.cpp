#include "OpenGLRenderSystem.h"
#include <glad/glad.h>
#include <EASTL/string.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
namespace TinyCore
{
	OpenGLRenderSystem::OpenGLRenderSystem()
	{
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

		SDL_GL_SetAttribute(
			SDL_GL_CONTEXT_PROFILE_MASK,
			SDL_GL_CONTEXT_PROFILE_CORE);

		eastl::string glsl_version = "";
#ifdef __APPLE__
		// GL 3.2 Core + GLSL 150
		glsl_version = "#version 350";
		SDL_GL_SetAttribute( // required on Mac OS
			SDL_GL_CONTEXT_FLAGS,
			SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
#elif __linux__
		// GL 3.2 Core + GLSL 150
		glsl_version = "#version 350";
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
#elif _WIN32
		// GL 3.0 + GLSL 130
		glsl_version = "#version 330";
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
#endif

		m_sWindowFlags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
		m_pWindow = SDL_CreateWindow(
			"Dear ImGui SDL",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_iWindowWidth,
			m_iWindowHeight,
			m_sWindowFlags);
		// limit to which minimum size user can resize the window
		SDL_SetWindowMinimumSize(m_pWindow, 500, 300);

		m_pContext = SDL_GL_CreateContext(m_pWindow);
		SDL_GL_MakeCurrent(m_pWindow, m_pContext);

		// enable VSync
		SDL_GL_SetSwapInterval(1);

		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
		{
			std::cerr << "[ERROR] Couldn't initialize glad" << std::endl;
		}
		else
		{
			std::cout << "[INFO] glad initialized\n";
		}

		glViewport(0, 0, m_iWindowWidth, m_iWindowHeight);

		// setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		(void)io;

		// setup Dear ImGui style
		ImGui::StyleColorsDark();

		// setup platform/renderer bindings
		ImGui_ImplSDL2_InitForOpenGL(m_pWindow, m_pContext);
		ImGui_ImplOpenGL3_Init(glsl_version.c_str());

		// colors are set in RGBA, but as float
		ImVec4 background = ImVec4(35 / 255.0f, 35 / 255.0f, 35 / 255.0f, 1.00f);

		glClearColor(background.x, background.y, background.z, background.w);

		SDL_AddEventWatch([](void* data, SDL_Event* event) {

			if ((*event).type == SDL_WINDOWEVENT && (*event).window.event == SDL_WINDOWEVENT_RESIZED)
			{
				std::cout << "resize" << '\n';
				static_cast<OpenGLRenderSystem*>(data)->SetWindowSize((*event).window.data2, (*event).window.data2);
				glViewport(0, 0, (*event).window.data2, (*event).window.data2);
				return 1;
			}
			return 0; }
		, this);
	}

	OpenGLRenderSystem::~OpenGLRenderSystem()
	{
		ImGui_ImplOpenGL3_Shutdown();
		SDL_GL_DeleteContext(m_pContext);
	}

	void OpenGLRenderSystem::Setup()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		ImGui_ImplOpenGL3_NewFrame();

		ImGui_ImplSDL2_NewFrame(m_pWindow);
		ImGui::NewFrame();
	}

	void OpenGLRenderSystem::ProcessEvent()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			// without it you won't have keyboard input and other things
			ImGui_ImplSDL2_ProcessEvent(&event);
			// you might also want to check io.WantCaptureMouse and io.WantCaptureKeyboard
			// before processing events

		}
	}

	void OpenGLRenderSystem::Draw()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		SDL_GL_SwapWindow(m_pWindow);
	}
}