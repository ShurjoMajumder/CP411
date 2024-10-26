//
// Created by shurj on 25-Oct-2024.
//

#include "Pyramid.h"

std::shared_ptr<Shape> Pyramid::Create() {
    auto program = std::make_shared<ShaderProgram>("test.vert", "test.frag");

    std::vector<ShapeVertex> vertices = {
            {{+0, +0, +1}, {1, 1, 1, 1}},  // 0: top
            {{-1, -1, -1}, {1, 0, 0, 1}},  // 1: front-bottom-left
            {{+1, -1, -1}, {0, 1, 0, 1}},  // 2: front-bottom-right
            {{-1, +1, -1}, {0, 0, 1, 1}},  // 3: back-bottom-left
            {{+1, +1, -1}, {1, 0, 1, 1}},  // 4: back-bottom-right
    };

    std::vector<GLuint> elements = {
            // front
            0, 1, 2,
            // left
            0, 1, 3,
            // right
            0, 2, 4,
            // back
            0, 3, 4,
            // base
            1, 2, 4, 1, 3, 4
    };

    std::vector<VertexAttribFormat> attribs = {
            VertexAttribFormat{
                    glGetAttribLocation(program->GetId(), "position"),
                    3,
                    GL_FLOAT,
                    GL_FALSE,
                    sizeof(ShapeVertex),
                    0
            },
            VertexAttribFormat{
                    glGetAttribLocation(program->GetId(), "i_vertexColor"),
                    4,
                    GL_FLOAT,
                    GL_FALSE,
                    sizeof(ShapeVertex),
                    (void*)(sizeof(glm::vec3))
            }
    };

    auto mesh =  std::make_shared<ObjectMesh<ShapeVertex>>(vertices, elements, attribs);

    return std::make_shared<Shape>(mesh, program);
}
