#include "shader.hpp"
#include "glad/gl.h"
#include <memory>

void Shader::compile(const char *src) {
    glShaderSource(this->id, 1, &src, nullptr);
    glCompileShader(this->id);
}

std::string Shader::log_info() {
    int log_len;
    glGetShaderiv(this->id, GL_INFO_LOG_LENGTH, &log_len);

    std::unique_ptr<char[]> raw_info(new char[log_len + 1]);
    glGetShaderInfoLog(id, log_len + 1, nullptr, raw_info.get());

    return std::string(raw_info.get(), log_len);
}

std::string ShaderProgram::log_info() {
    int log_len;
    glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &log_len);

    std::unique_ptr<char[]> raw_info(new char[log_len + 1]);
    glGetProgramInfoLog(id, log_len + 1, nullptr, raw_info.get());

    return std::string(raw_info.get(), log_len);
}
