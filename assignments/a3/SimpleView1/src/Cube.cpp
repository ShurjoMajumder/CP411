//
// Created by shurj on 25-Oct-2024.
//

#include "Cube.h"

std::shared_ptr<Shape> Cube::Create() {
    auto program = std::make_shared<ShaderProgram>("test.vert", "test.frag");

    std::vector<ShapeVertex> vertices = {
            {{-1, -1, +1}, {1, 0, 0, 1}},  // 0: front-top-left
            {{+1, -1, +1}, {0, 0, 1, 1}},  // 1: front-top-right
            {{-1, -1, -1}, {0, 1, 0, 1}},  // 2: front-bottom-left
            {{+1, -1, -1}, {1, 1, 1, 1}},  // 3: front-bottom-right
            {{-1, +1, +1}, {1, 0, 0, 1}},  // 4: back-top-left
            {{+1, +1, +1}, {0, 0, 1, 1}},  // 5: back-top-right
            {{-1, +1, -1}, {0, 1, 0, 1}},  // 6: back-bottom-left
            {{+1, +1, -1}, {1, 1, 1, 1}},  // 7: back-bottom-right
    };

    std::vector<GLuint> elements = {
            // front face
            0, 2, 3, 0, 1, 3,
            // top face
            0, 1, 5, 0, 4, 5,
            // left face
            0, 4, 6, 0, 2, 6,
            // right face
            1, 3, 7, 1, 5, 7,
            // bottom face
            2, 3, 7, 2, 6, 7,
            // back face
            4, 5, 7, 4, 6, 7
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
