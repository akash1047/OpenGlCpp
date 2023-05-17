function(testing name src)
    add_executable(${name} ${src})
    target_link_libraries(${name} GTest::gtest_main moduleUtil)
    gtest_discover_tests(${name})
endfunction()

add_library(moduleUtil STATIC reader.cpp reader.hpp)

configure_file(test/util_test.h.in util_test.h)

include_directories("${PROJECT_BINARY_DIR}/src/util/")

# tests
testing(util_test test/util_test.cpp)

target_include_directories(util_test PRIVATE "${PROJECT_BINARY_DIR}/src/util/")

