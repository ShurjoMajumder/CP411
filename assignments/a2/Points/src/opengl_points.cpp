/*
 * Description: draw a sequence of points
 * Compile: g++ opengl_points.cpp -lfreeglut -lopengl32 -lglu32
 * Run: a.exe
 * HBF
*/

#include <GL/glut.h>
#define MAX 100

GLsizei winWidth = 400, winHeight = 300;
typedef struct dot {
	int x, y;
} point;
point list[MAX];
int end = -1;

void init()
{
  glClearColor(0.0, 0.0, 1.0, 1.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
  /*  Reset viewport and projection parameters  */
  glViewport(0, 0, newWidth, newHeight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity( );
  gluOrtho2D(0.0, newWidth, 0.0, newHeight);

  /*  Reset display-window size parameters.  */
  winWidth = newWidth;
  winHeight = newHeight;
}

void drawPoint(int x, int y)
{
  glBegin(GL_POINTS);
	 glVertex2i(x, y);
  glEnd();
}

void drawPoints(point a[], int n)
{
  glBegin(GL_POINTS);
     for (int i=0; i<=n; i++) glVertex2i(a[i].x, a[i].y);
  glEnd();
}

/*
Geometric Primitive Names and Meanings
Value  Meaning

GL_POINTS  Individual points

GL_LINES    Pairs of vertices interpreted as individual line segments

GL_LINE_STRIP Series of connected line segments

GL_LINE_LOOP Same as above, with a segment added between last and first vertices

GL_TRIANGLES Triples of vertices interpreted as triangles

GL_TRIANGLE_STRIP Linked strip of triangles

GL_TRIANGLE_FAN  Linked fan of triangles

GL_QUADS Quadruples of vertices interpreted as four-sided polygons

GL_QUAD_STRIP Linked strip of quadrilaterals

GL_POLYGON Boundary of a simple, convex polygon
*/


void mousePtPlot(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
  if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && end < MAX-1) {
	 end++;
	 list[end].x = xMouse;
	 list[end].y = winHeight - yMouse;
  }
  drawPoint(list[end].x, list[end].y);
  glFlush();
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 0.0, 0.0);
  glPointSize(3.0);
  drawPoints(list, end);
  glFlush();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowPosition(100, 100);
   glutInitWindowSize(winWidth, winHeight);
   glutCreateWindow("Draw points by mouse click");
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(winReshapeFcn);
   glutMouseFunc(mousePtPlot);
   glutMainLoop();


}
