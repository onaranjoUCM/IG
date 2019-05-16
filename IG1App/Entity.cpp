#include "Entity.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Entity::uploadMvM(dmat4 const& modelViewMat) const {
  dmat4 aMat = modelViewMat * modelMat;
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixd(value_ptr(aMat));
}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l) : Entity() { mesh = Mesh::createRGBAxes(l); }

EjesRGB::~EjesRGB() {
  delete mesh;
  mesh = nullptr;
};

void EjesRGB::render(Camera const& cam) {
  if (mesh != nullptr) {
    uploadMvM(cam.getViewMat());
    glLineWidth(2);
    mesh->render();
    glLineWidth(1);
  }
}

//-------------------------------------------------------------------------

Poliespiral::Poliespiral(dvec2 verIni, GLdouble angIni, GLdouble incrAng,
                         GLdouble ladoIni, GLdouble incrLado, GLuint numVert)
    : Entity() {
  mesh = Mesh::generaPoliespiral(verIni, angIni, incrAng, ladoIni, incrLado,
                                 numVert);
}

Poliespiral::~Poliespiral() {
  delete mesh;
  mesh = nullptr;
};

void Poliespiral::render(Camera const& cam) {
  if (mesh != nullptr) {
    glColor3d(0.0, 0.0, 1.0);
    uploadMvM(cam.getViewMat());
    mesh->render();
    glLineWidth(2);
  }
}

//-------------------------------------------------------------------------

Dragon::Dragon(GLuint numVert) : Entity() {
  mesh = Mesh::generaDragon(numVert);
}

Dragon::~Dragon() {
  delete mesh;
  mesh = nullptr;
};

void Dragon::render(Camera const& cam) {
  if (mesh != nullptr) {
    glColor3d(0.0, 0.0, 1.0);
    glPointSize(2);
    uploadMvM(cam.getViewMat());
    mesh->render();
  }
}

//-------------------------------------------------------------------------

TrianguloRGB::TrianguloRGB(GLdouble r) : Entity() {
  mesh = Mesh::generaTrianguloRGB(r);
}

TrianguloRGB::~TrianguloRGB() {
  delete mesh;
  mesh = nullptr;
}

void TrianguloRGB::render(Camera const& cam) {
  if (mesh != nullptr) {
    uploadMvM(cam.getViewMat());
    mesh->render();
    glLineWidth(2);
  }
}

//-------------------------------------------------------------------------

RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h) : Entity() {
  mesh = Mesh::generaRectanguloRGB(w, h);
}

RectanguloRGB::~RectanguloRGB() {
  delete mesh;
  mesh = nullptr;
}

void RectanguloRGB::render(Camera const& cam) {
  if (mesh != nullptr) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3d(0.0, 0.0, 1.0);
    uploadMvM(cam.getViewMat());
    mesh->render();
  }
}

//-------------------------------------------------------------------------

TrianguloAnimado::TrianguloAnimado(GLdouble r) : Entity() {
  mesh = Mesh::generaTrianguloAnimado(r);
  modelMatIni = modelMat;
}

TrianguloAnimado::~TrianguloAnimado() {
  delete mesh;
  mesh = nullptr;
}

void TrianguloAnimado::render(Camera const& cam) {
  if (mesh != nullptr) {
    uploadMvM(cam.getViewMat());
    mesh->render();
    glLineWidth(2);
  }
}

void TrianguloAnimado::update() {
  dmat4 m;

  setModelMat(modelMatIni);
  m = rotate(getModelMat(), radians(angle += 1.0), dvec3(0, 0, 1));
  m = translate(m, dvec3(40, 40, 0));
  m = rotate(m, radians(angle += 10.0), dvec3(0, 0, 1));

  setModelMat(m);
}

//-------------------------------------------------------------------------

Estrella3D::Estrella3D(GLdouble re, GLdouble np, GLdouble h) : Entity() {
  mesh = Mesh::generaEstrella3D(re, np, h);
  modelMatIni = modelMat;
}

Estrella3D::~Estrella3D() {
  delete mesh;
  mesh = nullptr;
}

