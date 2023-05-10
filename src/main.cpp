#define GLFW_INCLUDE_NONE
#include "glad/gl.h"
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
    gladLoaderLoadGL();

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

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // clean up glfw
    glfwTerminate();

    return 0;
}
