cmake_minimum_required(VERSION 3.26.3)

project(OpenGLCpp
    VERSION 0.1.0
    # LANGUAGES CXX
    # DESCRIPTION "Learning OpenGL in C++"
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)

# glfw settings
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_executable(ogc
    src/main.cpp
    src/callback.cpp
)

add_subdirectory(external/glfw)

add_subdirectory(external/glad)

target_include_directories(ogc PUBLIC
    external/glad/include
    external/glfw/include
)

target_link_libraries(ogc PRIVATE glad glfw OpenGL::GL)
