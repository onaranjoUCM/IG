#include "Mesh.h"

using namespace glm;

//-------------------------------------------------------------------------

Mesh ::~Mesh(void) 
{
  delete[] vertices;  vertices = nullptr;
  delete[] colors;    colors = nullptr;
}
//-------------------------------------------------------------------------

void Mesh::render()
{
  if (vertices != nullptr) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertices);  // number of coordinates per vertex, type of each coordinate, stride, pointer 
    if (colors != nullptr) {
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, colors);   // number of coordinates per color, type of each coordinate, stride, pointer 
    }

	if (textCoords != nullptr) {
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_DOUBLE, 0, textCoords);
	}

    glDrawArrays(primitive, 0, numVertices);   // primitive graphic, first index and number of elements to be rendered

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh * Mesh::createRGBAxes(GLdouble l)
{
  Mesh* m = new Mesh();
  m->primitive = GL_LINES;
  m->numVertices = 6;

  m->vertices = new dvec3[m->numVertices];
  // X axis vertices
  m->vertices[0] = dvec3(0.0, 0.0, 0.0);   
  m->vertices[1] = dvec3(l, 0.0, 0);
  // Y axis vertices
  m->vertices[2] = dvec3(0, 0.0, 0.0);
  m->vertices[3] = dvec3(0.0, l, 0.0); 
  // Z axis vertices
  m->vertices[4] = dvec3(0.0, 0.0, 0.0);
  m->vertices[5] = dvec3(0.0, 0.0, l);

  m->colors = new dvec4[m->numVertices];
  // X axis color: red  ( Alpha = 1 : fully opaque)
  m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  m->colors[2] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[3] = dvec4(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  m->colors[4] = dvec4(0.0, 0.0, 1.0, 1.0);
  m->colors[5] = dvec4(0.0, 0.0, 1.0, 1.0);
 
  return m; 
}

//-------------------------------------------------------------------------

Mesh * Mesh::generaPoliespiral(dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert)
{
	Mesh* m = new Mesh();
	m->primitive = GL_LINE_STRIP;
	m->numVertices = numVert;
	m->vertices = new dvec3[m->numVertices];

	double x = verIni.x;
	double y = verIni.y;
	for (int i = 0; i < numVert; i++) {
		m->vertices[i] = dvec3(x, y, 0.0);

		x += ladoIni * cos(radians(angIni));
		y += ladoIni * sin(radians(angIni));
		angIni += incrAng;
		ladoIni += incrLado;
	}

	return m;
}

//-------------------------------------------------------------------------

Mesh * Mesh::generaDragon(GLuint numVert)
{
	Mesh* m = new Mesh();
	m->primitive = GL_POINTS;
	m->numVertices = numVert;
	m->vertices = new dvec3[m->numVertices];

	double x = 0;
	double y = 0;
	double auxX = x;
	double auxY = y;
	for (int i = 0; i < numVert; i++) {
		m->vertices[i] = dvec3(x, y, 0.0);

		double azar = rand() / double(RAND_MAX);
		auxX = x;
		auxY = y;
		if (azar < 0.787473) { // T1
			x = 0.824074 * auxX + 0.281482 * auxY - 0.882290;
			y = -0.212346 * auxX + 0.864198 * auxY - 0.110607;
		} else { // T2
			x = 0.088272 * auxX + 0.520988 * auxY + 0.785360;
			y = -0.463889 * auxX - 0.377778 * auxY + 8.095795;
		}
	}

	return m;
}

//-------------------------------------------------------------------------

Mesh * Mesh::generaTriangulo(GLdouble r)
{
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLES;
	m->numVertices = 3;
	m->vertices = new dvec3[m->numVertices];

	double x = 0;
	double y = 0;
	double angIni = 90;
	double incrAng = 90;
	double Cx = x;
	double Cy = y;
	double ang = angIni;

	for (int i = 0; i < m->numVertices; i++) {
		x = Cx + r * cos(ang);
		y = Cy + r * sin(ang);
		m->vertices[i] = dvec3(x, y, 0.0);
		ang += incrAng;
		Cx = x;
		Cy = y;
	}

	return m;
}

Mesh * Mesh::generaTrianguloRGB(GLdouble r)
{
	Mesh* m = generaTriangulo(r);
	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);
	return m;
}

//-------------------------------------------------------------------------

Mesh * Mesh::generaRectangulo(GLdouble w, GLdouble h)
{
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 4;
	m->vertices = new dvec3[m->numVertices];

	m->vertices[0] = dvec3(0, 0, 0);
	m->vertices[1] = dvec3(0, h, 0.0);
	m->vertices[2] = dvec3(w, 0, 0.0);
	m->vertices[3] = dvec3(w, h, 0.0);


	return m;
}

Mesh * Mesh::generaRectanguloRGB(GLdouble w, GLdouble h) {
	Mesh* m = generaRectangulo(w, h);
	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);
	m->colors[3] = dvec4(0.0, 1.0, 1.0, 1.0);
	return m;
}

//-------------------------------------------------------------------------

Mesh * Mesh::generaTrianguloAnimado(GLdouble r) {
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLES;
	m->numVertices = 3;
	m->vertices = new dvec3[m->numVertices];

	double x = 0;
	double y = 0;
	double angIni = 90;
	double incrAng = 90;
	double ang = angIni;

	for (int i = 0; i < m->numVertices; i++) {
		x = r * cos(ang);
		y = r * sin(ang);
		m->vertices[i] = dvec3(x, y, 0.0);
		ang += incrAng;
	}

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);

	return m;
}

//-------------------------------------------------------------------------

