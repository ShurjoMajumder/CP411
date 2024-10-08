//
// Created by shurj on 08-Oct-2024.
//

#ifndef A3_OBJECTMESH_H
#define A3_OBJECTMESH_H

#include <vector>
#include <GL/glew.h>

#include "ShaderProgram.h"

struct VertexAttribFormat {
    GLuint AttribLocation;
    GLint AttribSize;
    GLenum AttribType;
    GLboolean AttribNormalized;
    GLsizei AttribStride;
    void* AttribOffset;
};

template<typename Vertex>
class ObjectMesh {
public:
    ObjectMesh(std::vector<Vertex> &vertices, std::vector<GLuint> &elements, const ShaderProgram& program, std::vector<VertexAttribFormat> &attribFormatArray);
    ~ObjectMesh();

private:
    GLuint m_VAO{}, m_VBO{}, m_EBO{};
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_elements;
    ShaderProgram m_shaderProgram;
};

#endif //A3_OBJECTMESH_H
