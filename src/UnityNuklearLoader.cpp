#define CINTERFACE
#define D3D11_NO_HELPERS
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_D3D11_IMPLEMENTATION
#include "UnityNuklearLoader.h"
#include "3rdparty/nuklear/demo/d3d11/nuklear_d3d11.h"
#include <vector>
#include <IUnityGraphicsD3D11.h>
#include "UnityLogger.h"

#include "NuklearDemo.h"

static IUnityInterfaces* s_UnityInterfaces = nullptr;
static IUnityGraphics* s_Graphics = nullptr;
static UnityGfxRenderer s_DeviceType = kUnityGfxRendererNull;

static IDXGISwapChain* swap_chain;
static ID3D11Device* device;
static ID3D11DeviceContext* context;
static ID3D11RenderTargetView* rt_view;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_INDEX_BUFFER 128 * 1024


NuklearDemo* g_demo = nullptr;;
struct nk_font_atlas* atlas;
struct nk_colorf bg;

namespace UnityNuklearLoader
{
	std::vector<NuklearApp*>* g_apps = nullptr;
	nk_context* g_nuklearContext = nullptr;

	void InitializeNuklearLoader()
	{
		IUnityGraphicsD3D11* d3d = s_UnityInterfaces->Get<IUnityGraphicsD3D11>();
		ID3D11Device* device = d3d->GetDevice();
		ID3D11Device_GetImmediateContext(device, &context);
		g_nuklearContext = nk_d3d11_init(device, WINDOW_WIDTH, WINDOW_HEIGHT, MAX_VERTEX_BUFFER, MAX_INDEX_BUFFER);

		g_apps = new std::vector <NuklearApp*>();
		{struct nk_font_atlas* atlas;
		nk_d3d11_font_stash_begin(&atlas);
		nk_d3d11_font_stash_end();
		}

		g_demo = new NuklearDemo();
		RegisterNuklearApp(g_demo);
	}

	void Render()
	{
		nk_input_begin(g_nuklearContext);
		nk_input_end(g_nuklearContext);

		for (NuklearApp* app : *g_apps)
		{
			UnityLogger::Log("render");
			app->Render(g_nuklearContext);
		}
		
		nk_d3d11_render(context, NK_ANTI_ALIASING_ON);
	}

	void UNITY_NUKLEAR_LOADER_API RegisterNuklearApp(NuklearApp* app)
	{
		g_apps->push_back(app);
	}

	void UNITY_NUKLEAR_LOADER_API RemoveNuklearApp(NuklearApp* app)
	{
		//return ImguiLoader::RemoveApp(app);
	}
}

static float g_Time;

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetTimeFromUnity(float t) { g_Time = t; }

static void UNITY_INTERFACE_API OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType)
{
	switch (eventType)
	{
		case kUnityGfxDeviceEventInitialize:
		{
			s_DeviceType = s_Graphics->GetRenderer();
			UnityNuklearLoader::InitializeNuklearLoader();
			break;
		}
		case kUnityGfxDeviceEventShutdown:
		{
			s_DeviceType = kUnityGfxRendererNull;
			break;
		}
		case kUnityGfxDeviceEventBeforeReset:
		{
			break;
		}
		case kUnityGfxDeviceEventAfterReset:
		{
			break;
		}
	};
}

void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces* unityInterfaces)
{
	s_UnityInterfaces = unityInterfaces;
	s_Graphics = s_UnityInterfaces->Get<IUnityGraphics>();
	s_Graphics->RegisterDeviceEventCallback(OnGraphicsDeviceEvent);

	UnityLogger::Log(context);

#if SUPPORT_VULKAN
	if (s_Graphics->GetRenderer() == kUnityGfxRendererNull)
	{
		extern void RenderAPI_Vulkan_OnPluginLoad(IUnityInterfaces*);
		RenderAPI_Vulkan_OnPluginLoad(unityInterfaces);
	}
#endif // SUPPORT_VULKAN
	OnGraphicsDeviceEvent(kUnityGfxDeviceEventInitialize);
}

void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginUnload()
{
	//g_isUnloaded = true;
}

#if UNITY_WEBGL
typedef void	(UNITY_INTERFACE_API* PluginLoadFunc)(IUnityInterfaces* unityInterfaces);
typedef void	(UNITY_INTERFACE_API* PluginUnloadFunc)();

extern "C" void	UnityRegisterRenderingPlugin(PluginLoadFunc loadPlugin, PluginUnloadFunc unloadPlugin);

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API RegisterPlugin()
{
	UnityRegisterRenderingPlugin(UnityPluginLoad, UnityPluginUnload);
}
#endif

static void UNITY_INTERFACE_API OnRenderEvent(int eventID)
{
	UnityNuklearLoader::Render();
}

extern "C" UnityRenderingEvent UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetRenderEventFunc()
{
	return OnRenderEvent;
}