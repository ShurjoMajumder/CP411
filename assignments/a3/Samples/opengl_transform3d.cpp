/*
 * Description: testing on 3D transformations
 * compile: g++ opengl_transform3d.cpp -lfreeglut -lopengl32 -lglu32
 * Run: a.exe
 * HBF
 */

#include <GL/glut.h>

int transType = 0;
int objType = 1;
char str[100];

GLfloat v[8][3] = { /* declare array and initialize vertices of cube */
        {-1.0, -1.0,  1.0  },
        {-1.0, -1.0, -1.0 },
        {-1.0,  1.0, -1.0 },
        {-1.0,  1.0,  1.0 },
        {1.0,  -1.0,  1.0  },
        {1.0,  -1.0, -1.0 },
        {1.0,   1.0, -1.0 },
        {1.0,   1.0,  1.0 }
};

GLint faces[6][4] = { /* Vertex indices for the 6 faces */
        { 0, 3, 2, 1 },
        { 2, 3, 7, 6 },
        { 4, 5, 6, 7 },
        { 0, 1, 5, 4 },
        { 1, 2, 6, 5 },
        { 3, 0, 4, 7 }
};

void drawCube1() {
    int i;
    for (i = 0; i < 6; i++) {
        glBegin(GL_LINE_LOOP);
        glVertex3fv(v[faces[i][0]]);
        glVertex3fv(v[faces[i][1]]);
        glVertex3fv(v[faces[i][2]]);
        glVertex3fv(v[faces[i][3]]);
        glEnd();
    }
}


GLfloat vertex[8][3];  /* declare array data structure, set data in init() */
GLint face[6][4];
void drawCube2(void) {
    int i;
    for (i = 0; i < 6; i++) {
        glBegin(GL_LINE_LOOP);
        glVertex3fv(vertex[face[i][0]]);
        glVertex3fv(vertex[face[i][1]]);
        glVertex3fv(vertex[face[i][2]]);
        glVertex3fv(vertex[face[i][3]]);
        glEnd();
    }
}


void drawObject(void) {
    switch (objType) {
        case 1:
            drawCube1();
            break;
        case 2:
            drawCube1();
            break;
        case 3:
            glutWireCube(1);
            break;

        case 4:
            glutWireSphere(1,16,16);
            break;
        case 5:
            glutWireCone(1,1,16,16);
            break;

        case 6:
            glutWireTorus(0.2,0.8,16,16);
            break;
        case 7:
            glutWireTeapot(1);
            break;
    }
}

void lineSegment(float x1, float y1, float z1, float x2, float y2, float z2) {
    glBegin(GL_LINES);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y2, z2);
    glEnd();
}

void message(char str[]) {
    glRasterPos2f(-5, -6);
    int i = 0;
    while (str[i]) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
        i++;
    }
}

void DisplayCallback(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // draw WCS axis
    glColor3f(1.0, 0.0, 0.0);
    lineSegment(-2, 0, 0, 2, 0, 0); /* x-axis in red */
    glColor3f(0.0, 1.0, 0.0);
    lineSegment(0, -2, 0, 0, 2, 0); /* y-axis in green */
    glColor3f(0.0, 0.0, 1.0);
    lineSegment(0, 0, -2, 0, 0, 2); /* z-axis in blue */

    glColor3f(1.0, 1.0, 1.0);
    drawObject();

    // 3D translate
    if (transType == 1) {
        strcpy(str, "Translation (2.0, 0.0, 0.0)");
        message(str);
        glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslatef(2.0, 0.0, 0.0);
        drawObject();
        glPopMatrix();
    }
        // 3D rotation
    else if (transType == 2) {
        strcpy(str, "Rotation 45 degree w.r.t. z-axis");
        message(str);
        glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glRotatef(45.0, 0.0, 0.0, 1.0);
        drawObject();
        glPopMatrix();
    }

        // 3D scale
    else if (transType == 3) {
        strcpy(str, "Scaling(0.5, 0.5, 0.5)");
        message(str);
        glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glScalef(0.5, 0.5, 0.5);
        drawObject();
        glPopMatrix();
    }

        // Composite transformation
    else if (transType == 4) {
        strcpy(str, "Scale(1.5, 2.0, 1.0), Translate(-2.0, 0.0, 0.0)");
        message(str);
        glPushMatrix();
        glTranslatef(-2.0, 0.0, 0.0);  // step 2
        glScalef(1.5, 2.0, 1.0);        // step 1
        glColor3f(1.0, 1.0, 0.0);
        drawObject();
        glPopMatrix();
    }

    glutSwapBuffers();
}

