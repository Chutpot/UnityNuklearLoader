set(UNITYNUKLEARLOADER_PROJECT_SRC
    UnityNuklearLoader.cpp
	IUnityRenderer.cpp
	D3D11Renderer.cpp
	D3D12Renderer.cpp
	UnityLogger.cpp
	UnityNuklearLoader.def
	IUnityRendererImplemantation.c
)

set(UNITYNUKLEARLOADER_PROJECT_HEADER
	UnityLogger.h
	IUnityRenderer.h
	D3D11Renderer.h
	D3D12Renderer.h
)


add_library(UnityNuklearLoader SHARED ${UNITYNUKLEARLOADER_PROJECT_SRC} ${UNITYNUKLEARLOADER_PROJECT_HEADER})
target_include_directories(UnityNuklearLoader PUBLIC "${PROJECT_SOURCE_DIR}\\3rdparty\\Unity\\")
target_include_directories(UnityNuklearLoader PUBLIC "${PROJECT_SOURCE_DIR}\\3rdparty\\Nuklear\\")
target_include_directories(UnityNuklearLoader PUBLIC "${PROJECT_SOURCE_DIR}\\3rdparty\\Nuklear\\Demo\\d3d11")
target_include_directories(UnityNuklearLoader PUBLIC "${PROJECT_SOURCE_DIR}\\3rdparty\\Nuklear\\Demo\\d3d12")
link_libraries(UnityNuklearLoader NuklearImplemantation)
set_property(GLOBAL PROPERTY VS_STARTUP_PROJECT UnityNuklearLoader)