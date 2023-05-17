#include "util_test.h"
#include "../reader.hpp"
#include <gtest/gtest.h>

TEST(utilStr, read_file) {
    auto file_str = util::read_file(DIR_SRC "/test/shader_example.glsl");
    char shader_src[] = "#version 330 core\n"
                        "layout (location = 0) in vec3 aPos;\n"
                        "\n"
                        "void main()\n"
                        "{\n"
                        "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                        "}\n";

    ASSERT_EQ(strlen(file_str.c_str()), strlen(shader_src));
    ASSERT_TRUE(file_str == shader_src);
}
