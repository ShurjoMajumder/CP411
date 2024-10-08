#include "Mesh.hpp" // C++ file I/O

Mesh::Mesh() {
	numVerts = numFaces = numNorms = 0;
	pt = NULL;
	norm = NULL;
	face = NULL;
	lastVertUsed = lastNormUsed = lastFaceUsed = -1;
	scale = 1.0;
	mode = MODE_WIRE;
}

void Mesh::freeMesh() { // free up memory used by this mesh.
	delete[] pt; // release whole vertex list
	delete[] norm;
	for (int f = 0; f < numFaces; f++)
		delete[] face[f].vert; // delete the vert[] array of this face
	delete[] face;
}

int Mesh::isEmpty() {
	return (numVerts == 0) || (numFaces == 0) || (numNorms == 0);
}

void Mesh::makeEmpty() {
	numVerts = numFaces = numNorms = 0;
}

void Mesh::draw() {
	glPushMatrix();
	switch (mode) {
	case MODE_WIRE:
		drawEdges();
		break;
	case MODE_SOLID:
		drawFaces();
		break;
	default:
		drawFaces();
		drawEdges();
		break;
	}
	glPopMatrix();
}

Mesh::Mesh(string fname) { // read this file to build mesh
	numVerts = numFaces = numNorms = 0;
	pt = NULL;
	norm = NULL;
	face = NULL;
	lastVertUsed = lastNormUsed = lastFaceUsed = -1;
	scale = 1.0;
	mode = MODE_WIRE;
	readMesh(fname);
}

