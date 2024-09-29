/*
 * Description: This illustrates how to read image data from frame buffer,
 * and how to save image to bitmap file, and load and display bitmap.
 * Compile: g++ opengl_bitmap.cpp -lfreeglut -lopengl32 -lglu32
 * Run: a.exe
 * HBF
*/

#include <GL/glut.h>
#include <cstdio>

#define GL_BGR_EXT 0x80E0
#define GL_BGR     0x80E0
#define GL_BGRA    0x80E1

GLsizei winWidth = 300, winHeight = 300;      // Initial Display-window size.
GLfloat red = 1.0, green = 1.0, blue = 1.0;   // Initial color values.
GLenum renderingMode = GL_SMOOTH;             // Initial fill method.
int drawOption = 0;               // option to draw triangle, or bitmap
GLubyte *bits = nullptr;             // pointers to image data (array of bytes)
BITMAPINFOHEADER *bih = nullptr;     // point to bitmap information header object

void init (void);
int saveBitmap(const char *ptrcFileName, int nX, int nY, int nWidth, int nHeight);
int loadBitmap(const char *ptrcFileName, GLubyte **bitsp, BITMAPINFOHEADER **bihp);
void drawTriangle(void);
void drawBitmap(GLubyte *bits, BITMAPINFOHEADER *bih);
void display();
void reshapeFcn(GLint newWidth, GLint newHeight);
void mainMenu(GLint renderingOption);
void colorSubMenu(GLint colorOption);

void init (void)
{
    glClearColor (0.0, 0.0, 0.0, 1.0);
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, 300.0, 0.0, 300.0);
}

int saveBitmap(const char *ptrcFileName, int nX, int nY, int nWidth, int nHeight)
{
    FILE *fp = fopen(ptrcFileName, "wb");
    if (fp == NULL) {
        printf("fp == NULL \n");
        return 0;
    }
    printf("step 1\n");

    // allocate memory to store image data
    int bitsize = nWidth*nHeight*3 +  ((3*nWidth)%4 == 0 ? 0 : (4-(3*nWidth)%4)*nHeight);

    printf("step 0 %d\n", bitsize);

    unsigned char *ptrImage = (unsigned char*) malloc(bitsize);
    if (ptrImage == nullptr) {
        printf("ptrImage == NULL \n");
        fclose(fp);
        return 0;
    }

    //read pixels from frame buffer, byte order is BGR
    glReadPixels(nX, nY, nWidth, nHeight, GL_BGR, GL_UNSIGNED_BYTE, ptrImage);

    printf("step 1\n");
    // clean memory buffer of bitmap header and information header
    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;
    memset(&bfh, 0, sizeof(bfh));
    memset(&bih, 0, sizeof(bih));

    // set the bitmap header with the give parameters
    bfh.bfType = 0x4d42; // 'MB'
    bfh.bfSize = sizeof(bfh) + sizeof(bih) + bitsize;
    bfh.bfOffBits = sizeof(bfh) + sizeof(bih);

    // set bitmap information header
    bih.biSize = sizeof(bih);
    bih.biWidth = nWidth + nWidth%4;
    bih.biHeight = nHeight;
    bih.biPlanes = 1;
    bih.biBitCount = 24;
    bih.biSizeImage = bitsize;

    printf("step 2\n");
    // write to file
    if (fwrite(&bfh, sizeof(bfh), 1, fp) < 1) {
        free(ptrImage);
        fclose(fp);
        return 0;
    };

    if (fwrite(&bih, sizeof(bih), 1, fp)<1) {
        free(ptrImage);
        fclose(fp);
        return 0;
    }

    printf("step 3\n");

    if ( fwrite(ptrImage, 1, bitsize, fp) < bitsize ) {
        free(ptrImage);
        fclose(fp);
        return 0;
    }

    fclose(fp);
    free(ptrImage);

    printf("end of save bitmap\n");
    return 1;
}

