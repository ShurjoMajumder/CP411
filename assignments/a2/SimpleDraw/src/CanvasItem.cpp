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
                s_quadVertices[i].x, s_quadVertices[i].y, s_quadVertices[i].z,
                m_fillColor.r, m_fillColor.g, m_fillColor.b, m_fillColor.a,
                m_strokeColor.r, m_strokeColor.g, m_strokeColor.b, m_strokeColor.a
        };
    }
    for (auto item : vertices) {
        std::cout << item.x << ' ';
        std::cout << item.y << ' ';
        std::cout << item.z << ' ';
        std::cout << item.fill_r << ' ';
        std::cout << item.fill_b << ' ';
        std::cout << item.fill_g << ' ';
        std::cout << item.fill_a << ' ';
        std::cout << std::endl;
    }

    glGenVertexArrays(1, &m_VAO);
    std::cout << glGetError() << std::endl;
    glBindVertexArray(m_VAO);
    std::cout << glGetError() << std::endl;

    glGenBuffers(1, &m_VBO);
    std::cout << glGetError() << std::endl;
    glGenBuffers(1, &m_EBO);
    std::cout << glGetError() << std::endl;

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    std::cout << glGetError() << std::endl;
    glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(), GL_STATIC_DRAW);
    std::cout << glGetError() << std::endl;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(s_quadIndices), s_quadIndices, GL_STATIC_DRAW);
    std::cout << glGetError() << std::endl;

    glVertexAttribPointer(VERTEX_POSITION_LOC, VERTEX_POSITION_SIZE, GL_FLOAT, GL_FALSE, VERTEX_STRIDE, VERTEX_POSITION_OFFSET);
    std::cout << glGetError() << std::endl;
    glEnableVertexAttribArray(VERTEX_POSITION_LOC);
    std::cout << glGetError() << std::endl;

    glVertexAttribPointer(VERTEX_FILL_LOC, VERTEX_FILL_SIZE, GL_FLOAT, GL_FALSE, VERTEX_STRIDE, VERTEX_FILL_OFFSET);
    std::cout << glGetError() << std::endl;
    glEnableVertexAttribArray(VERTEX_FILL_LOC);
    std::cout << glGetError() << std::endl;

    glVertexAttribPointer(VERTEX_STROKE_LOC, VERTEX_STROKE_SIZE, GL_FLOAT, GL_FALSE, VERTEX_STRIDE, VERTEX_STROKE_OFFSET);
    std::cout << glGetError() << std::endl;
    glEnableVertexAttribArray(VERTEX_STROKE_LOC);
    std::cout << glGetError() << std::endl;
}

void CanvasItem::Draw() {
    m_shaderProgram->Use();
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
