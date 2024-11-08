//
// Created by shurj on 07-Nov-2024.
//

#include "Axes.h"

std::shared_ptr<Graphics::CanvasItem> Axes::Create() {
    auto program = std::make_shared<Graphics::ShaderProgram>("test.vert", "test.frag");

    std::vector<Graphics::CanvasItemVertex> vertices = {
            {{10, 0, 0}, {1, 0, 0, 1}},
            {{-10, 0, 0}, {1, 0, 0, 1}},
            {{0, 10, 0}, {0, 1, 0, 1}},
            {{0, -10, 0}, {0, 1, 0, 1}},
            {{0, 0, 10}, {0, 0, 1, 1}},
            {{0, 0, -10}, {0, 0, 1, 1}}
    };

    std::vector<GLuint> elements = {
            0, 1,  // x-axis
            2, 3,  // y-axis
            4, 5   // z-axis
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
