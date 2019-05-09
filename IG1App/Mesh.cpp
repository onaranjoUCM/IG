#include "Mesh.h"

using namespace glm;

//-------------------------------------------------------------------------

Mesh ::~Mesh(void) {
  delete[] vertices;
  vertices = nullptr;
  delete[] colors;
  colors = nullptr;
  delete[] normals;
  normals = nullptr;
}
//-------------------------------------------------------------------------

void Mesh::render() {
  if (vertices != nullptr) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0,
                    vertices);  // number of coordinates per vertex, type of
                                // each coordinate, stride, pointer
    if (colors != nullptr) {
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0,
                     colors);  // number of coordinates per color, type of each
                               // coordinate, stride, pointer
    }

    if (textCoords != nullptr) {
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2, GL_DOUBLE, 0, textCoords);
    }

    if (normals != nullptr) {
      glEnableClientState(GL_NORMAL_ARRAY);
      glNormalPointer(GL_DOUBLE, 0, normals);
    }

    glDrawArrays(primitive, 0,
                 numVertices);  // primitive graphic, first index and number of
                                // elements to be rendered

    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh* Mesh::createRGBAxes(GLdouble l) {
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

Mesh* Mesh::generaPoliespiral(dvec2 verIni, GLdouble angIni, GLdouble incrAng,
                              GLdouble ladoIni, GLdouble incrLado,
                              GLuint numVert) {
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

Mesh* Mesh::generaDragon(GLuint numVert) {
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
    if (azar < 0.787473) {  // T1
      x = 0.824074 * auxX + 0.281482 * auxY - 0.882290;
      y = -0.212346 * auxX + 0.864198 * auxY - 0.110607;
    } else {  // T2
      x = 0.088272 * auxX + 0.520988 * auxY + 0.785360;
      y = -0.463889 * auxX - 0.377778 * auxY + 8.095795;
    }
  }

  return m;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaTriangulo(GLdouble r) {
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

//-------------------------------------------------------------------------

Mesh* Mesh::generaTrianguloRGB(GLdouble r) {
  Mesh* m = generaTriangulo(r);
  m->colors = new dvec4[m->numVertices];
  m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);
  return m;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaRectangulo(GLdouble w, GLdouble h) {
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

//-------------------------------------------------------------------------

Mesh* Mesh::generaRectanguloRGB(GLdouble w, GLdouble h) {
  Mesh* m = generaRectangulo(w, h);
  m->colors = new dvec4[m->numVertices];
  m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);
  m->colors[3] = dvec4(0.0, 1.0, 1.0, 1.0);
  return m;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaTrianguloAnimado(GLdouble r) {
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

Mesh* Mesh::generaEstrella3D(GLdouble re, GLdouble np, GLdouble h) {
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

Mesh* Mesh::generaContCubo(GLdouble l) {
  Mesh* m = new Mesh();
  m->primitive = GL_TRIANGLE_STRIP;
  m->numVertices = 10;
  m->vertices = new dvec3[m->numVertices];

  m->vertices[0] = dvec3(-l / 2, l / 2, -l / 2);
  m->vertices[1] = dvec3(-l / 2, -l / 2, -l / 2);
  m->vertices[2] = dvec3(-l / 2, l / 2, l / 2);
  m->vertices[3] = dvec3(-l / 2, -l / 2, l / 2);
  m->vertices[4] = dvec3(l / 2, l / 2, l / 2);
  m->vertices[5] = dvec3(l / 2, -l / 2, l / 2);
  m->vertices[6] = dvec3(l / 2, l / 2, -l / 2);
  m->vertices[7] = dvec3(l / 2, -l / 2, -l / 2);
  m->vertices[8] = dvec3(-l / 2, l / 2, -l / 2);
  m->vertices[9] = dvec3(-l / 2, -l / 2, -l / 2);

  return m;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw,
                                   GLuint rh) {
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
  m->textCoords[1] = dvec2(0, rh);
  m->textCoords[2] = dvec2(rw, 0);
  m->textCoords[3] = dvec2(rw, rh);

  return m;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaEstrella3DTexCor(GLdouble re, GLdouble np, GLdouble h) {
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
    } else {
      x = re / 2 * cos(radians(ang));
      y = re / 2 * sin(radians(ang));
    }
    m->textCoords[i] = dvec2(x / 12, y / 12);
  }
  return m;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaContCuboTexCor(GLdouble l) {
  Mesh* m = generaContCubo(l);

  m->textCoords = new dvec2[m->numVertices];
  m->textCoords[0] = dvec2(0, 0);
  m->textCoords[1] = dvec2(0, l / 10);
  m->textCoords[2] = dvec2(l / 10, 0);
  m->textCoords[3] = dvec2(l / 10, l / 10);
  m->textCoords[4] = dvec2(0, 0);
  m->textCoords[5] = dvec2(0, l / 10);
  m->textCoords[6] = dvec2(l / 10, 0);
  m->textCoords[7] = dvec2(l / 10, l / 10);
  m->textCoords[8] = dvec2(0, 0);
  m->textCoords[9] = dvec2(0, l / 10);

  return m;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaParedCuboTexCor(GLdouble w, GLdouble h) {
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

void IndexMesh::render() {
  if (vertices != nullptr) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0,
                    vertices);  // number of coordinates per vertex, type of
                                // each coordinate, stride, pointer
    if (colors != nullptr) {
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0,
                     colors);  // number of coordinates per color, type of each
                               // coordinate, stride, pointer
    }

    if (textCoords != nullptr) {
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2, GL_DOUBLE, 0, textCoords);
    }

    if (normals != nullptr) {
      glEnableClientState(GL_NORMAL_ARRAY);
      glNormalPointer(GL_DOUBLE, 0, normals);
    }

    if (indices != nullptr) {
      glEnableClientState(GL_INDEX_ARRAY);
      glIndexPointer(GL_UNSIGNED_INT, 0, indices);
    }

    glDrawElements(primitive, numIndices, GL_UNSIGNED_INT, indices);

    glDisableClientState(GL_INDEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
  }
}

IndexMesh* IndexMesh::generateGrid(GLdouble lado, GLuint numDiv) {
  // Grid cuadrado de lado*lado, centrado en el plano Y=0,
  // dividido en numDiv*numDiv celdas (cada celda son 2 triángulos)
  IndexMesh* m = new IndexMesh();
  GLdouble incr = lado / numDiv;  // incremento para la coordenada x, y la c. z
  GLuint numFC = numDiv + 1;      // número de vértices por filas y columnas
  m->primitive = GL_TRIANGLES;

  // generar vértices
  m->numVertices = numFC * numFC;  // número de vértices
  m->vertices = new dvec3[m->numVertices];

  GLuint z = -lado / 2;
  GLuint x = -lado / 2;
  for (int f = 0; f <= numDiv; f++) {
    for (int c = 0; c <= numDiv; c++) {
      m->vertices[f * numFC + c] = dvec3(x + c * incr, 0, z + f * incr);
    }
  }

  // generar índices
  m->numIndices = numDiv * numDiv * 6;  // número de índices
  m->indices = new GLuint[m->numIndices];

  GLuint i = 0;  // array de índices
  for (int h = 0; h < numDiv; h++) {
    for (int k = 0; k < numDiv; k++) {
      GLuint iv = h * numFC + k;
      m->indices[i++] = iv;
      m->indices[i++] = iv + numFC;
      m->indices[i++] = iv + 1;
      m->indices[i++] = iv + 1;
      m->indices[i++] = iv + numFC;
      m->indices[i++] = iv + numFC + 1;
    }
  }

  return m;
}

// Grid cuadrado de lado*lado, centrado en el plano Y=0, dividido en
// numDiv*numDiv celdas
IndexMesh* IndexMesh::generateGridTex(GLdouble lado, GLuint numDiv) {
  IndexMesh* m = generateGrid(lado, numDiv);
  GLuint numFC = numDiv + 1;  // número de vértices por filas y columnas
  // generar coordenadas de textura
  m->textCoords = new dvec2[m->numVertices];
  GLuint s = 0;
  GLuint t = 1;
  for (int f = 0; f < m->numVertices; f++) {
    for (int c = 0; c < m->numVertices; c++) {
      m->textCoords[f * numFC + c] = dvec2(s + 0.25 * c, t - 0.25 * f);
    }
  }
  return m;
}

IndexMesh* IndexMesh::generarPlanoCurvado(GLdouble lado, GLuint numDiv,
                                          GLdouble curvatura) {
  IndexMesh* m = generateGridTex(lado, numDiv);

  for (int f = 0; f <= numDiv; f++) {
    for (int c = 0; c <= numDiv; c++) {
      GLuint x = m->vertices[f, c].x;
      GLuint z = m->vertices[f, c].z;
      m->vertices[f, c].y = lado * curvatura / 2 - curvatura / lado * (x * x) -
                            curvatura / lado * (z * z);
      m->normals[f, c].y =
          (2 * curvatura / lado * x, 1, 2 * curvatura / lado * z);
    }
  }
  m->normals = new dvec3[m->numVertices];
  // modificar la coordenada Y de los vértices con la ecuación
  // f(x, z) = lado * curvatura / 2 – curvatura / lado * (x * x) – curvatura /
  // lado * (z * z) …  // para cada vértice del Grid V=(x,0,z), la coordenada Y
  // se cambia a f(x,z)
  // generar el vector normal a cada vértice con la ecuación
  // n(x, z) = (2 * curvatura / lado * x, 1, 2 * curvatura / lado * z)
  //…  // el vector normal del vértice V=(x, y,z), es n(x, z) normalizado
  return m;
}
