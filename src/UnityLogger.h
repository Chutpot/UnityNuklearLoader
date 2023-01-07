//reference https ://stackoverflow.com/questions/43732825/use-debug-log-from-c
#ifndef _UNITY_LOGGER_H_
#define _UNITY_LOGGER_H_

#include "UnityNuklearLoader.h"
#include <string>

extern "C"
{
    //Create a callback delegate
    typedef void(*FuncCallBack)(const char* message, int size);
    static FuncCallBack callbackInstance = nullptr;
    void UNITY_NUKLEAR_LOADER_API RegisterDebugCallback(FuncCallBack cb);
};

class UnityLogger
{
public:
    static void UNITY_NUKLEAR_LOADER_API Log(const char* message);
    static void UNITY_NUKLEAR_LOADER_API Log(const std::string message);
    static void UNITY_NUKLEAR_LOADER_API Log(const int message);
    static void UNITY_NUKLEAR_LOADER_API Log(const char message);
    static void UNITY_NUKLEAR_LOADER_API Log(const float message);
    static void UNITY_NUKLEAR_LOADER_API Log(const double message);
    static void UNITY_NUKLEAR_LOADER_API Log(const bool message);

private:
    static void send_log(const std::stringstream& ss);
};
#endif // !_UNITY_LOGGER_H_