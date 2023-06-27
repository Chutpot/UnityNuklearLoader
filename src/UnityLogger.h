#pragma once

#include <IUnityInterface.h>
#include <IUnityLog.h>

namespace UnityLogger 
{
	void Initialize(IUnityInterfaces* unityInterfaces);
	void Log(const char* msg);
	void LogWarning(const char* msg);
	void LogError(const char* msg);
};