//
// Created by shurj on 25-Oct-2024.
//

#include "Pyramid.h"

std::shared_ptr<Graphics::CanvasItem> Pyramid::Create() {
    auto program = std::make_shared<Graphics::ShaderProgram>("test.vert", "test.frag");

    std::vector<Graphics::CanvasItemVertex> vertices = {
            // front
            {{+0.0, +0.0, +0.5}, {1, 0, 0, 1}},  // 0: top
            {{-0.5, -0.5, -0.5}, {1, 0, 0, 1}},  // 1: front-bottom-right
            {{+0.5, -0.5, -0.5}, {1, 0, 0, 1}},  // 2: front-bottom-left
            // right
            {{+0.0, +0.0, +0.5}, {0, 1, 0, 1}},  // 3: top
            {{+0.5, -0.5, -0.5}, {0, 1, 0, 1}},  // 4: right-front
            {{+0.5, +0.5, -0.5}, {0, 1, 0, 1}},  // 5: right-back
            // left
            {{+0.0, +0.0, +0.5}, {0, 1, 0, 1}},  // 6: top
            {{-0.5, +0.5, -0.5}, {0, 1, 0, 1}},  // 7: left-back
            {{-0.5, -0.5, -0.5}, {0, 1, 0, 1}},  // 8: left-front
            // back
            {{+0.0, +0.0, +0.5}, {0, 0, 1, 1}},  // 9: top
            {{+0.5, +0.5, -0.5}, {0, 0, 1, 1}},  // 10: back-bottom-left
            {{-0.5, +0.5, -0.5}, {0, 0, 1, 1}},  // 11: back-bottom-right
            // base
            {{-0.5, +0.5, -0.5}, {1, 0, 1, 1}},  // 12: back-bottom-left
            {{+0.5, +0.5, -0.5}, {1, 0, 1, 1}},  // 13: back-bottom-right
            {{+0.5, -0.5, -0.5}, {1, 0, 1, 1}},  // 14: front-bottom-right
            {{-0.5, -0.5, -0.5}, {1, 0, 1, 1}},  // 15: front-bottom-left
    };

    std::vector<GLuint> elements = {
            // front
            0, 1, 2,
            // right
            3, 4, 5,
            // left
            6, 7, 8,
            // back
            9, 10, 11,
            // base
            12, 13, 14, 14, 15, 12
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
