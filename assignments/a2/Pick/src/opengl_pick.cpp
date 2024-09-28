/*
 * Description: GUI, select object, example from textbook chapter 20
 * Compile: g++ opengl_pick.cpp -lfreeglut -lopengl32 -lglu32
 * Run: a.exe
*/

#include <GL/glut.h>
#include <cstdio>

const GLint pickBuffSize = 32;

/*  Set initial display-window size.  */
GLsizei winWidth = 400, winHeight = 400;

void init()
{
    /*  Set display-window color to white.  */
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

/*  Define 3 rectangles and associated IDs.  */
void rects(GLenum mode)
{
    if (mode == GL_SELECT) {
        glPushName(30);         //  Red rectangle.
    }

    glColor3f(1.0, 0.0, 0.0);
    glRecti(40, 130, 150, 260);

    if (mode == GL_SELECT) {
        glPushName(10);         //  Blue rectangle.
    }

    glColor3f(0.0, 0.0, 1.0);
    glRecti(150, 130, 260, 260);

    if (mode == GL_SELECT) {
        glPushName(20);         //  Green rectangle.
    }

    glColor3f(0.0, 1.0, 0.0);
    glRecti(40, 40, 260, 130);
}

/*  Print the contents of the pick buffer for each mouse selection.  */
void processPicks(GLint nPicks, GLuint pickBuffer[ ])
{
    GLint j, k;
    GLuint objID, *ptr;
    printf(" Number of objects picked = %d\n", nPicks);
    printf("\n");
    ptr = pickBuffer;

    /*  Output all items in each pick record.  */
    for (j = 0; j < nPicks; j++) {
        objID = *ptr;

        printf("   Stack position = %d\n", objID);
        ptr++;

        printf("   Min depth = %g,", float (*ptr/0x7fffffff));
        ptr++;

        printf("   Max depth = %g\n", float (*ptr/0x7fffffff));
        ptr++;

        printf("   Stack IDs are: \n");
        for (k = 0; k < objID; k++) {
            printf("   %d ",*ptr);
            ptr++;
        }
        printf("\n\n");
    }
}

void pickRects(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
    GLuint pickBuffer[pickBuffSize];
    GLint nPicks, vpArray [4];

    if (button != GLUT_LEFT_BUTTON || action != GLUT_DOWN)
        return;

    glSelectBuffer(pickBuffSize, pickBuffer);  //  Designate pick buffer.
    glRenderMode(GL_SELECT);             //  Activate picking operations.
    glInitNames( );                   //  Initialize the object-ID stack.

    /*  Save current viewing matrix.  */
    glMatrixMode(GL_PROJECTION);
    glPushMatrix( );
    glLoadIdentity( );

    /*  Obtain the parameters for the current viewport.  Set up
     *  a 5 x 5 pick window, and invert the input yMouse value
     *  using the height of the viewport, which is the fourth
     *  element of vpArray.
     */
    glGetIntegerv(GL_VIEWPORT, vpArray);
    gluPickMatrix(GLdouble (xMouse), GLdouble (vpArray [3] - yMouse),
                  5.0, 5.0, vpArray);

    gluOrtho2D(0.0, 300.0, 0.0, 300.0);
    rects(GL_SELECT);       // Process the rectangles in selection mode.

    /*  Restore original viewing matrix.  */
    glMatrixMode(GL_PROJECTION);
    glPopMatrix( );
    glFlush( );

    /*  Determine the number of picked objects and return to the
     *  normal rendering mode.
     */

    nPicks = glRenderMode(GL_RENDER);
    processPicks(nPicks, pickBuffer);  // Process picked objects.
    glutPostRedisplay( );
}

void displayFcn()
{
    glClear(GL_COLOR_BUFFER_BIT);
    rects(GL_RENDER);                // Display the rectangles.
    glFlush( );
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
    /*  Reset viewport and projection parameters.  */
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0.0, 300.0, 0.0, 300.0);
    glMatrixMode(GL_MODELVIEW);

    /* Reset display-window size parameters.  */
    winWidth  = newWidth;
    winHeight = newHeight;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Example Pick Program");
    init();
    glutDisplayFunc(displayFcn);
    glutReshapeFunc(winReshapeFcn);
    glutMouseFunc(pickRects);
    glutMainLoop();
    return 0;
}
