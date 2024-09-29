// Author: Shurjo Majumder
// ID: 169035249
// Date: 28-Sep-2024

#include <GL/glew.h>
#include <GL/glut.h>

#include "sd_callbacks.h"


int main(int argc, char **argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 400);
    glutCreateWindow("SimpleDraw");

    glewInit();

    SimpleDraw::init();
    glutDisplayFunc(SimpleDraw::display_callback);
//    glutReshapeFunc(winReshapeFcn);
//    glutMouseFunc(mousePtPlot);
    glutMainLoop();

    SimpleDraw::cleanup();

    exit(0);
}
