#pragma once

#include "3rdparty/Unity/IUnityGraphics.h"
#include "3rdparty/nuklear/nuklear.h"
#include "src/UnityKeyCode.h"
#include "src/NuklearApp.h"
#include "src/UnityLogger.h"

#ifndef UNITY_NUKLEAR_LOADER_API
#if defined(__CYGWIN32__)
#if defined UNITYNUKLEAR_LOADER_IS_NO_EXPORT
#define UNITY_NUKLEAR_LOADER_API __declspec(dllimport)
#else
#define UNITY_NUKLEAR_LOADER_API __declspec(dllexport)
#endif
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(WINAPI_FAMILY)
#if defined UNITYNUKLEAR_LOADER_IS_NO_EXPORT
#define UNITY_NUKLEAR_LOADER_API __declspec(dllimport)
#else
#define UNITY_NUKLEAR_LOADER_API __declspec(dllexport)
#endif
#elif defined(__MACH__) || defined(__ANDROID__) || defined(__linux__)
#define IMGUI_LOADER_API
#endif
#endif // !UNITY_NUKLEAR_LOADER_API

namespace UnityNuklearLoader
{
	extern void UNITY_NUKLEAR_LOADER_API RegisterNuklearApp(NuklearApp* app);
	extern void UNITY_NUKLEAR_LOADER_API RemoveNuklearApp(NuklearApp* app);
}

namespace UnityLogger
{
    extern void UNITY_NUKLEAR_LOADER_API Log(const char* message);
    extern void UNITY_NUKLEAR_LOADER_API Log(const std::string message);
    extern void UNITY_NUKLEAR_LOADER_API Log(const int message);
    extern void UNITY_NUKLEAR_LOADER_API Log(const char message);
    extern void UNITY_NUKLEAR_LOADER_API Log(const double message);
    extern void UNITY_NUKLEAR_LOADER_API Log(const bool message);
    extern void UNITY_NUKLEAR_LOADER_API Log(const float message);
}
