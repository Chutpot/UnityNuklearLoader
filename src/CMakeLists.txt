set(UNITYNUKLEARLOADER_PROJECT_SRC
	UnityNuklearLoader.def
	UnityNuklearLoader.cpp
	UnityLogger.cpp
	IUnityRenderer.cpp
	D3D11Renderer.cpp
)

set(UNITYNUKLEARLOADER_PROJECT_HEADER
	UnityNuklearLoader.h
	UnityLogger.h
	IUnityRenderer.h
	D3D11Renderer.h
)

add_library(UnityNuklearLoader SHARED ${UNITYNUKLEARLOADER_PROJECT_SRC} ${UNITYNUKLEARLOADER_PROJECT_HEADER})
set_property(GLOBAL PROPERTY VS_STARTUP_PROJECT UnityNuklearLoader)