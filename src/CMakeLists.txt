set(UNITYNUKLEARLOADER_PROJECT_SRC
	UnityNuklearLoader.def
	UnityNuklearLoader.cpp
	UnityLogger.cpp
	NuklearDemo.cpp
)

set(UNITYNUKLEARLOADER_PROJECT_HEADER
	${UNITYNUKLEARLOADER_SOURCE_DIR}/UnityNuklearLoader.h
	UnityLogger.h
	NuklearApp.h
	NuklearDemo.h
	UnityKeyCode.h
)

add_library(UnityNuklearLoader SHARED ${UNITYNUKLEARLOADER_PROJECT_SRC} ${UNITYNUKLEARLOADER_PROJECT_HEADER})
set_property(GLOBAL PROPERTY VS_STARTUP_PROJECT UnityNuklearLoader)