//
// Created by shurj on 28-Sep-2024.
//

#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>

#include "sd_callbacks.h"
#include "CanvasItem.h"

static CanvasItem* testQuad = nullptr;

void SimpleDraw::init() {
    testQuad = new CanvasItem(
            glm::vec3(0, 0, 0),
            glm::vec4(1, 1, 1, 1),
            glm::vec4(1, 1, 1, 1),
            "general.vert",
            "quad.frag"
    );
}

void SimpleDraw::display_callback() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    testQuad->Draw();
    glutSwapBuffers();
    std::cout << "Frame drawn" << std::endl;
}

void SimpleDraw::mouse_callback() {

}

void SimpleDraw::main_menu_callback() {

}

void SimpleDraw::cleanup() {
    delete testQuad;
}
