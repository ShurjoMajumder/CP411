//
// Created by shurj on 25-Oct-2024.
//

#include "House.h"

std::shared_ptr<Shape> House::Create() {
    auto program = std::make_shared<ShaderProgram>("test.vert", "test.frag");

    std::vector<ShapeVertex> vertices = {
            // roof
            {{+0, +0, +1}, {1, 1, 1, 1}},  // 0: top
            {{-1, -1, +0}, {1, 0, 0, 1}},  // 1: front-bottom-left
            {{+1, -1, +0}, {0, 1, 0, 1}},  // 2: front-bottom-right
            {{-1, +1, +0}, {0, 0, 1, 1}},  // 3: back-bottom-left
            {{+1, +1, +0}, {1, 0, 1, 1}},  // 4: back-bottom-right

            // walls & floor
            {{-0.8, -0.8, +0}, {1, 0, 0, 1}},  //  5: front-top-left
            {{+0.8, -0.8, +0}, {0, 1, 0, 1}},  //  6: front-top-right
            {{-0.8, -0.8, -1}, {0, 0, 1, 1}},  //  7: front-bottom-left
            {{+0.8, -0.8, -1}, {1, 0, 1, 1}},  //  8: front-bottom-right
            {{-0.8, +0.8, +0}, {0, 0, 1, 1}},  //  9: back-top-left
            {{+0.8, +0.8, +0}, {0, 1, 0, 1}},  // 10: back-top-right
            {{-0.8, +0.8, -1}, {1, 0, 0, 1}},  // 11: back-bottom-left
            {{+0.8, +0.8, -1}, {0, 1, 1, 1}}   // 12: back-bottom-right
    };

    std::vector<GLuint> elements = {
            // roof front
            0, 1, 2,
            // roof left
            0, 1, 3,
            // roof right
            0, 2, 4,
            // roof back
            0, 3, 4,
            // roof base
            1, 2, 4, 1, 3, 4,
            // front wall
            5, 7, 8, 5, 6, 8,
            // left wall
            5, 7, 11, 5, 9, 11,
            // right wall
            6, 8, 12, 6, 10, 12,
            // back wall
            9, 10, 12, 9, 11, 12,
            // floor
            11, 7, 8, 11, 12, 8
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
