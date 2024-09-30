/*
 * Description: implementation of SimpleDraw file functions
 * Author: HBF
 * Version: 2021-08-24
 */

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#include "file.hpp"
#include "object.hpp"

#define MaxNumObj 100
#define GL_BGR_EXT 0x80E0
#define GL_BGR     0x80E0
#define GL_BGRA    0x80E1

extern LIST objlist;

int saveBitmap(const char *ptrcFileName, int nX, int nY, int nWidth,
		int nHeight) {

  // your implementation
	return 1;
}

int saveSVG(const char *filename, int winWidth, int winHeight) {
	FILE *fp = fopen(filename, "w");
	if (fp == NULL)  return EXIT_FAILURE;

	char line[255];
	int width, height; //store calculated height and width

	//write header data for SVG
	sprintf(line, "<?xml version=\"1.0\" standalone=\"no\"?>\n");
	fputs(line, fp);
	sprintf(line, "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n");
	fputs(line, fp);
	sprintf(line, "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
	fputs(line, fp);
	sprintf(line,
			"<svg width=\"%d\" height=\"%d\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n",
			winWidth, winHeight);
	fputs(line, fp);

	// traverse through object list and a line for each object
	// need to convert the rectangal/circle data to SVG rect/circle data


    // your implementation

	sprintf(line, "</svg>\n");
	fputs(line, fp);
	fclose(fp);

	return EXIT_SUCCESS;
}

int openSVG(const char *filename) {
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) return EXIT_FAILURE;

	int lineLength = 255;
	char line[lineLength];
	int x1, y1, w, h, fr, fg, fb, sr, sg, sb, sw; // variables to hold scan values

	// read line by line, if it is line of rect/circle element, retrieve the attribute values and convert them to
	// object values and create object and insert to the object list.

	while ( fgets(line, lineLength, fp)) {
		//printf("%s\n", buffer);
		SHAPE *shapeObj;
		if (line[0] == '<' && line[1] == 'r' ) { // rectangle
			sscanf(line,
					"<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"rgb(%d,%d,%d)\" stroke=\"rgb(%d,%d,%d)\" stroke-width=\"%d\"/>",
					&x1, &y1, &w, &h, &fr, &fg, &fb, &sr, &sg, &sb, &sw);

			shapeObj = (SHAPE*) malloc(sizeof(SHAPE));
			shapeObj->type = RECTANGLE;
			shapeObj->x1 = x1;
			shapeObj->y1 = y1;
			shapeObj->x2 = x1 + w;
			shapeObj->y2 = y1 + h;
			shapeObj->fr = fr / 255;
			shapeObj->fg = fg / 255;
			shapeObj->fb = fb / 255;
			shapeObj->sr = sr / 255;
			shapeObj->sg = sg / 255;
			shapeObj->sb = sb / 255;
			shapeObj->swidth = sw;
			insert(&objlist, shapeObj);

		} else if (line[0] == '<' && line[1] == 'c' )  {
			// ....
		}
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

