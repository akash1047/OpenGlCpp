add_library(moduleUtil STATIC str.cpp reader.cpp str.hpp reader.hpp)

configure_file(test/util_test.h.in util_test.h)

include_directories("${PROJECT_BINARY_DIR}/src/util/")


# tests
testing(util_test test/util_test.cpp)

target_include_directories(util_test PRIVATE "${PROJECT_BINARY_DIR}/src/util/")
target_link_libraries(util_test moduleUtil)

