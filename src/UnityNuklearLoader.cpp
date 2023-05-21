#include "IUnityRenderer.h"
#include "UnityNuklearLoader.h"

static IUnityInterfaces* s_UnityInterfaces = nullptr;
static IUnityGraphics* s_Graphics = nullptr;
static UnityGfxRenderer s_DeviceType = kUnityGfxRendererNull;


namespace UnityNuklearLoader
{
    static nk_context* g_nuklearContext = nullptr;
    static IUnityRenderer* g_renderer = nullptr;

    static void InitializeNuklearLoader()
    {
        g_renderer = IUnityRenderer::CreateRendererAPI(s_DeviceType, s_UnityInterfaces, &g_nuklearContext);
    }

    static void Render()
    {
        g_renderer->Render();
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
        g_renderer->Resize(width, height);
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