//
// Created by shurj on 28-Sep-2024.
//
#pragma once

#ifndef SHAPES_SHADERPROGRAM_H
#define SHAPES_SHADERPROGRAM_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <string>
#include <memory>
#include <glm/glm.hpp>
#include <iostream>

#include "utils.h"

class ShaderProgram {
public:

    /**
     * Default constructor.
     */
    ShaderProgram();

    /**
     * Loads a shader from specified paths.
     *
     * @param vs_path Path to the vertex shader source.
     * @param fs_path Path to the fragment shader source.
     */
    ShaderProgram(const std::string& vs_path, const std::string &fs_path);

    /**
     * Copy constructor.
     *
     * @param program
     */
    ShaderProgram(const ShaderProgram& program);

    /**
     * Move constructor.
     */
    ShaderProgram(ShaderProgram&& program) noexcept;

    /**
     * Frees all memory associated with the shader.
     */
    ~ShaderProgram();

    /**
     * Move assignment operator.
     *
     * @param other
     * @return
     */
    ShaderProgram& operator=(const ShaderProgram& other) noexcept;

    /**
     * Move assignment operator.
     *
     * @param other
     * @return
     */
    ShaderProgram& operator=(ShaderProgram&& other) noexcept;

    explicit operator GLuint () const;

    /**
     * Makes this program instance the active shader program.
     */
    void Use() const;

    GLuint GetId() const;

    /**
     * Sets the specified uniform to the specified value.
     *
     * @param name Name of the uniform.
     * @param value Value to set the uniform to.
     */
    void SetUniform(const std::string &name, const glm::mat4x4 &value) const;

    /**
     * Sets the specified uniform to the specified value.
     *
     * @param name Name of the uniform.
     * @param value Value to set the uniform to.
     */
    void SetUniform(const std::string &name, const glm::mat4x4 &&value) const;

    /**
     * Sets the specified uniform to the specified value.
     *
     * @param name Name of the uniform.
     * @param value Value to set the uniform to.
     */
    void SetUniform(const std::string &name, GLfloat value) const;

private:
    volatile GLuint m_id = 0;
};

#endif //SHAPES_SHADERPROGRAM_H
