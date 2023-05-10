#define GLFW_INCLUDE_NONE
#include "glad/gl.h"
#include "shader.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

using std::cout;
using std::endl;

int main() {
    int width{800};
    int height{800};
    char title[] = "OGL";

    GLFWwindow *window{nullptr};

    glfwSetErrorCallback([](int code, const char *desc) {
        cout << "GLFW ERROR: " << desc << endl;
    });

    // initialize glfw library
    if (!glfwInit()) {
        cout << "Failed to initialize glfw library" << endl;
        return -1;
    }

    /* window creation */

    // set window creation hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window
    if (!(window = glfwCreateWindow(width, height, title, nullptr, nullptr))) {
        cout << "Failed to create window" << endl;
        glfwTerminate();
        return -1;
    }

    // make opengl context window
    glfwMakeContextCurrent(window);

    // load opengl binding
    // note: window context should be created
    // before calling this function
    if (!gladLoaderLoadGL()) {
        cout << "Failed to load Glad" << endl;
        glfwTerminate();
        return -1;
    }

    glClearColor(0.9f, 0.8f, 0.3f, 0.7f);
    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(
        window, [](GLFWwindow *win, int h, int w) { glViewport(0, 0, h, w); });

    // input callback
    glfwSetKeyCallback(window, [](GLFWwindow *win, int key, int scancode,
                                  int action, int mods) {
        // exit on pressing escape
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(win, GLFW_TRUE);
        }
    });

    // clang-format off
    float vertices[] = {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f
    };
    // clang-format on

    unsigned int vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertices, GL_STATIC_DRAW);

    const char *vertex_shader_src =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
        "}\0";

    // unsigned int vertex_shader;
    // vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(vertex_shader, 1, &vertex_shader_src, nullptr);
    // glCompileShader(vertex_shader);

    VertexShader vshader{};
    vshader.compile(vertex_shader_src);

    if (!vshader.compile_success()) {
        cout << "ERROR [vertex shader compilation failed]\n"
             << vshader.log_info() << endl;
    }

    // int success;
    // char info_log[512];
    // glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    // if (!success) {
    //     glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
    //     cout << "ERROR [vertex shader compilation failed]: " << info_log
    //          << endl;
    // }

    FragmentShader fshader{};
    fshader.compile("#version 330 core\n"
                    "out vec4 FragColor;\n"
                    "\n"
                    "void main()\n"
                    "{\n"
                    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                    "}\0");

    if (!fshader.compile_success()) {
        cout << "ERROR [fragment shader compilation failed]\n"
             << fshader.log_info() << endl;
    }

    ShaderProgram shader_program{};
    shader_program.attach_shader(std::move(vshader));
    shader_program.attach_shader(std::move(fshader));
    shader_program.link();

    if (!shader_program.link_success()) {
        cout << "ERROR [shader proram link failed]\n"
             << shader_program.log_info() << endl;
    }

    // vshader.~VertexShader();
    // fshader.~FragmentShader();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // clean up glfw
    glfwTerminate();

    return 0;
}
