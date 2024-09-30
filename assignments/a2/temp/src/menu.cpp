/*
 * Description: implementation of menu.hpp
 * Author: HBF
 * Version: 2021-08-24
 */

#include <GL/glut.h>
#include "menu.hpp"
#include "object.hpp"
#include "edit.hpp"
#include "file.hpp"

extern LIST objlist;
extern GLsizei winHeight, winWidth;
extern GLint oprMode, isInMenu, objType, isInMove;
extern NODE *selectNode;
extern GLint strokeWidth;
extern GLfloat fillred, fillgreen, fillblue, sred, sgreen, sblue;

void addMenu() {

	GLint drawMenuID, styleMenuID, fillColorMenuFcnID, strokefillColorMenuFcnID,
			strokeWidthMenuID, editMenuFcnID, fileMenuFcnID;

	drawMenuID = glutCreateMenu(drawMenuFcn);
	glutAddMenuEntry("Rectangle", 1);
	glutAddMenuEntry("Circle", 2);

	fillColorMenuFcnID = glutCreateMenu(fillColorMenuFcn);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Black", 4);
	glutAddMenuEntry("White", 5);

	strokefillColorMenuFcnID = glutCreateMenu(strokeColorMenuFcn);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Black", 4);
	glutAddMenuEntry("White", 5);

	strokeWidthMenuID = glutCreateMenu(strokeWidthMenuFcn);
	glutAddMenuEntry("1", 1);
	glutAddMenuEntry("2", 2);
	glutAddMenuEntry("3", 3);
	glutAddMenuEntry("4", 4);
	glutAddMenuEntry("5", 5);

	styleMenuID = glutCreateMenu(styleSubMenu);
	glutAddSubMenu("Fill Color", fillColorMenuFcnID);
	glutAddSubMenu("Stroke Color", strokefillColorMenuFcnID);
	glutAddSubMenu("Stroke Width", strokeWidthMenuID);

	editMenuFcnID = glutCreateMenu(editMenuFcn);
	glutAddMenuEntry("Select", 1);
	glutAddMenuEntry("Delete", 2);
	glutAddMenuEntry("Move front", 3);
	glutAddMenuEntry("Move back", 4);
	glutAddMenuEntry("Move around", 5);

	fileMenuFcnID = glutCreateMenu(fileMenuFcn);
	glutAddMenuEntry("Save SVG", 1);
	glutAddMenuEntry("Open SVG", 2);
	glutAddMenuEntry("Export Bitmap", 3);

	glutCreateMenu(mainMenuFcn); // Create main pop-up menu.
	glutAddMenuEntry("New", 1);
	glutAddSubMenu("Draw", drawMenuID);
	glutAddSubMenu("Style", styleMenuID);
	glutAddSubMenu("Edit", editMenuFcnID);
	glutAddSubMenu("File", fileMenuFcnID);
	glutAddMenuEntry("Quit", 2);
}

void clear() {
// ...
}

void mainMenuFcn(GLint menuOption) {
	isInMenu = 1;
	switch (menuOption) {
	case 1:
		clear();
		break;
	case 2:
		exit(0);
	}
	isInMenu = 0;
	glutPostRedisplay();
}

void drawMenuFcn(GLint typeOption) {
	oprMode = 0;
	isInMove = 0;
//
}

void fileMenuFcn(GLint fileOption) {
// ..
}

void editMenuFcn(GLint editOption) {
	oprMode = 1;
	isInMove = 0;
	// ...
	glutPostRedisplay();
}

void styleSubMenu(GLint styleOption) {
}

void fillColorMenuFcn(GLint colorOption) {
// ...
}

void strokeColorMenuFcn(GLint colorOption) {
// ...
}

void strokeWidthMenuFcn(GLint width) {
// ....
}

