#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(WINAPI_FAMILY)
#define CINTERFACE
#define D3D11_NO_HELPERS
#define WIN32_LEAN_AND_MEAN
#define COBJMACROS
#endif 

#include <d3d11.h>

#include "D3D11Renderer.h"
#include "..\3rdparty\nuklear\demo\d3d11\nuklear_d3d11.h"
#include "..\3rdparty\Unity\IUnityGraphicsD3D11.h"

static IDXGISwapChain* swap_chain;
static ID3D11Device* device;
static ID3D11DeviceContext* context;
static ID3D11RenderTargetView* rt_view;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_INDEX_BUFFER 128 * 1024


D3D11Renderer::D3D11Renderer(IUnityInterfaces* unityInterfaces, nk_context** ctx)
{
    IUnityGraphicsD3D11* d3d = unityInterfaces->Get<IUnityGraphicsD3D11>();
    ID3D11Device* device = d3d->GetDevice();
    ID3D11Device_GetImmediateContext(device, &context);
    *ctx = nk_d3d11_init(device, WINDOW_WIDTH, WINDOW_HEIGHT, MAX_VERTEX_BUFFER, MAX_INDEX_BUFFER);

    {struct nk_font_atlas* atlas;
    nk_d3d11_font_stash_begin(&atlas);
    nk_d3d11_font_stash_end();
    }
}

D3D11Renderer::~D3D11Renderer()
{
}

void D3D11Renderer::Render()
{
    nk_d3d11_render(context, NK_ANTI_ALIASING_ON);
}

void D3D11Renderer::Resize(int width, int height)
{
    nk_d3d11_resize(context, width, height);
}