void init(void) {
    vertex[0][0] = -1; vertex[0][1] = -1; vertex[0][2] = -1;
    vertex[1][0] = -1; vertex[1][1] = 1;  vertex[1][2] = -1;
    vertex[2][0] = 1;  vertex[2][1] = 1;  vertex[2][2] = -1;
    vertex[3][0] = 1;  vertex[3][1] = -1; vertex[3][2] = -1;
    vertex[4][0] = -1; vertex[4][1] = -1; vertex[4][2] = 1;
    vertex[5][0] = -1; vertex[5][1] = 1;  vertex[5][2] = 1;
    vertex[6][0] = 1;  vertex[6][1] = 1;  vertex[6][2] = 1;
    vertex[7][0] = 1;  vertex[7][1] = -1; vertex[7][2] = 1;

    face[0][0] = 0; face[0][1] = 1; face[0][2] = 2; face[0][3] = 3;
    face[1][0] = 7; face[1][1] = 6; face[1][2] = 5; face[1][3] = 4;
    face[2][0] = 0; face[2][1] = 4; face[2][2] = 5; face[2][3] = 1;
    face[3][0] = 2; face[3][1] = 1; face[3][2] = 5; face[3][3] = 6;
    face[4][0] = 3; face[4][1] = 2; face[4][2] = 6; face[4][3] = 7;
    face[5][0] = 0; face[5][1] = 3; face[5][2] = 7; face[5][3] = 4;


    /* Setup 3D view */
    glMatrixMode(GL_PROJECTION);
    gluPerspective(
            40.0,  /* field of view in degree */
            1.0,   /* aspect ratio */
            1.0,   /* Z near */
            20.0   /* Z far */
    );
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(6.0, 8.0, 10.0, /* eye is at (0,0,5) */
              0.0, 0.0, 0.0,  /* center is at (0,0,0) */
              0.0, 1.0, 0.0   /* up is in positive Y direction */
    );
}

void objSubMenu(GLint option) {
    objType = option;
    glutPostRedisplay();
}

void transSubMenu(GLint option) {
    transType = option;
    glutPostRedisplay();
}

void mainMenu(GLint option) {
    switch (option){
        case 1:
            exit(0);
            break;
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("3D transformations");
    init();
    glutDisplayFunc(DisplayCallback);

    GLint object_Menu = glutCreateMenu(objSubMenu);
    glutAddMenuEntry("Cube1", 1);
    glutAddMenuEntry("Cube2", 2);
    glutAddMenuEntry("Glut Cube", 3);
    glutAddMenuEntry("Glut Sphere", 4);
    glutAddMenuEntry("Glut Cone", 5);
    glutAddMenuEntry("Glut  Torus", 6);
    glutAddMenuEntry("Glut Teapot", 7);

    GLint trans_Menu = glutCreateMenu(transSubMenu);
    glutAddMenuEntry("Translate", 1);
    glutAddMenuEntry("Rotate", 2);
    glutAddMenuEntry("Scale", 3);
    glutAddMenuEntry("Composite transformation", 4);

    glutCreateMenu(mainMenu);
    glutAddSubMenu("Select Object", object_Menu);
    glutAddSubMenu("Select transType", trans_Menu);
    glutAddMenuEntry("Quit", 1);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
}