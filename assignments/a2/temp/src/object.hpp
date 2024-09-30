/*
 * Description: SimpleDraw data structures and operation function header
 * Author: HBF
 * Version: 2021-08-24
 */

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <GL/gl.h>

typedef enum type {
	RECTANGLE = 1,
	CIRCLE
} TYPE;

// shape object: rectangle or circle
typedef struct shape {
	TYPE type;
	int x1, y1, x2, y2; // rectangle: (x1, y1) and (x2, y2) are opposite corner.
	                    // circle: (x1, y1) is center, (x2, y2) is any point on the circle
	                    // a better design is to (x1, y1) as center, and x2 as radius.
	GLfloat fr, fg, fb; // fill color
	GLfloat sr, sg, sb; // stroke color
	GLint swidth;       // stroke width
} SHAPE;

// node structure of doubly linked list
typedef struct node {
   SHAPE *object;
   struct node *prev, *next;
} NODE;

// Doubly linked list
typedef struct objectlist {
	NODE *start, *end;
} LIST;

void insert(LIST *list, SHAPE *object);
void deleteNode(LIST *list, NODE **selectp);
void clearList(LIST *list);
void drawShape(SHAPE *object);
void drawShapeHighLight(SHAPE *object);
void drawList(LIST *list);


void setPixel(GLint x, GLint y);
void circlePlotPoints(const GLint& xc, const GLint& yc, const GLint& x, const GLint& y);
void circleMidpoint(GLint x1, GLint y1, GLint x2, GLint y2);
void circlePlotPointsFill(GLint x1, GLint y1, GLint x, GLint y);
void circleMidpointFill(GLint x1, GLint y1, GLint x2, GLint y2);
void plotObject(GLint x1, GLint y1, GLint x2, GLint y2, GLfloat r1, GLfloat g1, GLfloat b1, GLint t1, GLint s1);

#endif