Mesh * Mesh::generaEstrella3D(GLdouble re, GLdouble np, GLdouble h) {
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_FAN;
	m->numVertices = 2 * np + 2;
	m->vertices = new dvec3[m->numVertices];

	double x = 0;
	double y = 0;
	double z = 0;
	double angIni = 360 / np / 2;
	double ang = angIni;

	m->vertices[0] = dvec3(0, 0, 0);
	for (int i = 1; i < m->numVertices; i++) {
		x = y = 0;
		ang += angIni;
		if (i % 2 == 0) {
			x = re * cos(radians(ang));
			y = re * sin(radians(ang));
		} else {
			x = re / 2 * cos(radians(ang));
			y = re / 2 * sin(radians(ang));
		}
		m->vertices[i] = dvec3(x, y, h);
	}
	return m;
}

//-------------------------------------------------------------------------

Mesh * Mesh::generaContCubo(GLdouble l) {
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 10;
	m->vertices = new dvec3[m->numVertices];

	m->vertices[0] = dvec3(-l/2, l/2, -l/2);
	m->vertices[1] = dvec3(-l/2, -l/2, -l/2);
	m->vertices[2] = dvec3(-l/2, l/2, l/2);
	m->vertices[3] = dvec3(-l/2, -l/2, l/2);
	m->vertices[4] = dvec3(l/2, l/2, l/2);
	m->vertices[5] = dvec3(l/2, -l/2, l/2);
	m->vertices[6] = dvec3(l/2, l/2, -l/2);
	m->vertices[7] = dvec3(l/2, -l/2, -l/2);
	m->vertices[8] = dvec3(-l/2, l/2, -l/2);
	m->vertices[9] = dvec3(-l/2, -l/2, -l/2);

	return m;
}

//-------------------------------------------------------------------------

Mesh * Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh) {
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 4;
	m->vertices = new dvec3[m->numVertices];

	m->vertices[0] = dvec3(0, 0, 0);
	m->vertices[1] = dvec3(0, h, 0.0);
	m->vertices[2] = dvec3(w, 0, 0.0);
	m->vertices[3] = dvec3(w, h, 0.0);

	m->textCoords = new dvec2[m->numVertices];
	m->textCoords[0] = dvec2(0, 0);
	m->textCoords[1] = dvec2(0, h / 10);
	m->textCoords[2] = dvec2(w / 10, 0);
	m->textCoords[3] = dvec2(w / 10, h / 10);

	return m;
}

//-------------------------------------------------------------------------

Mesh * Mesh::generaEstrella3DTexCor(GLdouble re, GLdouble np, GLdouble h) {
	Mesh* m = generaEstrella3D(re, np, h);
	double x = 0;
	double y = 0;
	double z = 0;
	double angIni = 360 / np / 2;
	double ang = angIni;
	m->textCoords = new dvec2[m->numVertices];
	m->textCoords[0] = dvec2(0, 0);
	for (int i = 1; i < m->numVertices; i++) {
		x = y = 0;
		ang += angIni;
		if (i % 2 == 0) {
			x = re * cos(radians(ang));
			y = re * sin(radians(ang));
		}
		else {
			x = re / 2 * cos(radians(ang));
			y = re / 2 * sin(radians(ang));
		}
		m->textCoords[i] = dvec2(x / 12, y / 12);
	}
	return m;
}

//-------------------------------------------------------------------------

Mesh * Mesh::generaContCuboTexCor(GLdouble l) {
	Mesh* m = generaContCubo(l);

	m->textCoords = new dvec2[m->numVertices];
	m->textCoords[0] = dvec2(0, 0);
	m->textCoords[1] = dvec2(0, l/10);
	m->textCoords[2] = dvec2(l/10, 0);
	m->textCoords[3] = dvec2(l/10, l/10);
	m->textCoords[4] = dvec2(0, 0);
	m->textCoords[5] = dvec2(0, l/10);
	m->textCoords[6] = dvec2(l/10, 0);
	m->textCoords[7] = dvec2(l/10, l/10);
	m->textCoords[8] = dvec2(0, 0);
	m->textCoords[9] = dvec2(0, l/10);

	return m;
}

Mesh * Mesh::generaParedCuboTexCor(GLdouble w, GLdouble h) {
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 10;
	m->vertices = new dvec3[m->numVertices];

	m->vertices[0] = dvec3(-w / 2, h / 2, -w / 2);
	m->vertices[1] = dvec3(-w / 2, -h / 2, -w / 2);
	m->vertices[2] = dvec3(-w / 2, h / 2, w / 2);
	m->vertices[3] = dvec3(-w / 2, -h / 2, w / 2);
	m->vertices[4] = dvec3(w / 2, h / 2, w / 2);
	m->vertices[5] = dvec3(w / 2, -h / 2, w / 2);
	m->vertices[6] = dvec3(w / 2, h / 2, -w / 2);
	m->vertices[7] = dvec3(w / 2, -h / 2, -w / 2);
	m->vertices[8] = dvec3(-w / 2, h / 2, -w / 2);
	m->vertices[9] = dvec3(-w / 2, -h / 2, -w / 2);

	m->textCoords = new dvec2[m->numVertices];
	m->textCoords[0] = dvec2(0, 0);
	m->textCoords[1] = dvec2(0, h / 50);
	m->textCoords[2] = dvec2(w / 100, 0);
	m->textCoords[3] = dvec2(w / 100, h / 50);
	m->textCoords[4] = dvec2(0, 0);
	m->textCoords[5] = dvec2(0, h / 50);
	m->textCoords[6] = dvec2(w / 100, 0);
	m->textCoords[7] = dvec2(w / 100, h / 50);
	m->textCoords[8] = dvec2(0, 0);
	m->textCoords[9] = dvec2(0, h / 50);

	return m;
}
