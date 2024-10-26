//
// Created by shurj on 15-Oct-2024.
//

#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <memory>

#include "Shape.h"
#include "Camera.h"
#include "World.h"
#include "Menu.h"


void Init() {
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glClearColor(0,  0, 0, 0);
}

int main(int argc, char** argv) {
    int winWidth = 800, winHeight = 800;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("SimpleView1");
    Init();
    Menu();
    glutDisplayFunc(DisplayCallback);
    glutMotionFunc(MouseMotionCallback);
    glutMouseFunc(MouseActionCallback);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();

    return 0;
}
