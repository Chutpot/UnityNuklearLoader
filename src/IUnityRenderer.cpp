#include "IUnityRenderer.h"

#include "D3D11Renderer.h"
#include "D3D12Renderer.h"

IUnityRenderer* IUnityRenderer::CreateRendererAPI(UnityGfxRenderer apiType, IUnityInterfaces* unityInterfaces, nk_context** ctx)
{
	if (apiType == kUnityGfxRendererD3D11)
	{
		return new D3D11Renderer(unityInterfaces, ctx);
	}
	else if (apiType == kUnityGfxRendererD3D12)
	{
		return new D3D12Renderer(unityInterfaces, ctx);
	}


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