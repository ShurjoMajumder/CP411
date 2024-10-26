//
// Created by shurj on 08-Oct-2024.
//

#ifndef A3_OBJECTMESH_H
#define A3_OBJECTMESH_H

#include <vector>
#include <GL/glew.h>

#include "ShaderProgram.h"

struct VertexAttribFormat {
    GLint AttribLocation;
    GLint AttribSize;
    GLenum AttribType;
    GLboolean AttribNormalized;
    GLsizei AttribStride;
    void* AttribOffset;
};


/**
 * A class which abstracts a VAO with associated mesh data. Doesn't store transformation information.
 *
 * @tparam Vertex The vertex type used by the object.
 */
template<typename Vertex>
class ObjectMesh {
public:

    ObjectMesh() {
        m_vertexCount = 0;
        m_elementCount = 0;
        m_VAO = 0;
        m_VBO = 0;
        m_EBO = 0;
    }

    /**
     * Creates an object mesh using the provided data. The mesh contains a set of OpenGL buffers and associated data.
     *
     * @param vertices Vertex data.
     * @param elements Elements.
     * @param program Shader program.
     * @param attribFormatArray Vertex attribute specifications.
     */
    ObjectMesh(std::vector<Vertex> &vertices, std::vector<GLuint> &elements,
               std::vector<VertexAttribFormat> &attribFormatArray) {
        m_vertexCount = vertices.size();
        std::cout << "Vertex count: " << m_vertexCount << '\n';

        m_elementCount = (GLsizei) elements.size();
        std::cout << "Element count: " << m_elementCount << '\n';

        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertexCount, vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_elementCount, elements.data(), GL_STATIC_DRAW);

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

        glBindVertexArray(0);
    }

    ObjectMesh(const ObjectMesh<Vertex> &mesh) {
        m_VAO = mesh.m_VAO;
        m_VBO = mesh.m_VBO;
        m_EBO = mesh.m_EBO;
        m_vertexCount = mesh.m_vertexCount;
        m_elementCount = mesh.m_elementCount;
    }

    ObjectMesh(ObjectMesh<Vertex> &&mesh)  noexcept {
        m_VAO = mesh.m_VAO;
        m_VBO = mesh.m_VBO;
        m_EBO = mesh.m_EBO;
        mesh.m_VAO = 0;
        mesh.m_VBO = 0;
        mesh.m_EBO = 0;
        m_vertexCount = mesh.m_vertexCount;
        m_elementCount = mesh.m_elementCount;
    }

    /**
     * Destroy the mesh and associated buffers, and shaders.
     */
    ~ObjectMesh() {
        std::cout << "Mesh destructor called!" << std::endl;
        if (m_VAO == 0 || m_VBO == 0 || m_EBO == 0) {
            return;
        }

        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
        glDeleteVertexArrays(1, &m_VAO);
    }

    ObjectMesh& operator=(const ObjectMesh<Vertex> &mesh)  noexcept = default;

    ObjectMesh& operator=(ObjectMesh<Vertex> &&other)  noexcept {
        *this = std::move(other);
        return *this;
    }

    void Draw() {
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, m_elementCount, GL_UNSIGNED_INT, nullptr);
    }


private:
    GLuint m_VAO{}, m_VBO{}, m_EBO{};
    GLsizei m_vertexCount{}, m_elementCount{};
};

#endif //A3_OBJECTMESH_H
