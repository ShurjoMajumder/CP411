//
// Created by shurj on 28-Sep-2024.
//

#ifndef SHAPES_SHADERPROGRAM_H
#define SHAPES_SHADERPROGRAM_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <string>
#include <memory>
#include <map>


class ShaderProgram {
private:
    GLuint m_id{};
    std::string data;

    static std::map<std::string, std::shared_ptr<ShaderProgram>> s_shaders;  // path -> ShaderProgram

    /**
     *
     * @param vs_path
     * @param fs_path
     */
    ShaderProgram(const std::string& vs_path, const std::string &fs_path);

public:
    /**
     * Loads shader, returning a shared pointer to the program object. If the shader was already loaded previously,
     * the function fetches the pre-loaded shader.
     *
     * @param vs_path
     * @param fs_path
     * @return
     */
    static std::shared_ptr<ShaderProgram> LoadShader(const std::string& vs_path, const std::string &fs_path);

    /**
     * Cleans up all loaded shader programs.
     */
    static void Cleanup();

    /**
     * Makes this program instance the active shader program.
     */
    void Use() const;
};

#endif //SHAPES_SHADERPROGRAM_H
