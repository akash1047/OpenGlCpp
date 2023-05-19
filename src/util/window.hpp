#pragma once

#include "monitor.hpp"
#include <GLFW/glfw3.h>
#include <cstdint>
#include <exception>
#include <optional>
#include <string>

namespace util {

class window {
    public:
    class builder {
        public:
        class size_not_set: public std::exception {
            public:
            const char *what() const noexcept override {
                return "window size is not provided\n"
                       "help: builder.set_size(uint16_t, uint16_t)";
            }
        };

        builder() = default;

        // create window
        inline window build() {
            GLFWwindow *glfw_window{nullptr};

            if (!this->width.has_value() || !this->height.has_value())
                throw size_not_set{};

            glfw_window = glfwCreateWindow(
                this->width.value(), this->height.value(),
                this->title.has_value() ? this->title.value().c_str() : nullptr,
                this->monitor.has_value() ? this->monitor.value().monitor_id()
                                          : nullptr,
                nullptr);

            return window{glfw_window};
        }

        inline builder &set_size(std::uint16_t width, std::uint16_t height) {
            this->width = width;
            this->height = height;
            return *this;
        }

        inline builder &set_title(std::string title) {
            this->title = std::move(title);
            return *this;
        }

        // window hints

        // set opengl context version
        inline builder &context_version(int major, int minor) {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
            return *this;
        }

        inline builder &context_version_major(int value) {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, value);
            return *this;
        }

        inline builder &context_version_minor(int value) {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, value);
            return *this;
        }

        // set opengl core profile
        inline builder &opengl_core() {
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            return *this;
        }

        // set opengl compatable profile
        inline builder &opengl_compat() {
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
            return *this;
        }

        private:
        std::optional<int> width{std::nullopt}, height{std::nullopt};
        std::optional<std::string> title{std::nullopt};
        std::optional<util::monitor> monitor{std::nullopt};
    };

    // swap buffers
    inline void swap_buffers() { glfwSwapBuffers(this->id); }

    // set window as opengl contex
    inline void make_context() { glfwMakeContextCurrent(this->id); }

    inline bool should_close() { return glfwWindowShouldClose(this->id); }

    inline void set_should_close(bool value) {
        glfwSetWindowShouldClose(this->id, value);
    }

    operator GLFWwindow *() { return this->id; }

    private:
    GLFWwindow *id{nullptr};

    window(GLFWwindow *glfw_window) : id(glfw_window) {}
};

} // namespace util
