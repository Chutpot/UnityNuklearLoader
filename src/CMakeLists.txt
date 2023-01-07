set(UNITYNUKLEARLOADER_PROJECT_SRC
	UnityNuklearLoader.cpp
	UnityLogger.cpp
	NuklearDemo.cpp
)

set(UNITYNUKLEARLOADER_PROJECT_HEADER
	${UnityNuklearLoader_SOURCE_DIR}/UnityNuklearLoader.h
	UnityLogger.h
	NuklearApp.h
	NuklearDemo.h
)

add_library(UnityNuklearLoader SHARED ${UNITYNUKLEARLOADER_PROJECT_SRC} ${UNITYNUKLEARLOADER_PROJECT_HEADER})
target_include_directories(UnityNuklearLoader PRIVATE ${UnityNuklearLoader_SOURCE_DIR}/3rdparty/Unity)
target_include_directories(UnityNuklearLoader PRIVATE ${UnityNuklearLoader_SOURCE_DIR}/3rdparty/Nuklear)
target_include_directories(UnityNuklearLoader PRIVATE ${UnityNuklearLoader_SOURCE_DIR})

if(${UNITYNUKLEAR_LOADER_IS_NO_EXPORT})
    target_compile_definitions(UnityNuklearLoader PUBLIC UNITYNUKLEAR_LOADER_IS_NO_EXPORT)
endif()


set_property(GLOBAL PROPERTY VS_STARTUP_PROJECT UnityNuklearLoader)