int loadBitmap(const char *filename, GLubyte **bitsp, BITMAPINFOHEADER **bihp)
{
    FILE *fp;      /* Open file pointer */
    GLubyte *bits; /* Bitmap pixel bits */
    int bitsize;   /* Size of bitmap */
    int infosize;  /* Size of header bihrmation */

    BITMAPFILEHEADER bfh; /* Bitmap file header */
    BITMAPINFOHEADER *bih;  /*  bitmap bih header */

    /* Open the binary file to read useing "rb" mode */
    if ((fp = fopen(filename, "rb")) == NULL) return 0;

    /* Read the file header */
    if (fread(&bfh, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
        fclose(fp);
        return 0;
    }

    if (bfh.bfType !=  0x4d42) { // 'MB') /* Check for BM reversed... */
        fclose(fp);
        return 0;
    }

    printf("bfh.bfSize =======%d\n", bfh.bfSize);

    /* Read bitmap info header */
    if ((bih = (BITMAPINFOHEADER *) malloc(sizeof(BITMAPINFOHEADER))) == NULL) {
        fclose(fp);
        return 0;
    }

    //if (fread(&info, 1, infosize, fp) < infosize) { // failed to read in info header
    if (fread(bih, sizeof(BITMAPINFOHEADER), 1, fp) < 1) { // failed to read in info header
        fclose(fp);
        return 0;
    }

    bitsize = bih->biWidth*bih->biHeight*3 + ((3*bih->biWidth)%4 == 0 ? 0 : (4-(3*bih->biWidth)%4)*bih->biHeight);

    //	int bitsize = nWidth*nHeight*3 +  ((3*nWidth)%4 == 0) ? 0 : (4-(3*nWidth)%4)*nHeight;


    printf("bih.biWidth=======%d\n", bih->biWidth);
    printf("bih->biHeight=======%d\n", bih->biHeight);
    printf("bitsize =======%d\n", bitsize);

    if ((bits = (GLubyte *) malloc(bitsize)) == NULL) {
        fclose(fp);
        return 0;
    }

    if (fread(bits, 1, bitsize, fp) < bitsize) {  // failed to image data in info header
        free(bih);
        free(bits);
        fclose(fp);
        return 0;
    }

    fclose(fp);

    // The following reverses ordering of colors,  e.g. (bgr -> rgb), use GL_RGB in glDrawPixels
    /*
    GLubyte temp;
    for (int i = 0; i < bitsize; i += 3) {
        temp = bits[i];
        bits[i] = bits[i + 2];
        bits[i + 2] = temp;
    }
    */


// We can also modify a pixel values at position (x, y), e.g. the following changes the rectangle of size 50 at  (0, 0) to blue color, in case of RGB ordering.

    /*
       int x = 0, y = 0, w = 50; k;
       for (int j=0; j<s; j++) {
           for (int h=0; h<w; h++) {
              k = ((y+h)*bih->biHeight + x+j)*3;
              bits[k] = 0;
              bits[k+1] = 0;
              bits[k+2] = 255;
           }
        }
   */

    // the following outputs bits and bih.
    *bitsp = bits; // output t
    *bihp = bih;
    printf("end of loading\n");
    return 1;
}

void drawTriangle()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glShadeModel(renderingMode); //  Set fill method for triangle.

    glBegin(GL_TRIANGLES);
    glColor3f(red, green, blue); //  Set color for first two vertices.
    glVertex2i(280, 20);
    glVertex2i(160, 280);
    if(renderingMode == GL_SMOOTH)
        glColor3f(1.0, 0.0, 0.0);  // Set color of last vertex to red.
    glVertex2i(20, 100);
    glEnd( );

    glFlush( );

}

void drawBitmap(GLubyte *bits, BITMAPINFOHEADER *bih)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glRasterPos2f(0, 0);
    glDrawPixels(bih->biWidth, bih->biHeight, GL_BGR, GL_UNSIGNED_BYTE, bits);
    //glDrawPixels(bih->biWidth, bih->biHeight, GL_RGB, GL_UNSIGNED_BYTE, bits);
}

void display(void)
{
    if (drawOption == 0) {
        drawTriangle();
    }
    else if (drawOption == 1) {
        drawBitmap(bits, bih);  // draw bitmap data once
        drawOption = 2;
    }
}

void reshapeFcn(GLint newWidth, GLint newHeight)
{
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    gluOrtho2D(0.0, newWidth, 0.0, newHeight);
}

void mainMenu(GLint renderingOption)
{
    switch(renderingOption) {
        case 1:
            drawOption = 0;
            break;
        case 2:
            drawOption = 0;
            saveBitmap("output.bmp", 0, 0, winWidth, winHeight);
            break;
        case 3:

            if (bits != NULL) {
                free(bits);
                bits = NULL;
            }

            if (bih != NULL ) {
                free(bih);
                bih = NULL;
            }
            loadBitmap("output.bmp", &bits, &bih);
            drawOption = 1;
            display();

            break;
        case 4:
            if (bits) free(bits);
            if (bih) free(bih);
            exit(1);
            break;

    }
    glutPostRedisplay( );
}

void colorSubMenu(GLint colorOption)
{
    drawOption = 0;
    switch(colorOption) {
        case 1:
        {red = 0.0;  green = 0.0;  blue = 1.0;}
            break;
        case 2:
        {red = 0.0;  green = 1.0;  blue = 0.0;}
            break;
        case 3:
        {red = 1.0;  green = 1.0;  blue = 1.0;}
    }
    glutPostRedisplay( );
}


int main(int argc, char **argv)
{
    GLint subMenu;             //  Identifier for submenu.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Bitmap I/O");
    init( );
    glutDisplayFunc(display);

    subMenu = glutCreateMenu(colorSubMenu);
    glutAddMenuEntry("Blue", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("White", 3);

    glutCreateMenu(mainMenu);
    glutAddMenuEntry("Draw triangle", 1);
    glutAddMenuEntry("Save to output.bmp", 2);
    glutAddMenuEntry("Load from output.bmp", 3);
    glutAddSubMenu("Color", subMenu);
    glutAddMenuEntry("Quit", 4);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutReshapeFunc(reshapeFcn);
    glutMainLoop( );

}