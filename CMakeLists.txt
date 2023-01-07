cmake_minimum_required(VERSION 3.20)

project(UNITYNUKLEARLOADER VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(3rdparty)
add_subdirectory(src)

set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "")