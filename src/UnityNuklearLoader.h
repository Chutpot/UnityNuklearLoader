#pragma once

#include "..\src\UnityLogger.h"

namespace UnityLogger
{
    void Log(const char* message);
    void Log(const std::string message);
    void Log(const int message);
    void Log(const char message);
    void Log(const double message);
    void Log(const bool message);
    void Log(const float message);
}
