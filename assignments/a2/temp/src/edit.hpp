/*
 * Description: SimpleDraw edit function header
 * Author: HBF
 * Version: 2021-08-24
 */

#ifndef EDIT_HPP_
#define EDIT_HPP_

#include <GL/glut.h>

extern int selected;
extern int selection;

GLint min(GLint x, GLint y);

GLint max(GLint x, GLint y);

NODE* select(GLint x, GLint y);

void Delete(NODE **pp);

void moveFront(NODE *p);

void moveBack(NODE *p);

void moveAround(NODE *p);

#endif /* EDIT_HPP_ */
