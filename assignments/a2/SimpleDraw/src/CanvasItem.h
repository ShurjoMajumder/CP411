//
// Created by shurj on 29-Sep-2024.
//
#pragma once

#ifndef SHAPES_CANVASITEM_H
#define SHAPES_CANVASITEM_H

#include <vector>
#include <array>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderProgram.h"


struct Vertex {
    float x, y, z;
    float fill_r, fill_g, fill_b, fill_a;
    float stroke_r, stroke_g, stroke_b, stroke_a;
};


class CanvasItem {
private:
    const GLsizei VERTEX_STRIDE = sizeof(Vertex);

    const GLint VERTEX_POSITION_SIZE = 3;
    const GLint VERTEX_FILL_SIZE     = 4;
    const GLint VERTEX_STROKE_SIZE   = 4;

    const void* VERTEX_POSITION_OFFSET = (void*) nullptr;
    const void* VERTEX_FILL_OFFSET     = (void*) (3 * sizeof(float));
    const void* VERTEX_STROKE_OFFSET   = (void*) (7 * sizeof(float));

    const GLuint VERTEX_POSITION_LOC = 0;
    const GLuint VERTEX_FILL_LOC     = 1;
    const GLuint VERTEX_STROKE_LOC   = 2;

    static glm::vec3 s_quadVertices[];
    static GLuint s_quadIndices[];

    glm::vec3 m_position{};
    glm::vec4 m_fillColor{};
    glm::vec4 m_strokeColor{};
    GLuint m_VBO{}, m_EBO{}, m_VAO{};
    std::shared_ptr<ShaderProgram> m_shaderProgram;

public:
    CanvasItem(glm::vec3 position, glm::vec4 fillColor, glm::vec4 strokeColor, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

    void Draw();
};

#endif //SHAPES_CANVASITEM_H
