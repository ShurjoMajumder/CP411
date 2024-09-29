//
// Created by shurj on 28-Sep-2024.
//

#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>

#include "sd_callbacks.h"
#include "ShaderProgram.h"


void SimpleDraw::init() {
    std::shared_ptr<ShaderProgram> shaderProgram = ShaderProgram::LoadShader("./triangle_basic.vert", "./triangle_fragment.frag");

    unsigned int VAO, VBO;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    shaderProgram->Use();
    glBindVertexArray(VAO);
}

void SimpleDraw::display_callback() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glutSwapBuffers();
}

void SimpleDraw::mouse_callback() {

}

void SimpleDraw::main_menu_callback() {

}

void SimpleDraw::cleanup() {
}