void Estrella3D::render(Camera const& cam) {
  if (mesh != nullptr) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3d(1.0, 0.0, 1.0);
    uploadMvM(cam.getViewMat());
    mesh->render();
    modelMat = rotate(modelMat, radians(180.0), dvec3(1, 0, 0));
    uploadMvM(cam.getViewMat());
    mesh->render();
    glLineWidth(2);
  }
}

void Estrella3D::update() {
  setModelMat(modelMatIni);
  dmat4 m = rotate(getModelMat(), radians(angle += 5.0), dvec3(0, 1, 0));
  m = rotate(m, radians(angle += 5.0), dvec3(0, 0, 1));
  setModelMat(m);
}

//-------------------------------------------------------------------------

Caja::Caja(GLdouble l) : Entity() { mesh = Mesh::generaContCubo(l); }

Caja::~Caja() {
  delete mesh;
  mesh = nullptr;
}

void Caja::render(Camera const& cam) {
  if (mesh != nullptr) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3d(0.0, 0.0, 1.0);
    uploadMvM(cam.getViewMat());
    mesh->render();
    glLineWidth(2);
  }
}

void Caja::update() {}

//-------------------------------------------------------------------------

RectanguloTexCor::RectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
    : Entity() {
  mesh = Mesh::generaRectanguloTexCor(w, h, rw, rh);
  texture.load("Images/baldosaC.bmp");
}

RectanguloTexCor::~RectanguloTexCor() {
  delete mesh;
  mesh = nullptr;
}

void RectanguloTexCor::render(Camera const& cam) {
  if (mesh != nullptr) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    texture.bind();
    glColor3d(0.0, 0.0, 1.0);
    uploadMvM(cam.getViewMat());
    mesh->render();
    texture.unbind();
  }
}

//-------------------------------------------------------------------------

Estrella3DTexCor::Estrella3DTexCor(GLdouble re, GLdouble np, GLdouble h)
    : Entity() {
  mesh = Mesh::generaEstrella3DTexCor(re, np, h);
  modelMatIni = modelMat;
  texture.load("Images/baldosaP.bmp");
}

Estrella3DTexCor::~Estrella3DTexCor() {
  delete mesh;
  mesh = nullptr;
}

void Estrella3DTexCor::render(Camera const& cam) {
  if (mesh != nullptr) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    texture.bind();
    glColor3d(0.0, 0.0, 1.0);
    uploadMvM(cam.getViewMat());
    mesh->render();
    modelMat = rotate(modelMat, radians(180.0), dvec3(1, 0, 0));
    uploadMvM(cam.getViewMat());
    mesh->render();
    texture.unbind();
  }
}

void Estrella3DTexCor::update() {
  setModelMat(modelMatIni);
  glm::dmat4 m = rotate(getModelMat(), radians(angle += 5.0), dvec3(0, 1, 0));
  m = rotate(m, radians(angle += 5.0), dvec3(0, 0, 1));
  setModelMat(m);
}

//-------------------------------------------------------------------------

CajaTexCor::CajaTexCor(GLdouble l) : Entity() {
  mesh = Mesh::generaContCuboTexCor(l);
  texture.load("Images/container.bmp");
  texture1.load("Images/papelE.bmp");
}

CajaTexCor::~CajaTexCor() {
  delete mesh;
  mesh = nullptr;
}

void CajaTexCor::render(Camera const& cam) {
  if (mesh != nullptr) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    texture.bind();
    glColor3d(0.0, 0.0, 1.0);
    uploadMvM(cam.getViewMat());
    mesh->render();
    texture.unbind();

    glCullFace(GL_FRONT);
    texture1.bind();
    mesh->render();
    texture1.unbind();

    glDisable(GL_CULL_FACE);
    glLineWidth(2);
  }
}

//-------------------------------------------------------------------------

ParedTexCor::ParedTexCor(GLdouble w, GLdouble h) {
  mesh = Mesh::generaParedCuboTexCor(w, h);
  texture.load("Images/cristalTri.bmp", 100);
}

ParedTexCor::~ParedTexCor() {
  delete mesh;
  mesh = nullptr;
}

void ParedTexCor::render(Camera const& cam) {
  if (mesh != nullptr) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);
    texture.bind();
    uploadMvM(cam.getViewMat());
    mesh->render();
    texture.unbind();
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
  }
}

