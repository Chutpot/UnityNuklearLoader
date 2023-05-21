//reference https ://stackoverflow.com/questions/43732825/use-debug-log-from-c

#include "UnityNuklearLoader.h"

#include <stdio.h>
#include <sstream>

void send_log(const std::stringstream& ss) {
    const std::string tmp = ss.str();
    const char* tmsg = tmp.c_str();
    if (callbackInstance != nullptr)
        callbackInstance(tmsg, (int)strlen(tmsg));
}

void UnityLogger::Log(const char* message) {
    if (callbackInstance != nullptr)
        callbackInstance(message,(int)strlen(message));
}

void UnityLogger::Log(const std::string message) {
    const char* tmsg = message.c_str();
    if (callbackInstance != nullptr)
        callbackInstance(tmsg, (int)strlen(tmsg));
}

void UnityLogger::Log(const int message) {
    std::stringstream ss;
    ss << message;
    send_log(ss);
}

void UnityLogger::Log(const char message) {
    std::stringstream ss;
    ss << message;
    send_log(ss);
}

void UnityLogger::Log(const float message) {
    std::stringstream ss;
    ss << message;
    send_log(ss);
}

void UnityLogger::Log(const double message) {
    std::stringstream ss;
    ss << message;
    send_log(ss);
}

void UnityLogger::Log(const bool message) {
    std::stringstream ss;
    if (message)
        ss << "true";
    else
        ss << "false";

    send_log(ss);
}

//Create a callback delegate
void UNITY_INTERFACE_EXPORT RegisterDebugCallback(FuncCallBack cb) {
    callbackInstance = cb;
}