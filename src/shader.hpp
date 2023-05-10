#pragma once

#include "glad/gl.h"
#include <iostream>
#include <string>

class Id {
    protected:
    unsigned int id;

    public:
    // Id() {}
    // Id(unsigned int id_t) : id(id_t) {}
    Id(unsigned int (*func)(void)) : id(func()) {}
    template <typename T> Id(unsigned int (*func)(T), T arg) : id(func(arg)) {}

    constexpr inline unsigned int get_id() { return this->id; }
};

class Shader: public Id {
    public:
    Shader(GLenum shader_type) : Id(glCreateShader, shader_type) {}
    virtual ~Shader() {
        // std::cout << "deleting shader" << std::endl;
        glDeleteShader(this->id);
    }

    constexpr inline unsigned int get_id() { return this->id; }

    inline void compile() { glCompileShader(this->id); }
    void compile(const char *);

    // return's true if compiled without errors
    inline bool compile_success() {
        int status;
        glGetShaderiv(id, GL_COMPILE_STATUS, &status);
        return status;
    }

    std::string log_info();
};

class VertexShader: public Shader {
    public:
    VertexShader() : Shader(GL_VERTEX_SHADER) {}
    // ~VertexShader() { std::cout << "deleting vertex shader" << std::endl; }
};

class FragmentShader: public Shader {
    public:
    FragmentShader() : Shader(GL_FRAGMENT_SHADER) {}
    // ~FragmentShader() { std::cout << "deleting fragment shader" << std::endl;
    // }
};

class ShaderProgram: public Id {
    public:
    ShaderProgram() : Id(glCreateProgram) {}
    ~ShaderProgram() { glDeleteProgram(this->id); }

    inline void attach_shader(Shader &&shader) {
        glAttachShader(this->id, shader.get_id());
    }

    inline void link() { glLinkProgram(this->id); }

    // return's true if shader proram linked without error
    inline bool link_success() {
        int success;
        glGetProgramiv(this->id, GL_LINK_STATUS, &success);
        return success;
    }

    std::string log_info();

    inline void use() { glUseProgram(this->id); }
};
