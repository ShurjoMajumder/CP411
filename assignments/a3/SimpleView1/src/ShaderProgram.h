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
public:
    /**
     * Loads a shader.
     *
     * @param vs_path Path to the vertex shader source.
     * @param fs_path Path to the fragment shader source.
     */
    ShaderProgram(const std::string& vs_path, const std::string &fs_path);

    /**
     * Frees all memory associated with the shader.
     */
    ~ShaderProgram();

    /**
     * Makes this program instance the active shader program.
     */
    void Use() const;

    explicit operator GLuint () const;

private:
    volatile GLuint m_id = 0;
};

#endif //SHAPES_SHADERPROGRAM_H
