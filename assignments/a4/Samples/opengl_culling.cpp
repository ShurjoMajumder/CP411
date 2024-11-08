/*
 * Description: testing on 3D hidden surface removal and animations
 * compile: g++ opengl_culling.cpp -lfreeglut -lopengl32 -lglu32
 * Run: a.exe  right clicking mouse to bring the menu
 * HBF
 */

#include <GL/glut.h>
#include <time.h>


GLfloat v[8][3] = { /* declare array and initialize vertices of cube */{ -1.0, -1.0, 1.0 }, { -1.0, -1.0, -1.0 }, { -1.0, 1.0, -1.0 },
                                                                       { -1.0, 1.0, 1.0 }, { 1.0, -1.0, 1.0 }, { 1.0, -1.0, -1.0 }, { 1.0, 1.0,
                                                                                     -1.0 }, { 1.0, 1.0, 1.0 }
};

GLint face[6][4] = { /* Vertex indices for the 6 faces */
        { 0, 3, 2, 1 }, { 2, 3, 7, 6 }, { 4, 5, 6, 7 }, { 0, 1, 5, 4 }, { 1, 2, 6, 5 },
        { 3, 0, 4, 7 } };

GLfloat color[6][3] = { /* colors of faces by face index */
        { 1.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 1.0, 0.0 },  { 1.0, 1.0, 0.0 }, {
          1.0, 0.0, 1.0 }, { 0.0, 1.0, 1.0 } };

void drawCube(void) {
    int i;
    for (i = 0; i < 6; i++) {
        glColor3f(color[i][0], color[i][1], color[i][2]);
        glBegin(GL_POLYGON);
        glVertex3fv(v[face[i][0]]);
        glVertex3fv(v[face[i][1]]);
        glVertex3fv(v[face[i][2]]);
        glVertex3fv(v[face[i][3]]);
        glEnd();
    }
}


void lineSegment(float x1, float y1, float z1, float x2, float y2, float z2) {
    glBegin(GL_LINES);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y2, z2);
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // draw WCS axis
    glColor3f(1.0, 0.0, 0.0);
    lineSegment(-2, 0, 0, 4, 0, 0); /* x-axis in red */
    glColor3f(0.0, 1.0, 0.0);
    lineSegment(0, -2, 0, 0, 4, 0); /* y-axis in green */
    glColor3f(0.0, 0.0, 1.0);
    lineSegment(0, 0, -2, 0, 0, 4); /* z-axis in blue */

    glColor3f(1.0, 1.0, 1.0);
    drawCube();
    glutSwapBuffers();
}

void move1(void){
    glRotatef(0.1, 0, 0, 1);
    glutPostRedisplay();
}


GLfloat theta;
int oldTime, newTime;
void  move2() {
    GLfloat speed = 0.1;
    newTime = clock();
    theta = (newTime - oldTime) * speed;
    oldTime = newTime;
    glRotatef(theta, 0, 0, 1);
    glutPostRedisplay();
}

/*
 * using glutTimerFunc for next
 */
int startTimer = 0;
void move3(int speed)
{
    if (startTimer) {
        glRotatef(0.1*speed, 0, 0, 1);
        glutTimerFunc(5, move3, 1);
    }
    glutPostRedisplay();
}


void init(void) {
    /* Setup 3D view */
    glMatrixMode(GL_PROJECTION);
    gluPerspective(40.0, /* field of view in degree */
                   1.0, /* aspect ratio */
                   1.0, /* Z near */
                   20.0 /* Z far */
    );
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(6.0, 3.0, 10.0, /* eye is at (0,0,5) */
              0.0, 0.0, 0.0, /* center is at (0,0,0) */
              0.0, 0.0, 1.0  /* up is in positive Y direction */
    );
}

void mainMenu(GLint option) {
    switch (option) {
        case 1:
            glDisable(GL_CULL_FACE);
            glDisable(GL_DEPTH_TEST);
            break;
        case 2:
            glEnable(GL_CULL_FACE);
            glDisable(GL_DEPTH_TEST);
            break;
        case 3:
            glDisable(GL_CULL_FACE);
            glEnable(GL_DEPTH_TEST);
            break;
        case 4:
            glEnable(GL_CULL_FACE);
            glEnable(GL_DEPTH_TEST);
            break;
        case 5:
            glutIdleFunc(move1);
            break;
        case 6:
            oldTime = clock();
            glutIdleFunc(move2);
            break;
        case 7:
            startTimer = 1;
            glutTimerFunc(10, move3, 1);
            break;
        case 8:
            glutIdleFunc(NULL);
            startTimer = 0;
            break;
        case 9:
            exit(0);
            break;
    }

    glutPostRedisplay();

}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );

    glutInitWindowPosition(50, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Hidden surface removal and animation (HBF)");
    init();
    glutDisplayFunc(display);

    glutCreateMenu(mainMenu);
    glutAddMenuEntry("Without culling", 1);
    glutAddMenuEntry("Use OpenGL backface API", 2);
    glutAddMenuEntry("Use Depth Buffer API", 3);
    glutAddMenuEntry("Use both API", 4);
    glutAddMenuEntry("Animate using idle time", 5);
    glutAddMenuEntry("Animate using system time", 6);
    glutAddMenuEntry("Animate using glut timer", 7);
    glutAddMenuEntry("Stop animation", 8);
    glutAddMenuEntry("Quit", 9);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
}