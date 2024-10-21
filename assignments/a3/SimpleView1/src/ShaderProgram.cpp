//
// Created by shurj on 28-Sep-2024.
//

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

ShaderProgram::ShaderProgram() = default;

ShaderProgram::ShaderProgram(const ShaderProgram &program) {
    m_id = program.m_id;
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(m_id);  // delete this program when finished.
}

ShaderProgram &ShaderProgram::operator=(const ShaderProgram& other) = default;

ShaderProgram::operator GLuint() const {
    return m_id;
}

void ShaderProgram::Use() const {
    glUseProgram(m_id);
}

void ShaderProgram::SetUniform(const std::string &name, const glm::mat4x4 &value) const {
    GLint uniformLocation = glGetUniformLocation(m_id, name.c_str());
    glProgramUniformMatrix4fv(m_id, uniformLocation, 1, GL_FALSE, &value[0][0]);
}

void ShaderProgram::SetUniform(const std::string &name, const glm::mat4x4 &&value) const {
    GLint uniformLocation = glGetUniformLocation(m_id, name.c_str());
    glProgramUniformMatrix4fv(m_id, uniformLocation, 1, GL_FALSE, &value[0][0]);
}

void ShaderProgram::SetUniform(const std::string &name, GLfloat value) const {
    GLint uniformLocation = glGetUniformLocation(m_id, name.c_str());
    glProgramUniform1f(m_id, uniformLocation, value);
}

GLuint ShaderProgram::GetId() const {
    return m_id;
}

