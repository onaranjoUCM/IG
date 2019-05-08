//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>

#include <glm.hpp>

//-------------------------------------------------------------------------

class Mesh {
 public:
  static Mesh* createRGBAxes(GLdouble l);  // creates a new 3D RGB axes mesh
  static Mesh* generaPoliespiral(glm::dvec2 verIni, GLdouble angIni,
                                 GLdouble incrAng, GLdouble ladoIni,
                                 GLdouble incrLado, GLuint numVert);
  static Mesh* generaDragon(GLuint numVert);
  static Mesh* generaTriangulo(GLdouble r);
  static Mesh* generaTrianguloRGB(GLdouble r);
  static Mesh* generaRectangulo(GLdouble w, GLdouble h);
  static Mesh* generaRectanguloRGB(GLdouble w, GLdouble h);
  static Mesh* generaTrianguloAnimado(GLdouble r);
  static Mesh* generaEstrella3D(GLdouble re, GLdouble np, GLdouble h);
  static Mesh* generaContCubo(GLdouble l);
  static Mesh* generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw,
                                      GLuint rh);
  static Mesh* generaEstrella3DTexCor(GLdouble re, GLdouble np, GLdouble h);
  static Mesh* generaContCuboTexCor(GLdouble l);
  static Mesh* generaParedCuboTexCor(GLdouble w, GLdouble h);

  Mesh(void){};
  ~Mesh(void);
  virtual void render();

  glm::dvec3* getVertices() { return vertices; };  // vertex array
  glm::dvec4* getColors() { return colors; };      // color array

 protected:
  GLuint numVertices = 0;           // arrays size (number of elements)
  GLuint primitive = GL_TRIANGLES;  // graphic primitive: GL_POINTS, GL_LINES,
                                    // GL_TRIANGLES, ...

  glm::dvec2* textCoords = nullptr;  // coordinates array
  glm::dvec3* vertices = nullptr;    // vertex array
  glm::dvec4* colors = nullptr;      // color array

  glm::dvec3* normals = nullptr;
};

//-------------------------------------------------------------------------

class IndexMesh : public Mesh {
 protected:
  GLuint* indices = nullptr;
  GLuint numIndices = 0;

 public:
  virtual void render();
  static IndexMesh* generateGrid(GLdouble lado, GLuint numDiv);
  static IndexMesh* generateGridTex(GLdouble lado, GLuint numDiv);
  static IndexMesh* generarPlanoCurvado(GLdouble lado, GLuint numDiv, GLdouble curvatura);
};

#endif  //_H_Scene_H_
