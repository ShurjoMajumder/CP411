/*
 * Description: testing on 2D transformations
 * compile: g++ opengl_transform2d.cpp -lopengl32 -lglu32 -lfreeglut
 * Run: a.exe
 * HBF
 */
#include <GL/glut.h>
#include <cstring>

GLsizei winWidth = 400, winHeight = 300;

GLint transType = 1;
char str[100];

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);  /* Set display-window background color to yellow */
    glMatrixMode(GL_PROJECTION);       /* Set projection parameters */
    gluOrtho2D(-winWidth/2, winWidth/2, -winHeight/2, winHeight/2); /* Set clipping window */
}

void lineSegment(int x1, int y1, int x2, int y2) {
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
}

void polygon(void) {
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, 30.0);
    glVertex2f(40.0, 30.0);
    glVertex2f(60.0, 15);
    glVertex2f(40.0, 0.0);
    glEnd();
}

void message(char str[]) {
    glRasterPos2f(0, -50);
    int i = 0;
    while (str[i]) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
        i++;
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear display window.
    GLfloat xf, yf, sx, sy;
    glColor3f(0.0, 0.0, 0.0);
    lineSegment(0, -winHeight / 2, 0, winHeight / 2);
    lineSegment(-winWidth / 2, 0, winWidth / 2, 0);
    glColor3f(1.0, 0.0, 0.0);
    polygon(); /* polygon at original position */


    // 2D translate
    if (transType == 1) {
        strcpy(str, "Translation");
        message(str);
        glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glTranslatef(100.0, 100.0, 0.0);
        polygon();
        glPopMatrix();
    }

    // 2D rotation
    else if (transType == 2) {
        strcpy(str, "Rotation");
        message(str);
        glPushMatrix();
        glColor3f(0.0, 0.0, 1.0);
        glRotatef(45.0, 0.0, 0.0, 1.0);
        polygon();
        glPopMatrix();
    }

    // 2D scale
    else if (transType == 3) {
        strcpy(str, "Scaling");
        message(str);
        glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glScalef(1.5, 2.0, 1.0);
        polygon();
        glPopMatrix();
    }

    // Composite transformation
    else if (transType == 4) {
        strcpy(str, "Scale->Translate");
        message(str);
        glPushMatrix();
        glTranslatef(-100.0, -100.0, 0.0);  // step 2
        glScalef(1.5, 2.0, 1.0);           //  step 1
        glColor3f(1.0, 0.0, 0.0);
        polygon();
        glPopMatrix();
    }

        // Scaling relative to a fix point
    else if (transType == 5) {
        strcpy(str, "Relative scaling");
        message(str);
        xf = 50;
        yf = 50;
        sx = 0.5;
        sy = 0.5;
        glPushMatrix();
        glTranslatef(xf, yf, 0.0);   // step 3
        glScalef(sx, sy, 1);         // step 2
        glTranslatef(-xf, -yf, 0);   // step 1
        glColor3f(0.0, 1.0, 0.0);
        polygon();
        glPopMatrix();
    }

        //Rotation about a pivot point
    else if (transType == 6) {
        strcpy(str, "Relative rotation");
        message(str);
        xf = -50;
        yf = -50;
        glColor3f(0.0, 0.0, 0.0);
        glPushMatrix();
        glTranslatef(xf, yf, 0.0);     // step.3
        glRotatef(90., 0.0, 0.0, 1.0); // step.2
        glTranslatef(-xf, -yf, 0);     // step.1
        glColor3f(0.0, 1.0, 0.0);
        polygon();
        glPopMatrix();
    }

        // reflect w.r.t. x-axis
    else if (transType == 7) {
        strcpy(str, "Reflect");
        message(str);
        glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        glScalef(1, -1, 1);
        glColor3f(0.0, 1.0, 0.0);
        polygon();
        glPopMatrix();
    }

    glFlush();
}

void mainMenuFcn(GLint menuOption) {
    transType = menuOption;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(400, 300);
    glutCreateWindow("2D transformations");

    init();
    glutDisplayFunc(display);         /* Send graphics to display window. */

    glutCreateMenu(mainMenuFcn);      /* Create main pop-up menu */
    glutAddMenuEntry("Translate", 1);
    glutAddMenuEntry("Rotate", 2);
    glutAddMenuEntry("Scale", 3);
    glutAddMenuEntry("Composite transformation", 4);
    glutAddMenuEntry("Scale w.r.t. fixed point", 5);
    glutAddMenuEntry("Rotation about a pivot point", 6);
    glutAddMenuEntry("Reflect w.r.t. x-axis", 7);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
}
