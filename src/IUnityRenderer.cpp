#define NK_IMPLEMENTATION

#include "IUnityRenderer.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(WINAPI_FAMILY)
#define CINTERFACE
#define D3D11_NO_HELPERS
#define NK_D3D11_IMPLEMENTATION
#include "..\3rdparty\nuklear\demo\d3d11\nuklear_d3d11.h"
#include "..\3rdparty\Unity\IUnityGraphicsD3D11.h"
#include "D3D11Renderer.h"
#endif 


IUnityRenderer* IUnityRenderer::CreateRendererAPI(UnityGfxRenderer apiType, IUnityInterfaces* unityInterfaces, nk_context** ctx)
{
	if (apiType == kUnityGfxRendererD3D11)
	{
		return new D3D11Renderer(unityInterfaces, ctx);
	}

#	if SUPPORT_D3D12
	if (apiType == kUnityGfxRendererD3D12)
	{
		extern RenderAPI* CreateRenderAPI_D3D12();
		return CreateRenderAPI_D3D12();
	}
#	endif // if SUPPORT_D3D12


#	if SUPPORT_OPENGL_UNIFIED
	if (apiType == kUnityGfxRendererOpenGLCore || apiType == kUnityGfxRendererOpenGLES20 || apiType == kUnityGfxRendererOpenGLES30)
	{
		extern RenderAPI* CreateRenderAPI_OpenGLCoreES(UnityGfxRenderer apiType);
		return CreateRenderAPI_OpenGLCoreES(apiType);
	}
#	endif // if SUPPORT_OPENGL_UNIFIED

#	if SUPPORT_METAL
	if (apiType == kUnityGfxRendererMetal)
	{
		extern RenderAPI* CreateRenderAPI_Metal();
		return CreateRenderAPI_Metal();
	}
#	endif // if SUPPORT_METAL

#	if SUPPORT_VULKAN
	if (apiType == kUnityGfxRendererVulkan)
	{
		extern RenderAPI* CreateRenderAPI_Vulkan();
		return CreateRenderAPI_Vulkan();
	}
#	endif // if SUPPORT_VULKAN

	// Unknown or unsupported graphics API
	return nullptr;
}