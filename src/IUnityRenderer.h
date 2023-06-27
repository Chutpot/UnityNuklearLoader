#pragma once

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT

#include <IUnityGraphics.h>
#include <nuklear.h>


class IUnityRenderer
{
public:
	virtual void Render()=0;
	virtual void Resize(int width, int height) = 0;
	static IUnityRenderer* CreateRendererAPI(UnityGfxRenderer apiType, IUnityInterfaces* unityInterfaces, nk_context** ctx);
};