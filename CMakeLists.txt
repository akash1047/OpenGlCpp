cmake_minimum_required(VERSION 3.26.3)

project(OpenGLCpp
    VERSION 0.1.0
    # LANGUAGES CXX
    # DESCRIPTION "Learning OpenGL in C++"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file(metadata.h.in metadata.h)
include_directories(${PROJECT_BINARY_DIR})

find_package(OpenGL REQUIRED)

add_executable(ogc
    src/main.cpp
    src/callback.cpp
    src/shader.cpp
)

# glfw settings
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# external dependency
add_subdirectory(external/glfw)
add_subdirectory(external/glad)

# testing

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# the modules having test will be added in ctest
enable_testing()
include(GoogleTest)

# module dependency

# util lib should be added first
# as it is required by other module
add_subdirectory(src/util)

add_subdirectory(src/opengl)

target_include_directories(ogc PUBLIC
    external/glad/include
    external/glfw/include
)

target_link_libraries(ogc PRIVATE glad glfw OpenGL::GL moduleOpengl moduleUtil)
