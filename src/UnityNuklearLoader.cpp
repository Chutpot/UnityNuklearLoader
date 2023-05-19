#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(WINAPI_FAMILY)
#define CINTERFACE
#define D3D11_NO_HELPERS
#define NK_D3D11_IMPLEMENTATION
#endif 

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION

#include "..\UnityNuklearLoader.h"
#include "..\3rdparty\nuklear\demo\d3d11\nuklear_d3d11.h"
#include "..\3rdparty\Unity\IUnityGraphicsD3D11.h"
#include "UnityLogger.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

//These static variables will be refactored when graphics API will be non-hardcoded
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


namespace UnityNuklearLoader
{
    static nk_context* g_nuklearContext = nullptr;

    static void InitializeNuklearLoader()
    {
        IUnityGraphicsD3D11* d3d = s_UnityInterfaces->Get<IUnityGraphicsD3D11>();
        ID3D11Device* device = d3d->GetDevice();
        ID3D11Device_GetImmediateContext(device, &context);
        g_nuklearContext = nk_d3d11_init(device, WINDOW_WIDTH, WINDOW_HEIGHT, MAX_VERTEX_BUFFER, MAX_INDEX_BUFFER);

        {struct nk_font_atlas* atlas;
        nk_d3d11_font_stash_begin(&atlas);
        nk_d3d11_font_stash_end();
        }
    }

    static void Render()
    {
        nk_d3d11_render(context, NK_ANTI_ALIASING_ON);
    }

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

    // UNITY INTERACTION EXPORTS


    extern "C" UnityRenderingEvent UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetRenderEventFunc()
    {
        return UnityNuklearLoader::OnRenderEvent;
    }

    extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API ChangeViewport(int width, int height)
    {
        nk_d3d11_resize(context, width, height);
    }

    extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetCharInput(char c)
    {
        nk_input_unicode(UnityNuklearLoader::g_nuklearContext, c);
    }

    extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetKeyboardInput(int key, bool isDown)
    {
        nk_input_key(UnityNuklearLoader::g_nuklearContext, (nk_keys)key, isDown);
    }


    extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetButtonInput(int key, bool isDown)
    {
        nk_input_button(UnityNuklearLoader::g_nuklearContext, (nk_buttons)key, g_nuklearContext->input.mouse.pos.x, UnityNuklearLoader::g_nuklearContext->input.mouse.pos.y, isDown);
    }

    extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetMouseInput(float posX, float posY, float scrollDeltaX, float scrollDeltaY)
    {
        nk_input_motion(UnityNuklearLoader::g_nuklearContext, posX, posY);
        nk_input_scroll(UnityNuklearLoader::g_nuklearContext, nk_vec2(scrollDeltaX, scrollDeltaY));
    }

    extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetInputState(bool isOpen)
    {
        if (isOpen) {
            nk_input_begin(g_nuklearContext);
        }
        else
        {
            nk_input_end(g_nuklearContext);
        }
    }

    extern "C"  UNITY_INTERFACE_EXPORT nk_context* UNITY_INTERFACE_API GetContext()
    {
        return g_nuklearContext;
    }
}

void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces* unityInterfaces)
{
    s_UnityInterfaces = unityInterfaces;
    s_Graphics = s_UnityInterfaces->Get<IUnityGraphics>();
    s_Graphics->RegisterDeviceEventCallback(UnityNuklearLoader::OnGraphicsDeviceEvent);

#if SUPPORT_VULKAN
    if (s_Graphics->GetRenderer() == kUnityGfxRendererNull)
    {
        extern void RenderAPI_Vulkan_OnPluginLoad(IUnityInterfaces*);
        RenderAPI_Vulkan_OnPluginLoad(unityInterfaces);
    }
#endif // SUPPORT_VULKAN
    UnityNuklearLoader::OnGraphicsDeviceEvent(kUnityGfxDeviceEventInitialize);
}

void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginUnload()
{
}