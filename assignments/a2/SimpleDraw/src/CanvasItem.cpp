//
// Created by shurj on 29-Sep-2024.
//

#include <iostream>
#include "CanvasItem.h"


glm::vec3 CanvasItem::s_quadVertices[] = {
        glm::vec3( 0.5f,  0.5f, 0.0f),
        glm::vec3( 0.5f, -0.5f, 0.0f),
        glm::vec3(-0.5f, -0.5f, 0.0f),
        glm::vec3(-0.5f,  0.5f, 0.0f),
};

GLuint CanvasItem::s_quadIndices[] = {
        0, 1, 3,  // first triangle (top right)
        1, 2, 3   // second triangle (bottom left)
};

CanvasItem::CanvasItem(
        glm::vec3 position, glm::vec4 fillColor, glm::vec4 strokeColor,
        const std::string &vertexShaderPath,
        const std::string &fragmentShaderPath) {
    m_shaderProgram = ShaderProgram::LoadShader(vertexShaderPath, fragmentShaderPath);
    m_position = position;
    m_fillColor = fillColor;
    m_strokeColor = strokeColor;

    std::array<Vertex, 4> vertices{};
    for (int i = 0; i < 4; ++i) {

        vertices[i] = {
                s_quadVertices[i], fillColor, strokeColor
        };
    }

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(s_quadIndices), s_quadIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(VERTEX_POSITION_LOC, VERTEX_POSITION_SIZE, GL_FLOAT, GL_FALSE, VERTEX_STRIDE, VERTEX_POSITION_OFFSET);
    glEnableVertexAttribArray(VERTEX_POSITION_LOC);

    glVertexAttribPointer(VERTEX_FILL_LOC, VERTEX_FILL_SIZE, GL_FLOAT, GL_FALSE, VERTEX_STRIDE, VERTEX_FILL_OFFSET);
    glEnableVertexAttribArray(VERTEX_FILL_LOC);

    glVertexAttribPointer(VERTEX_STROKE_LOC, VERTEX_STROKE_SIZE, GL_FLOAT, GL_FALSE, VERTEX_STRIDE, VERTEX_STROKE_OFFSET);
    glEnableVertexAttribArray(VERTEX_STROKE_LOC);
}

void CanvasItem::Draw() {
    m_shaderProgram->Use();
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);  // unbind
}
