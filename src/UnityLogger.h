//reference https ://stackoverflow.com/questions/43732825/use-debug-log-from-c
#pragma once

#include <string>

extern "C"
{
    //Create a callback delegate
    typedef void(*FuncCallBack)(const char* message, int size);
    static FuncCallBack callbackInstance = nullptr;
    void UNITY_INTERFACE_EXPORT RegisterDebugCallback(FuncCallBack cb);
};