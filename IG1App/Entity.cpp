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

EjesRGB::EjesRGB(GLdouble l): Entity()  {
  mesh = Mesh::createRGBAxes(l);
}

EjesRGB::~EjesRGB()  { 
	delete mesh; mesh = nullptr; 
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

Poliespiral::Poliespiral(dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert) : Entity() {
	mesh = Mesh::generaPoliespiral(verIni, angIni, incrAng, ladoIni, incrLado, numVert);
}

Poliespiral::~Poliespiral() {
	delete mesh; mesh = nullptr;
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
	delete mesh; mesh = nullptr;
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
	delete mesh; mesh = nullptr;
}

void TrianguloRGB::render(Camera const & cam) {
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
	delete mesh; mesh = nullptr;
}

void RectanguloRGB::render(Camera const & cam) {
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
}

TrianguloAnimado::~TrianguloAnimado() {
	delete mesh; mesh = nullptr;
}

void TrianguloAnimado::render(Camera const & cam) {
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		mesh->render();
		glLineWidth(2);
	}
}

void TrianguloAnimado::update() {
	glm::dmat4 m;

	setModelMat(glm::dmat4(1));
	m = rotate(getModelMat(), radians(angle+=1.0), dvec3(0, 0, 1));
	m = translate(m, dvec3(40, 40, 0));
	m = rotate(m, radians(angle+=10.0), dvec3(0, 0, 1));
	
	setModelMat(m);
}

//-------------------------------------------------------------------------

Estrella3D::Estrella3D(GLdouble re, GLdouble np, GLdouble h) : Entity() {
	mesh = Mesh::generaEstrella3D(re, np, h);
}

Estrella3D::~Estrella3D() {
	delete mesh; mesh = nullptr;
}

void Estrella3D::render(Camera const & cam) {
	if (mesh != nullptr) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3d(1.0, 0.0, 1.0);


		uploadMvM(cam.getViewMat());
		mesh->render();

		glm::dmat4 m = rotate(getModelMat(), radians(180.0), dvec3(1, 0, 0));
		setModelMat(m);
		uploadMvM(cam.getViewMat());
		mesh->render();
		glLineWidth(2);
	}
}

void Estrella3D::update() {
	setModelMat(glm::dmat4(1));
	glm::dmat4 m = translate(getModelMat(), dvec3(0, 20, 0));
	m = rotate(m, radians(angle+=5.0), dvec3(0, 1, 0));
	m = rotate(m, radians(angle+=5.0), dvec3(0, 0, 1));
	setModelMat(m);
}

//-------------------------------------------------------------------------

Caja::Caja(GLdouble l) : Entity() {
	mesh = Mesh::generaContCubo(l);
}

Caja::~Caja() {
	delete mesh; mesh = nullptr;
}

void Caja::render(Camera const & cam) {
	if (mesh != nullptr) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3d(0.0, 0.0, 1.0);
		uploadMvM(cam.getViewMat());
		mesh->render();
		glLineWidth(2);
	}
}

void Caja::update() { }

//-------------------------------------------------------------------------

RectanguloTexCor::RectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh) : Entity() {
	mesh = Mesh::generaRectanguloTexCor(w, h, rw, rh);
	texture.load("Images/baldosaC.bmp");
}

RectanguloTexCor::~RectanguloTexCor() {
	delete mesh; mesh = nullptr;
}

void RectanguloTexCor::render(Camera const & cam) {
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

Estrella3DTexCor::Estrella3DTexCor(GLdouble re, GLdouble np, GLdouble h) : Entity() {
	mesh = Mesh::generaEstrella3DTexCor(re, np, h);
	texture.load("Images/baldosaP.bmp");
}

Estrella3DTexCor::~Estrella3DTexCor() {
	delete mesh; mesh = nullptr;
}

void Estrella3DTexCor::render(Camera const & cam) {
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

CajaTexCor::CajaTexCor(GLdouble l) : Entity() {
	mesh = Mesh::generaContCuboTexCor(l);
	texture.load("Images/container.bmp");
	texture1.load("Images/papelE.bmp");
}

CajaTexCor::~CajaTexCor() {
	delete mesh; mesh = nullptr;
}

void CajaTexCor::render(Camera const & cam) {
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

ParedTexCor::ParedTexCor(GLdouble l) {
	mesh = Mesh::generaParedCuboTexCor(l);
	texture.load("Images/container.bmp");
}

ParedTexCor::~ParedTexCor() {
	delete mesh; mesh = nullptr;
}

void ParedTexCor::render(Camera const & cam) {
	if (mesh != nullptr) {
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		texture.bind();
		glClearColor(0.3, 1.0, 0.4, 0.0);
		//glColor3d(0.0, 0.0, 1.0);
		uploadMvM(cam.getViewMat());
		mesh->render();
		texture.unbind();
		glLineWidth(2);
	}
}