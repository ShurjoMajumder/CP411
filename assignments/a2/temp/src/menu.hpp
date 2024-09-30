/*
 * Description: SimpleDraw menu function header
 * Author: HBF
 * Version: 2021-08-24
 */

#ifndef MENU_HPP_
#define MENU_HPP_

#include <GL/glut.h>

void clear();

void addMenu();

void mainMenuFcn(GLint menuOption);

void drawMenuFcn(GLint typeOption);

void fileMenuFcn(GLint fileOption);

void editMenuFcn(GLint editOption);

void styleSubMenu(GLint styleOption);

void fillColorMenuFcn(GLint colorOption);

void strokeColorMenuFcn(GLint colorOption);

void strokeWidthMenuFcn(GLint width);

void dataviewSubMenu(GLint option);

#endif /* MENU_HPP_ */
