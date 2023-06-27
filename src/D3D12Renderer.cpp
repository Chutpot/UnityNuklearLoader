#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(WINAPI_FAMILY)
#define WIN32_LEAN_AND_MEAN
#endif 

#include <combaseapi.h>
#include <dxgi1_6.h>
#include <d3d12.h>
#include <d3d12.h>
#include <stddef.h>
#include <string.h>
#include <float.h>
#include <assert.h>


#include "D3D12Renderer.h"
extern "C"
{
#include <nuklear_d3d12.h>
}
#include <IUnityGraphicsD3D12.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define USER_TEXTURES 6

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_INDEX_BUFFER 128 * 1024

static IUnityGraphicsD3D12v5* s_D3D12;
static ID3D12Resource* s_D3D12Upload;
static ID3D12CommandAllocator* s_D3D12CmdAlloc;
static ID3D12GraphicsCommandList* s_D3D12CmdList;
static ID3D12Fence* s_D3D12QueueFence;
static ID3D12CommandQueue* s_D3D12CmdQueue;
static UINT64 s_D3D12FenceValue = 0;
static HANDLE s_D3D12Event = NULL;

const UINT kNodeMask = 0;

static void signal_and_wait()
{
    HRESULT hr;

    s_D3D12FenceValue = s_D3D12->GetNextFrameFenceValue();
    /* Signal fence when execution finishes */
    hr = s_D3D12CmdQueue->Signal(s_D3D12->GetFrameFence(), s_D3D12FenceValue);
    assert(SUCCEEDED(hr));


    /* Wait for queue to finish */
    while (s_D3D12QueueFence->GetCompletedValue() != s_D3D12FenceValue)
    {
        SwitchToThread(); /* Allow windows to do other work */
    }
}

static void execute_commands()
{
    /* Prepare command list for execution */
    s_D3D12CmdList->Close();

    /* Execute on command queue */
    ID3D12CommandList* cmd_lists[] = { (ID3D12CommandList*)s_D3D12CmdList };
    s_D3D12CmdQueue->ExecuteCommandLists(1, cmd_lists);

    /* Wait for execution */
    
    signal_and_wait();

    /* Reset command allocator and list */
    s_D3D12CmdAlloc->Reset();
    s_D3D12CmdList->Reset(s_D3D12CmdAlloc, NULL);
}

D3D12Renderer::D3D12Renderer(IUnityInterfaces* unityInterfaces, nk_context** ctx)
{

    s_D3D12 = unityInterfaces->Get<IUnityGraphicsD3D12v5>();
    ID3D12Device* device = s_D3D12->GetDevice();

    HRESULT hr = E_FAIL;

    s_D3D12CmdQueue = s_D3D12->GetCommandQueue();


    hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&s_D3D12CmdAlloc));
    if (FAILED(hr)) OutputDebugStringA("Failed to CreateCommandAllocator.\n");
    hr = device->CreateCommandList(kNodeMask, D3D12_COMMAND_LIST_TYPE_DIRECT, s_D3D12CmdAlloc, nullptr, IID_PPV_ARGS(&s_D3D12CmdList));
    if (FAILED(hr)) OutputDebugStringA("Failed to CreateCommandList.\n");
    
    *ctx = nk_d3d12_init(device, WINDOW_WIDTH, WINDOW_HEIGHT, MAX_VERTEX_BUFFER, MAX_INDEX_BUFFER, USER_TEXTURES);


    {
        //struct nk_font_atlas* atlas;
        //nk_d3d12_font_stash_begin(&atlas);
        /*struct nk_font *droid = nk_font_atlas_add_from_file(atlas, "../../extra_font/DroidSans.ttf", 14, 0);*/
        /*struct nk_font *robot = nk_font_atlas_add_from_file(atlas, "../../extra_font/Roboto-Regular.ttf", 14, 0);*/
        /*struct nk_font *future = nk_font_atlas_add_from_file(atlas, "../../extra_font/kenvector_future_thin.ttf", 13, 0);*/
        /*struct nk_font *clean = nk_font_atlas_add_from_file(atlas, "../../extra_font/ProggyClean.ttf", 12, 0);*/
        /*struct nk_font *tiny = nk_font_atlas_add_from_file(atlas, "../../extra_font/ProggyTiny.ttf", 10, 0);*/
        /*struct nk_font *cousine = nk_font_atlas_add_from_file(atlas, "../../extra_font/Cousine-Regular.ttf", 13, 0);*/
        nk_d3d12_font_stash_end(s_D3D12CmdList);
        /*nk_style_load_all_cursors(ctx, atlas->cursors);*/
        /*nk_style_set_font(ctx, &droid->handle)*/;
    }
    //execute_commands();
    //nk_d3d12_font_stash_cleanup();
}

D3D12Renderer::~D3D12Renderer()
{

}

void D3D12Renderer::Render()
{
    //nk_d3d12_render(s_D3D12CmdList, NK_ANTI_ALIASING_ON);
}

void D3D12Renderer::Resize(int width, int height)
{
    //nk_d3d12_resize(width, height);
}