#ifndef _UNITY_NUKLEAR_LOADER_H_
#define _UNITY_NUKLEAR_LOADER_H_

#include "IUnityGraphics.h"
#include "nuklear.h"
#include "NuklearApp.h"

#if defined(__CYGWIN32__)
#if defined IMGUI_LOADER_IS_NO_EXPORT
#define UNITY_NUKLEAR_LOADER_API __declspec(dllimport)
#else
#define UNITY_NUKLEAR_LOADER_API __declspec(dllexport)
#endif
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(WINAPI_FAMILY)
#if defined IMGUI_LOADER_IS_NO_EXPORT
#define UNITY_NUKLEAR_LOADER_API __declspec(dllimport)
#else
#define UNITY_NUKLEAR_LOADER_API __declspec(dllexport)
#endif
#elif defined(__MACH__) || defined(__ANDROID__) || defined(__linux__)
#define IMGUI_LOADER_API
#endif

namespace UnityNuklearLoader
{
	void UNITY_NUKLEAR_LOADER_API RegisterNuklearApp(NuklearApp* app);
	void UNITY_NUKLEAR_LOADER_API RemoveNuklearApp(NuklearApp* app);
	void InitializeNuklearLoader();
}
#endif // !_UNITY_NUKLEAR_LOADER_H_