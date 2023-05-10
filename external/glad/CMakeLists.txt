add_library(glad SHARED src/gl.c)

target_include_directories(glad PRIVATE include)
