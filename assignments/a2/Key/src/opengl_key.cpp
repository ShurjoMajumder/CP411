/*
 * Example from textbook chapter 20
 * Compile: g++ opengl_key.cpp -lfreeglut -lopengl32 -lglu32
 * Run: a.exe
*/

#include <GL/glut.h>

GLsizei winWidth = 400, winHeight = 300;   // Initial display-window size.
void init(void)
{
    glClearColor(0.0, 0.0, 1.0, 1.0);        // Set display-window color to blue.
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void displayFcn(void)
{
    glClear(GL_COLOR_BUFFER_BIT);          //  Clear display window.
    glColor3f(1.0, 0.0, 0.0);              //  Set point color to red.
    glPointSize(3.0);                      //  Set point size to 3.0.
}

void winReshapeFcn(int newWidth, int newHeight)
{
    /*  Reset viewport and projection parameters  */
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    gluOrtho2D(0.0, newWidth, 0.0, newHeight);

    /*  Reset display-window size parameters.  */
    winWidth  = newWidth;
    winHeight = newHeight;
}

void plotPoint(GLint x, GLint y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd( );
}

/*  Move cursor while pressing c key enables freehand curve drawing.  */
void curveDrawing(GLubyte curvePlotKey, GLint xMouse, GLint yMouse)
{
    GLint x = xMouse;
    GLint y = winHeight - yMouse;

    switch(curvePlotKey)
    {
        case 'c':
            plotPoint(x, y);
            break;
        default:
            break;
    }

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Keyboard Example");
    init( );
    glutDisplayFunc(displayFcn);
    glutReshapeFunc(winReshapeFcn);
    glutKeyboardFunc(curveDrawing);
    glutMainLoop( );
}