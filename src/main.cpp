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
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, // bottom left
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    // clang-format on

    /* shader */

    VertexShader vshader{};
    vshader.compile("#version 330 core\n"
                    "layout (location = 0) in vec3 aPos;\n"
                    "void main()\n"
                    "{\n"
                    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
                    "}\0"

    );

    if (!vshader.compile_success()) {
        cout << "ERROR [vertex shader compilation failed]\n"
             << vshader.log_info() << endl;
    }

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
    // ---------------------------------------------

    unsigned int vbo;
    glGenBuffers(1, &vbo);

    unsigned int vao;
    glGenVertexArrays(1, &vao);

    unsigned int ebo;
    glGenBuffers(1, &ebo);

    // bind vertex array object first
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        shader_program.use();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    // clean up glfw
    glfwTerminate();

    return 0;
}
