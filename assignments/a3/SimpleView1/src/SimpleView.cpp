//
// Created by shurj on 15-Oct-2024.
//

#include <vector>
#include <glm/glm.hpp>
#include <iostream>

#include "ObjectMesh.h"

#include <GLFW/glfw3.h>
#include <glm/ext/scalar_constants.hpp>

struct QuadVertex {
    glm::vec3 position;
    glm::vec4 color;
};

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow *window);

int main(int argc, char **argv) {

    // initialize GLFW window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    glewInit();

    ShaderProgram program = ShaderProgram("./test.vert", "./test.frag");
    std::vector<QuadVertex> vertices = {
            // top left
            {glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec4(1.f, 0.0f, 0.0f, 1.0f)},
            // top right
            {glm::vec3(0.5f, 0.5f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)},
            // bottom right
            {glm::vec3(0.5f, -0.5f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)},
            // bottom left
            {glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)}
    };
    std::vector<GLuint> elements = {
            0, 3, 2,  // triangle 1
            0, 1, 2   // triangle 2
    };
    std::vector<VertexAttribFormat> attribs = {
            VertexAttribFormat{
                glGetAttribLocation(program.GetId(), "position"),
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(QuadVertex),
                nullptr
            },
            VertexAttribFormat{
                glGetAttribLocation(program.GetId(), "i_vertexColor"),
                4,
                GL_FLOAT,
                GL_FALSE,
                sizeof(QuadVertex),
                (void*)(sizeof(glm::vec3))
            }
    };
    auto mesh = new ObjectMesh<QuadVertex>(vertices, elements, program, attribs);

    glClearColor(0,  0, 0, 0);
    while (!glfwWindowShouldClose(window)) {
        ProcessInput(window);
        glClear(GL_COLOR_BUFFER_BIT);

        mesh->Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // cleanup.
    delete mesh;
    glfwTerminate();
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

