#ifndef APPLICATIONSTATE_H
#define APPLICATIONSTATE_H
#include "pch.h"
namespace TinyCore
{
	enum  ApplicationState {
		USE_OPENGL_RENDERER = 0x1,
		USE_VULKAN_RENDERER = 0x2,
		RUNNING_APP = 0x3
	};

	struct ApplicationStateData {
		int32_t data = 0;
		ApplicationStateData() : data{ 0 << USE_OPENGL_RENDERER }
		{

		}
	};

}

#endif