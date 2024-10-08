//
// Created by shurj on 08-Oct-2024.
//

#include "ObjectMesh.h"

template<typename Vertex>
ObjectMesh<Vertex>::ObjectMesh(
        std::vector<Vertex> &vertices,
        std::vector<GLuint> &elements,
        const ShaderProgram& program,
        std::vector<VertexAttribFormat> &attribFormatArray) {
    m_vertices = vertices;
    m_elements = elements;
    m_shaderProgram = program;

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(GLuint) * elements.size()), elements.data(), GL_STATIC_DRAW);

    for (auto &attrib : attribFormatArray) {
        glVertexAttribPointer(
                attrib.AttribLocation,
                attrib.AttribSize,
                attrib.AttribType,
                attrib.AttribNormalized,
                attrib.AttribStride,
                attrib.AttribOffset
                );
        glEnableVertexAttribArray(attrib.AttribLocation);
    }

}

template<typename Vertex>
ObjectMesh<Vertex>::~ObjectMesh() {
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
    glDeleteVertexArrays(1, &m_VAO);
}
