#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT

#define NK_IMPLEMENTATION
#include <nuklear.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(WINAPI_FAMILY)
#include <initguid.h>
#include <dshow.h>
#include <stdio.h>
#include <Windows.h>

#define NK_D3D11_IMPLEMENTATION
#define NK_D3D12_IMPLEMENTATION
#define CINTERFACE
#define D3D11_NO_HELPERS
#define COBJMACROS
#define WIN32_LEAN_AND_MEAN

#include <d3d11.h>
#include <d3d12.h>
#include <nuklear_d3d11.h>
#include <nuklear_d3d12.h>
#endif