Vector Mesh::newell4(int indx[]) { /* return the normalized normal to face with vertices
 pt[indx[0]],...,pt[indx[3]]. i.e. indx[] contains the four indices
 into the vertex list to be used in the Newell calculation */
	Vector m;
	for (int i = 0; i < 4; i++) {
		int next = (i == 3) ? 0 : i + 1; // which index is next?
		int f = indx[i], n = indx[next]; // names for the indices in the pair
		m.x += (pt[f].y - pt[n].y) * (pt[f].z + pt[n].z);
		m.y += (pt[f].z - pt[n].z) * (pt[f].x + pt[n].x);
		m.z += (pt[f].x - pt[n].x) * (pt[f].y + pt[n].y);
	}
	m.normalize();
	return m;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<< setRenderMode >>>>>>>>>>>>>>>>>>>>>>>>
void Mesh::setRenderMode(RenderMode m) {
	mode = m;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<< setScale >>>>>>>>>>>>>>>>>>>>>>>>
void Mesh::setScale(float s) {
	scale = s;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<< readMesh >>>>>>>>>>>>>>>>>>>>>>>>
void Mesh::readMesh(string fname) {
	fstream inStream;
	inStream.open(fname.c_str(), ios::in); //open needs a c-like string
	if (inStream.fail() || inStream.eof()) {
		cout << "can't open file or eof: " << fname << endl;
		makeEmpty();
		return;
	}
	inStream >> numVerts >> numNorms >> numFaces;

	// make arrays for vertices, normals, and faces
	pt = new Point[numVerts];
	assert(pt != NULL);

	norm = new Vector[numNorms];
	assert(norm != NULL);

	face = new Face[numFaces];
	assert(face != NULL);

	for (int i = 0; i < numVerts; i++)  // read in the vertices
		inStream >> pt[i].x >> pt[i].y >> pt[i].z;

	for (int ii = 0; ii < numNorms; ii++) 	// read in the normals
		inStream >> norm[ii].x >> norm[ii].y >> norm[ii].z;

	for (int f = 0; f < numFaces; f++)   // read in face data
	{
		inStream >> face[f].nVerts;
		int n = face[f].nVerts;
		face[f].vert = new VertexID[n];
		assert(face[f].vert != NULL);
		for (int k = 0; k < n; k++) 		// read vertex indices for this face
			inStream >> face[f].vert[k].vertIndex;
		for (int kk = 0; kk < n; kk++) 		// read normal indices for this face
			inStream >> face[f].vert[kk].normIndex;
	}
	inStream.close();
} // end of readMesh

//<<<<<<<<<<<<<<<<<<<<<< drawEdges >>>>>>>>>>>>>>>>>>>>
void Mesh::drawEdges() {
	if (isEmpty())
		return; // mesh is empty
	for (int f = 0; f < numFaces; f++) {
		int n = face[f].nVerts;
		glBegin(GL_LINE_LOOP);
		for (int v = 0; v < n; v++) {
			int iv = face[f].vert[v].vertIndex;
			assert(iv >= 0 && iv < numVerts);
			glVertex3f(pt[iv].x * scale, pt[iv].y * scale, pt[iv].z * scale);
		}
		glEnd();
	}
	glFlush();
}

//<<<<<<<<<<<<<<<<<<<<<< drawFaces >>>>>>>>>>>>>>>>>>>>
void Mesh::drawFaces() { // draw each face of this mesh using OpenGL: draw each polygon.
	if (isEmpty())
		return; // mesh is empty
	for (int f = 0; f < numFaces; f++) {
		int n = face[f].nVerts;
		glBegin(GL_POLYGON);
		for (int v = 0; v < n; v++) {
			int in = face[f].vert[v].normIndex;
			assert(in >= 0 && in < numNorms);
			glNormal3f(norm[in].x, norm[in].y, norm[in].z);
			int iv = face[f].vert[v].vertIndex;
			assert(iv >= 0 && iv < numVerts);
			glVertex3f(pt[iv].x * scale, pt[iv].y * scale, pt[iv].z * scale);
		}
		glEnd();
	}
	glFlush();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<< write mesh>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Mesh::writeMesh(char * fname) {
	// write this mesh object into a new Chapter 6 format file.
	if (numVerts == 0 || numNorms == 0 || numFaces == 0)
		return; //empty
	fstream outStream(fname, ios::out); // open the output stream
	if (outStream.fail()) {
		cout << "can't make new file: " << fname << endl;
		return;
	}
	outStream << numVerts << " " << numNorms << " " << numFaces << "\n";
	// write the vertex and vertex normal list
	for (int i = 0; i < numVerts; i++)
		outStream << pt[i].x << " " << pt[i].y << " " << pt[i].z << "\n";
	for (int ii = 0; ii < numNorms; ii++)
		outStream << norm[ii].x << " " << norm[ii].y << " " << norm[ii].z
				<< "\n";
	// write the face data
	for (int f = 0; f < numFaces; f++) {
		int n = face[f].nVerts;
		outStream << n << "\n";
		for (int v = 0; v < n; v++) // write vertex indices for this face
			outStream << face[f].vert[v].vertIndex << " ";
		outStream << "\n";
		for (int k = 0; k < n; k++)	// write normal indices for this face
			outStream << face[f].vert[k].normIndex << " ";
		outStream << "\n";
	}
	outStream.close();
}

void Mesh::printMesh() {
	cout << numVerts << " " << numNorms << " " << numFaces << "\n";
	// write the vertex and vertex normal list
	for (int i = 0; i < numVerts; i++)
		cout << pt[i].x << " " << pt[i].y << " " << pt[i].z << "\n";
	for (int ii = 0; ii < numNorms; ii++)
		cout << norm[ii].x << " " << norm[ii].y << " " << norm[ii].z << "\n";
	// write the face data
	for (int f = 0; f < numFaces; f++) {
		int n = face[f].nVerts;
		cout << n << "\n";
		for (int v = 0; v < n; v++)	// write vertex indices for this face
			cout << face[f].vert[v].vertIndex << " ";
		cout << "\n";
		for (int k = 0; k < n; k++)	// write normal indices for this face
			cout << face[f].vert[k].normIndex << " ";
		cout << "\n";
	}
	cout << endl << flush;
}