//-------------------------------------------------------------------------

Foto::Foto(GLdouble w, GLdouble h, GLuint rw, GLuint rh) {
  mesh = Mesh::generaRectanguloTexCor(w, h, rw, rh);
}

Foto::~Foto() {
  delete mesh;
  mesh = nullptr;
}

void Foto::render(Camera const& cam) {
  if (mesh != nullptr) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    texture.loadColorBuffer();
    texture.bind();
    glColor3d(0.0, 0.0, 1.0);
    uploadMvM(cam.getViewMat());
    mesh->render();
    texture.unbind();
  }
}

//-------------------------------------------------------------------------

EntityMaterial::EntityMaterial(std::string t) : Entity() {
  texture = new Texture();
  texture->load(t, 100);
  glGetIntegerv(GL_TEXTURE_BINDING_2D, &id);
}

EntityMaterial::~EntityMaterial() {}

//-------------------------------------------------------------------------

Esfera::Esfera(GLdouble r, std::string t) : EntityMaterial(t), radius(r) {
  qObj = gluNewQuadric();
}

Esfera::~Esfera() { gluDeleteQuadric(qObj); }

void Esfera::render(Camera const& cam) {
  glEnable(GL_CULL_FACE);
  material.upload();

  gluQuadricDrawStyle(qObj, GLU_FILL);
  gluQuadricNormals(qObj, GLU_SMOOTH);
  gluQuadricOrientation(qObj, GLU_OUTSIDE);
  gluQuadricTexture(qObj, GL_TRUE);
  uploadMvM(cam.getViewMat());

  texture->bind(GL_MODULATE);
  gluSphere(qObj, radius, radius, radius);
  texture->unbind();

  glDisable(GL_CULL_FACE);
}

//-------------------------------------------------------------------------

EsferaLuz::EsferaLuz(GLdouble r, std::string t) : Esfera(r, t) {
  modelMatIni = modelMat;

  spotLight = new PosLight();
  spotLight->uploadLI();
  spotLight->enable();

  esferaGrande = new Esfera(r * 1.5, t);
  glm::dmat4 m = esferaGrande->getModelMat();
  m = translate(m, dvec3(0, 150, 100));
  esferaGrande->setModelMat(m);
}

EsferaLuz::~EsferaLuz() { Esfera::~Esfera(); }

void EsferaLuz::render(Camera const& cam) {
  glEnable(GL_CULL_FACE);
  material.upload();

  gluQuadricDrawStyle(qObj, GLU_LINE);
  gluQuadricNormals(qObj, GLU_SMOOTH);
  gluQuadricOrientation(qObj, GLU_OUTSIDE);
  gluQuadricTexture(qObj, GL_TRUE);
  uploadMvM(cam.getViewMat());

  texture->bind(GL_MODULATE);
  gluSphere(qObj, radius, radius, radius);
  texture->unbind();

  glDisable(GL_CULL_FACE);
  esferaGrande->render(cam);
}

void EsferaLuz::update() {
  ang += 5;
  if (ang >= 360) ang = 0;
  setModelMat(modelMatIni);
  glm::dmat4 m =
	  translate(getModelMat(), dvec3(200 * cos(radians(ang)),
		  radius * 4 * sin(radians(ang)) * sin(radians(ang)),
                         -200 * sin(radians(ang)) * cos(radians(ang))));
  
  spotLight->setPos(dvec3(200 * cos(radians(ang)),
	  radius * 4 * sin(radians(ang)) * sin(radians(ang)),
	  -200 * sin(radians(ang)) * cos(radians(ang))));
  setModelMat(m);
}

//-------------------------------------------------------------------------

Superficie::Superficie(GLdouble lado, GLuint numDiv, GLdouble curvatura,
                       std::string t)
    : EntityMaterial(t) {
  mesh = IndexMesh::generarPlanoCurvado(lado, numDiv, curvatura);
}

Superficie::~Superficie() {}

void Superficie::render(Camera const& cam) {
  material.upload();

  texture->bind(GL_MODULATE);

  uploadMvM(cam.getViewMat());

  mesh->render();
  texture->unbind();
}
