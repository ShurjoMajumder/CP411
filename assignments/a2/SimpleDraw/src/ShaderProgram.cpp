//
// Created by shurj on 28-Sep-2024.
//

#include <iostream>
#include "utils.h"
#include "ShaderProgram.h"


std::map<std::string, std::shared_ptr<ShaderProgram>> ShaderProgram::s_shaders = std::map<std::string, std::shared_ptr<ShaderProgram>>();

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

}


std::shared_ptr<ShaderProgram> ShaderProgram::LoadShader(const std::string &vs_path, const std::string &fs_path) {
    if (vs_path.empty() || fs_path.empty()) {
        std::cout << "vs_path or fs_path was empty.\n";
        exit(-1);
    }

    if (s_shaders.count(vs_path + fs_path) != 0) {
        return s_shaders.at(vs_path);
    }

    std::shared_ptr<ShaderProgram> shaderProgramPtr(new ShaderProgram(vs_path, fs_path));

    s_shaders.insert({vs_path + fs_path, shaderProgramPtr});

    return shaderProgramPtr;
}

void ShaderProgram::Cleanup() {
    for (auto &prog : s_shaders) {
        glDeleteProgram(prog.second->m_id);
    }
}

void ShaderProgram::Use() const {
    glUseProgram(m_id);
}
