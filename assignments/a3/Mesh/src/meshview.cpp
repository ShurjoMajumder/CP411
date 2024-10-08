/* 
 * Description: testing on mesh object model
 * Adopted from reference resource
 * HBF
 */
#include <GL/glut.h>
#include <string.h>

#include "Mesh.hpp"

GLsizei winWidth = 600, winHeight = 600;

GLint transType = 0;
char str[100];

Mesh * meshObj1, *meshObj2, *meshObj3, *selectObj;

void lineSegment(float x1, float y1, float z1, float x2, float y2, float z2) {
	glBegin(GL_LINES);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glEnd();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0);
	lineSegment(-2, 0, 0, 4, 0, 0); /* x-axis in red */
 	glColor3f(0.0, 1.0, 0.0);
	lineSegment(0, -2, 0, 0, 4, 0); /* y-axis in green */
	glColor3f(0.0, 0.0, 1.0);
	lineSegment(0, 0, -2, 0, 0, 4); /* z-axis in blue */

	glColor3f(1.0, 1.0, 0.0);
	if (selectObj) selectObj->draw();

	glFlush();
	glutSwapBuffers();
}


void init(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	/* Setup 3D view */
	glMatrixMode(GL_PROJECTION);
	gluPerspective(
	 40.0,  /* field of view in degree */
	 1.0,   /* aspect ratio */
	 1.0,   /* Z near */
	 15.0   /* Z far */
	);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(4.0, 6.0, 10.0, /* eye is at (0,0,5) */
	          0.0, 0.0, 0.0,  /* center is at (0,0,0) */
	          0.0, 0.0, 1.0   /* up is in positive Y direction */
    );

	meshObj1 = new Mesh("BARN.3VN");
	meshObj2 = new Mesh("BUCK.3VN");
	meshObj3 = new Mesh("PAWN.3VN");
	selectObj = meshObj1;
}

void renderFcn(GLint option) {
	switch (option) {
	case 1:
		selectObj->setRenderMode(Mesh::MODE_WIRE);
	  break;
	case 2:
		selectObj->setRenderMode(Mesh::MODE_SOLID);
		break;
	case 3:
		selectObj->setRenderMode(Mesh::MODE_WIRE_SOLID);
	   break;
	}
	glutPostRedisplay();
}

void mainMenuFcn(GLint option) {
	switch (option) {
	case 1:
		selectObj = meshObj1;
	  break;
	case 2:
		selectObj = meshObj2;
	  break;
	case 3:
		selectObj = meshObj3;
	  break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Mesh object model");

    init();
	glutDisplayFunc(display);         /* Send graphics to display window. */

    GLint renderMode_Menu = glutCreateMenu(renderFcn);
	glutAddMenuEntry("Wire", 1);
	glutAddMenuEntry("Solid", 2);
	glutAddMenuEntry("Wire & Solic", 3);

	glutCreateMenu(mainMenuFcn);      /* Create main pop-up menu */
	glutAddMenuEntry("Barn", 1);
	glutAddMenuEntry("Buck", 2);
	glutAddMenuEntry("Pawn", 3);
	glutAddSubMenu("Render mode", renderMode_Menu);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	glutMainLoop();
}
