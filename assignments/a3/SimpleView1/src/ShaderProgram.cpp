//
// Created by shurj on 28-Sep-2024.
//

#include <iostream>
#include "utils.h"
#include "ShaderProgram.h"


ShaderProgram::ShaderProgram(const std::string &vs_path, const std::string &fs_path) {
    std::string vertexShaderSource = ReadFile(vs_path);
    std::string fragmentShaderSource = ReadFile(fs_path);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char *vertexCData = vertexShaderSource.c_str();
    glShaderSource(vertexShader,
                   1,
                   &vertexCData,
                   nullptr
                   );
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragmentCData = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader,
                   1,
                   &fragmentCData,
                   nullptr
                   );
    glCompileShader(fragmentShader);

    m_id = glCreateProgram();

    glAttachShader(m_id, vertexShader);
    glAttachShader(m_id, fragmentShader);
    glLinkProgram(m_id);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void ShaderProgram::Use() const {
    glUseProgram(m_id);
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(m_id);  // delete this program when finished.
}

ShaderProgram::operator GLuint() const {
    return m_id;
}
