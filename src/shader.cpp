#include <fstream>
#include <iostream>
#include <shader.hpp>
#include <sstream>
#include <string>
#include <format>

Shader::Shader(std::string path, GLenum shader_type)
    : m_type(shader_type), m_path(path) {
}

void Shader::CreateShader() {
    m_id = glCreateShader(m_type);
    std::ifstream stream(m_path);
    if (!stream) {
        std::cout << "FILE DOESN'T EXIST!\n";
    }

    std::string line;
    std::stringstream ss;
    while (std::getline(stream, line)) {
        ss << line << '\n';
    }

    m_source = ss.str();
    auto src = m_source.c_str();
    glShaderSource(m_id, 1, &src, nullptr);
}

void Shader::CompileShader() {
    glCompileShader(m_id);
    int success;
    char infoLog[512];
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(m_id, 512, NULL, infoLog);
        std::cerr << std::format("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n {}\n",infoLog);
    }
}

void Shader::DeleteShader() {
    glDeleteShader(m_id);
}

GLuint Shader::getId() const {
    return m_id;
}