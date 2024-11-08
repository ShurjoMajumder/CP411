//
// Created by shurj on 25-Oct-2024.
//

#include "House.h"

using namespace Graphics;

std::shared_ptr<CanvasItem> House::Create() {
    auto program = std::make_shared<ShaderProgram>("test.vert", "test.frag");

    std::vector<CanvasItemVertex> vertices = {
            // roof
            // front
            {{+0.0, +0.0, +0.5}, {1, 1, 0, 1}},  // 0: top
            {{-0.5, -0.5, +0.0}, {1, 1, 0, 1}},  // 1: front-bottom-right
            {{+0.5, -0.5, +0.0}, {1, 1, 0, 1}},  // 2: front-bottom-left
            // right
            {{+0.0, +0.0, +0.5}, {0, 1, 1, 1}},  // 3: top
            {{+0.5, -0.5, +0.0}, {0, 1, 1, 1}},  // 4: right-front
            {{+0.5, +0.5, +0.0}, {0, 1, 1, 1}},  // 5: right-back
            // left
            {{+0.0, +0.0, +0.5}, {1, 0, 1, 1}},  // 6: top
            {{-0.5, +0.5, +0.0}, {1, 0, 1, 1}},  // 7: left-back
            {{-0.5, -0.5, +0.0}, {1, 0, 1, 1}},  // 8: left-front
            // back
            {{+0.0, +0.0, +0.5}, {1, 1, 1, 1}},  // 9: top
            {{+0.5, +0.5, +0.0}, {1, 1, 1, 1}},  // 10: back-bottom-left
            {{-0.5, +0.5, +0.0}, {1, 1, 1, 1}},  // 11: back-bottom-right
            // base
            {{-0.5, +0.5, +0.0}, {1, 0, 1, 1}},  // 12: back-bottom-left
            {{+0.5, +0.5, +0.0}, {1, 0, 1, 1}},  // 13: back-bottom-right
            {{+0.5, -0.5, +0.0}, {1, 0, 1, 1}},  // 14: front-bottom-right
            {{-0.5, -0.5, +0.0}, {1, 0, 1, 1}},  // 15: front-bottom-left

            // walls/floor
            // front wall
            {{+0.5, -0.5, +0.0}, {1, 0, 0, 1}},  // 16: front-top-right
            {{-0.5, -0.5, +0.0}, {1, 0, 0, 1}},  // 17: front-top-left
            {{-0.5, -0.5, -0.5}, {1, 0, 0, 1}},  // 18: front-bottom-left
            {{+0.5, -0.5, -0.5}, {1, 0, 0, 1}},  // 19: front-bottom-right
            // right wall
            {{+0.5, +0.5, +0.0}, {0, 0, 1, 1}},  // 20: right-top-back
            {{+0.5, -0.5, +0.0}, {0, 0, 1, 1}},  // 21: right-top-front
            {{+0.5, -0.5, -0.5}, {0, 0, 1, 1}},  // 22: right-bottom-front
            {{+0.5, +0.5, -0.5}, {0, 0, 1, 1}},  // 23: right-bottom-back
            // left wall
            {{-0.5, -0.5, +0.0}, {1, 1, 0, 1}},  // 24: left-top-front
            {{-0.5, +0.5, +0.0}, {1, 1, 0, 1}},  // 25: left-top-back
            {{-0.5, +0.5, -0.5}, {1, 1, 0, 1}},  // 26: left-bottom-back
            {{-0.5, -0.5, -0.5}, {1, 1, 0, 1}},  // 27: left-bottom-front
            // floor
            {{-0.5, +0.5, -0.5}, {0, 1, 1, 1}},  // 28: bottom-back-left
            {{+0.5, +0.5, -0.5}, {0, 1, 1, 1}},  // 29: bottom-back-right
            {{+0.5, -0.5, -0.5}, {0, 1, 1, 1}},  // 30: bottom-front-right
            {{-0.5, -0.5, -0.5}, {0, 1, 1, 1}},  // 31: bottom-front-left
            // back wall
            {{-0.5, +0.5, +0.0}, {1, 0, 1, 1}},  // 32: back-top-left
            {{+0.5, +0.5, +0.0}, {1, 0, 1, 1}},  // 33: back-top-right
            {{+0.5, +0.5, -0.5}, {1, 0, 1, 1}},  // 34: back-bottom-right
            {{-0.5, +0.5, -0.5}, {1, 0, 1, 1}},  // 35: back-bottom-left
    };

    std::vector<GLuint> elements = {
            // roof
            // front
            0, 1, 2,
            // right
            3, 4, 5,
            // left
            6, 7, 8,
            // back
            9, 10, 11,
            // base
            12, 13, 14, 14, 15, 12,

            // walls & floor
            // front wall
            16, 17, 18, 18, 19, 16,
            // right wall
            20, 21, 22, 22, 23, 20,
            // left wall
            24, 25, 26, 26, 27, 24,
            // floor
            28, 29, 30, 30, 31, 28,
            // back wall
            32, 33, 34, 34, 35, 32
    };

    std::vector<VertexAttribFormat> attribs = {
            VertexAttribFormat{
                    glGetAttribLocation(program->GetId(), "position"),
                    3,
                    GL_FLOAT,
                    GL_FALSE,
                    sizeof(CanvasItemVertex),
                    0
            },
            VertexAttribFormat{
                    glGetAttribLocation(program->GetId(), "i_vertexColor"),
                    4,
                    GL_FLOAT,
                    GL_FALSE,
                    sizeof(CanvasItemVertex),
                    (void*)(sizeof(glm::vec3))
            }
    };

    auto mesh =  std::make_shared<Mesh<CanvasItemVertex>>(vertices, elements, attribs);

    return std::make_shared<CanvasItem>(mesh, program);
}
