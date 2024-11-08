//
// Created by shurj on 25-Oct-2024.
//

#include "Cube.h"

std::shared_ptr<Graphics::CanvasItem> Cube::Create() {
    auto program = std::make_shared<Graphics::ShaderProgram>("test.vert", "test.frag");

    std::vector<Graphics::CanvasItemVertex> vertices = {
            // front face
            {{+0.5, -0.5, +0.5}, {1, 0, 0, 1}},  // 0: front-top-right
            {{-0.5, -0.5, +0.5}, {1, 0, 0, 1}},  // 1: front-top-left
            {{-0.5, -0.5, -0.5}, {1, 0, 0, 1}},  // 2: front-bottom-left
            {{+0.5, -0.5, -0.5}, {1, 0, 0, 1}},  // 3: front-bottom-right
            // top face
            {{+0.5, +0.5, +0.5}, {0, 1, 0, 1}},  // 4: top-back-right
            {{-0.5, +0.5, +0.5}, {0, 1, 0, 1}},  // 5: top-back-left
            {{-0.5, -0.5, +0.5}, {0, 1, 0, 1}},  // 6: top-front-left
            {{+0.5, -0.5, +0.5}, {0, 1, 0, 1}},  // 7: top-front-right
            // right face
            {{+0.5, +0.5, +0.5}, {0, 0, 1, 1}},  // 8: right-top-back
            {{+0.5, -0.5, +0.5}, {0, 0, 1, 1}},  // 9: right-top-front
            {{+0.5, -0.5, -0.5}, {0, 0, 1, 1}},  // 10: right-bottom-front
            {{+0.5, +0.5, -0.5}, {0, 0, 1, 1}},  // 11: right-bottom-back
            // left face
            {{-0.5, -0.5, +0.5}, {1, 1, 0, 1}},  // 12: left-top-front
            {{-0.5, +0.5, +0.5}, {1, 1, 0, 1}},  // 13: left-top-back
            {{-0.5, +0.5, -0.5}, {1, 1, 0, 1}},  // 14: left-bottom-back
            {{-0.5, -0.5, -0.5}, {1, 1, 0, 1}},  // 15: left-bottom-front
            // bottom face
            {{-0.5, +0.5, -0.5}, {0, 1, 1, 1}},  // 16: bottom-back-left
            {{+0.5, +0.5, -0.5}, {0, 1, 1, 1}},  // 17: bottom-back-right
            {{+0.5, -0.5, -0.5}, {0, 1, 1, 1}},  // 18: bottom-front-right
            {{-0.5, -0.5, -0.5}, {0, 1, 1, 1}},  // 19: bottom-front-left
            // back face
            {{-0.5, +0.5, +0.5}, {1, 0, 1, 1}},  // 20: back-top-left
            {{+0.5, +0.5, +0.5}, {1, 0, 1, 1}},  // 21: back-top-right
            {{+0.5, +0.5, -0.5}, {1, 0, 1, 1}},  // 22: back-bottom-right
            {{-0.5, +0.5, -0.5}, {1, 0, 1, 1}},  // 23: back-bottom-left
    };

    std::vector<GLuint> elements = {
            // front face
            0, 1, 2, 2, 3, 0,
            // top face
            4, 5, 6, 6, 7, 4,
            // right face
            8, 9, 10, 10, 11, 8,
            // left face
            12, 13, 14, 14, 15, 12,
            // bottom face
            16, 17, 18, 18, 19, 16,
            // back face
            20, 21, 22, 22, 23, 20
    };

    std::vector<Graphics::VertexAttribFormat> attribs = {
            Graphics::VertexAttribFormat{
                    glGetAttribLocation(program->GetId(), "position"),
                    3,
                    GL_FLOAT,
                    GL_FALSE,
                    sizeof(Graphics::CanvasItemVertex),
                    0
            },
            Graphics::VertexAttribFormat{
                    glGetAttribLocation(program->GetId(), "i_vertexColor"),
                    4,
                    GL_FLOAT,
                    GL_FALSE,
                    sizeof(Graphics::CanvasItemVertex),
                    (void*)(sizeof(glm::vec3))
            }
    };

    auto mesh =  std::make_shared<Graphics::Mesh<Graphics::CanvasItemVertex>>(vertices, elements, attribs);

    return std::make_shared<Graphics::CanvasItem>(mesh, program);
}
