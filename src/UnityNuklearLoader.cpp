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
            app->Render(g_nuklearContext);
        }

        nk_d3d11_render(context, NK_ANTI_ALIASING_ON);
    }

    void UNITY_NUKLEAR_LOADER_API RegisterNuklearApp(NuklearApp* app)
    {
        UnityLogger::Log("Unity Nuklear Loader App registered");
        g_apps->push_back(app);
    }

    void UNITY_NUKLEAR_LOADER_API RemoveNuklearApp(NuklearApp* app)
    {
        //return ImguiLoader::RemoveApp(app);
    }
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

void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces* unityInterfaces)
{
    s_UnityInterfaces = unityInterfaces;
    s_Graphics = s_UnityInterfaces->Get<IUnityGraphics>();
    s_Graphics->RegisterDeviceEventCallback(OnGraphicsDeviceEvent);

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

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API ChangeViewport(int width, int height)
{
    nk_d3d11_resize(context, width, height);
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetIsDemoRendering(bool isRendering)
{
    g_demo->SetRender(isRendering);
}

void HandleMouseInput(float posX, float posY, float scrollDeltaX, float scrollDeltaY);
void HandleKeyboardInput(UnityKeyCode keycode, bool down);

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetKeyboardInput(UnityKeyCode key, bool isDown)
{
    HandleKeyboardInput(key, isDown);
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetMousePosition(float posX, float posY, float scrollDeltaX, float scrollDeltaY)
{
    HandleMouseInput(posX, posY, scrollDeltaX, scrollDeltaY);
}

void HandleMouseInput(float posX, float posY, float scrollDeltaX, float scrollDeltaY)
{
    nk_input_motion(UnityNuklearLoader::g_nuklearContext, posX, posY);
    nk_input_scroll(UnityNuklearLoader::g_nuklearContext, nk_vec2(scrollDeltaX, scrollDeltaY));
}

void HandleKeyboardInput(UnityKeyCode keycode, bool down)
{
    switch (keycode)
    {
    case UnityKeyCode::LeftShift:
    case UnityKeyCode::RightShift:
        nk_input_key(UnityNuklearLoader::g_nuklearContext, NK_KEY_SHIFT, down);
        return;

    case UnityKeyCode::Delete:
        nk_input_key(UnityNuklearLoader::g_nuklearContext, NK_KEY_DEL, down);
        return;

    case UnityKeyCode::Return:
        nk_input_key(UnityNuklearLoader::g_nuklearContext, NK_KEY_ENTER, down);
        return;

    case UnityKeyCode::Tab:
        nk_input_key(UnityNuklearLoader::g_nuklearContext, NK_KEY_TAB, down);
        return;

    case UnityKeyCode::LeftArrow:
        switch (keycode)
        {
        case (UnityKeyCode::LeftControl):
            nk_input_key(UnityNuklearLoader::g_nuklearContext, NK_KEY_TEXT_WORD_LEFT, down);
        default:
            nk_input_key(UnityNuklearLoader::g_nuklearContext, NK_KEY_LEFT, down);
            return;
        }
    case UnityKeyCode::RightArrow:
        switch (keycode)
        {
        case (UnityKeyCode::LeftControl):
            nk_input_key(UnityNuklearLoader::g_nuklearContext, NK_KEY_TEXT_WORD_RIGHT, down);
        default:
            nk_input_key(UnityNuklearLoader::g_nuklearContext, NK_KEY_RIGHT, down);
            return;
        }


    case UnityKeyCode::Backspace:
        nk_input_key(UnityNuklearLoader::g_nuklearContext, NK_KEY_BACKSPACE, down);
        return;

    case UnityKeyCode::Home:
        nk_input_key(UnityNuklearLoader::g_nuklearContext, NK_KEY_TEXT_START, down);
        nk_input_key(UnityNuklearLoader::g_nuklearContext, NK_KEY_SCROLL_START, down);
        return;

    case UnityKeyCode::End:
        nk_input_key(UnityNuklearLoader::g_nuklearContext, NK_KEY_TEXT_END, down);
        nk_input_key(UnityNuklearLoader::g_nuklearContext, NK_KEY_SCROLL_END, down);
        return;

    case UnityKeyCode::PageDown:
        nk_input_key(UnityNuklearLoader::g_nuklearContext, NK_KEY_SCROLL_DOWN, down);
        return;

    case UnityKeyCode::PageUp:
        nk_input_key(UnityNuklearLoader::g_nuklearContext, NK_KEY_SCROLL_UP, down);
        return;

    case UnityKeyCode::C:
        switch (keycode)
        {
        case UnityKeyCode::LeftControl:
            nk_input_key(UnityNuklearLoader::g_nuklearContext, NK_KEY_COPY, down);
            return;
        }
        break;

    case UnityKeyCode::V:
        switch (keycode)
        {
        case UnityKeyCode::LeftControl:
            nk_input_key(UnityNuklearLoader::g_nuklearContext, NK_KEY_PASTE, down);
            return;
        }
        break;

    case UnityKeyCode::X:
        switch (keycode)
        {
        case UnityKeyCode::LeftControl:
            nk_input_key(UnityNuklearLoader::g_nuklearContext, NK_KEY_CUT, down);
            return;
        }
        break;

    case UnityKeyCode::Z:
        switch (keycode)
        {
        case UnityKeyCode::LeftControl:
            nk_input_key(UnityNuklearLoader::g_nuklearContext, NK_KEY_TEXT_UNDO, down);
            return;
        }
        break;

    case UnityKeyCode::R:
        switch (keycode)
        {
        case UnityKeyCode::LeftControl:
            nk_input_key(UnityNuklearLoader::g_nuklearContext, NK_KEY_TEXT_REDO, down);
            return;
        }
        break;
        return;

    case UnityKeyCode::Mouse0:
        nk_input_button(UnityNuklearLoader::g_nuklearContext, NK_BUTTON_DOUBLE, UnityNuklearLoader::g_nuklearContext->input.mouse.pos.x, UnityNuklearLoader::g_nuklearContext->input.mouse.pos.y, down);
        nk_input_button(UnityNuklearLoader::g_nuklearContext, NK_BUTTON_LEFT, UnityNuklearLoader::g_nuklearContext->input.mouse.pos.x, UnityNuklearLoader::g_nuklearContext->input.mouse.pos.y, down);
        return;

    case UnityKeyCode::Mouse1:
        nk_input_button(UnityNuklearLoader::g_nuklearContext, NK_BUTTON_RIGHT, UnityNuklearLoader::g_nuklearContext->input.mouse.pos.x, UnityNuklearLoader::g_nuklearContext->input.mouse.pos.y, down);
        return;

    case UnityKeyCode::Mouse2:
        nk_input_button(UnityNuklearLoader::g_nuklearContext, NK_BUTTON_MIDDLE, UnityNuklearLoader::g_nuklearContext->input.mouse.pos.x, UnityNuklearLoader::g_nuklearContext->input.mouse.pos.y, down);
        return;
    }

    return;
}