#include "window.hpp"
#include <GLFW/glfw3.h>
#include <exception>

namespace util {

class glfw {
    public:
    class init_failed: public std::exception {
        public:
        const char *what() const noexcept override {
            return "failed initialize glfw library";
        }
    };

    // initialize's glfw library
    glfw() {
        if (!glfwInit()) throw init_failed{};
    }

    ~glfw() { glfwTerminate(); }

    static inline void set_error_callback(void (*callback)(int, const char *)) {
        glfwSetErrorCallback(callback);
    }

    window::builder window_builder() { return window::builder{}; }
};

} // namespace util
