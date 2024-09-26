/*
 * Description: drawing primitives, point, line segment, polygon
 * Compile: gcc opengl_primitives.c -lfreeglut -lopengl32 -lglu32
 * Run:  a.exe
 * HBF
 */
#include <GL/glew.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0); // Set display-window background color to white
	glMatrixMode(GL_PROJECTION);       // Set projection parameters
	gluOrtho2D(0.0, 200.0, 0.0, 150.0); // Set view port, look down
	//gluOrtho2D(0.0, 200.0, 150.0, 0);     // Set view port, look up
}


void setPixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void lineSegment(int x1, int y1, int x2, int y2) {
	glBegin(GL_LINES);
	glVertex2i(x1, y1);       // Specify line-segment geometry
	glVertex2i(x2, y2);
	glEnd();
}

void polygon(void) {
	glBegin(GL_POLYGON);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 30.0);
	glVertex2f(40.0, 30.0);
	glVertex2f(60.0, 15);
	glVertex2f(40.0, 0.0);
	glEnd();
}

void message(int x, int y, char *msg) {
	glRasterPos2f(x, y);
	char *p = msg;
	while (*p) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
		p++;
	}
}

void Bresenham(int x1, int y1, int x2, int y2) {
	int Dx, Dy, x, y, s, p, c1, c2;
	if (x1 > x2) {
		x = x2;
		y = y2;
		x2 = x1;
		y2 = y1;
		x1 = x;
		y1 = y;
	} else {
		x = x1;
		y = y1;
	}

	Dx = x2 - x1;

	if (y1 > y2) {
		Dy = y1 - y2;
		s = -1;
		y2 = 2 * y1 - y2;

	} else {
		Dy = y2 - y1;
		s = 1;
	}

	setPixel(x, y);

	if (Dy <= Dx) {
		p = 2 * Dy - Dx;
		c1 = 2 * Dy;
		c2 = 2 * (Dy - Dx);

		while (x < x2) {

			x = x + 1;
			if (p < 0)
				p = p + c1;
			else {
				y = y + 1;
				p = p + c2;
			}
			if (s == 1)
				setPixel(x, y);
			else
				setPixel(x, y1 + y1 - y);
		}
	} else {
		p = 2 * Dx - Dy;
		c1 = 2 * Dx;
		c2 = 2 * (Dx - Dy);

		while (y < y2) {
			y = y + 1;
			if (p < 0)
				p = p + c1;
			else {
				x = x + 1;
				p = p + c2;
			}
			if (s == 1)
				setPixel(x, y);
			else
				setPixel(x, y1 + y1 - y);
		}
	}
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);  // Clear display window.
	glColor3f(1.0, 0.0, 0.0);      // Set drawing color to red
	glPointSize(3);
	setPixel(100, 75);             // Draw a point at (100, 75) 
	glColor3f(0.0, 1.0, 0.0);      // Set drawing color to green
	glPointSize(1);
	lineSegment(185, 15, 10, 145); // Draw a line segment from (185, 15) to (10, 145)
	//Bresenham(185, 15, 10, 145);
	glColor3f(0.0, 0.0, 1.0);      // Set drawing color to blue
	polygon();      // draw the polygon specified in polygon()
	glColor3f(0.0, 0.0, 0.0);      // Set drawing color to black
	char str[] = "OpenGL";
	message(50, 60, str);     // Draw string "OpenGL" at position (50, 60)
	glFlush();     // Process all OpenGL routines as quickly as possible.
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);                         // Initialize GLUT.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   // Set display mode.
	glutInitWindowPosition(50, 100);    // Set top-left display-window position.
	glutInitWindowSize(400, 300);        // Set display-window width and height.
	glutCreateWindow("OpenGL primitives");        // Create display window.
	init();                                 // Execute initialization procedure.
	glutDisplayFunc(display);          // Send graphics to display window.
	glutMainLoop();                   // Display everything and wait.
}
