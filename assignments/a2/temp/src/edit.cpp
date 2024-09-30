/*
 * Description: implementation of edit.hpp
 * Author: HBF
 * Version: 2021-08-24
 */

#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include "object.hpp"

extern LIST objlist;

GLint min(GLint x, GLint y) {
	return x < y ? x : y;
}

GLint max(GLint x, GLint y) {
	if (x < y)
		return y;
	else
		return x;
}

NODE *select(GLint x, GLint y) {
	// your implementation
    // search the object that cover the clicking point staring

	return NULL;
}

void Delete(NODE **pp) {
	// your implementation
}

void moveFront(NODE *p) {
	// your implementation
}

void moveBack(NODE *p) {
	// your implementation
}

