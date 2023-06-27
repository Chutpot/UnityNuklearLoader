#include "UnityLogger.h"
#include <IUnityInterface.h>

static IUnityLog* s_logger;

void UnityLogger::Initialize(IUnityInterfaces* unityInterfaces)
{
	s_logger = unityInterfaces->Get<IUnityLog>();
}

void UnityLogger::Log(const char* msg) 
{
	UNITY_LOG(s_logger, msg);
}

void UnityLogger::LogError(const char* msg)
{
	UNITY_LOG_ERROR(s_logger, msg);
}

void UnityLogger::LogWarning(const char* msg)
{
	UNITY_LOG_WARNING(s_logger, msg);
}