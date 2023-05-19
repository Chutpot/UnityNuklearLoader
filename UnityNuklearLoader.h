#pragma once

#include "3rdparty/Unity/IUnityGraphics.h"
#include "3rdparty/nuklear/nuklear.h"
#include "src/UnityKeyCode.h"
#include "src/UnityLogger.h"

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
