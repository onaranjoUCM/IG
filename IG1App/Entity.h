//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"

//-------------------------------------------------------------------------

class Entity 
{
public:
	Entity() : modelMat(1.0) { }; 
	virtual ~Entity() { };

	virtual void render(Camera const& cam) = 0;

	// modeling matrix
	glm::dmat4 const& getModelMat() const { return modelMat; };

	void setModelMat(glm::dmat4 const& aMat) { modelMat = aMat; }
	virtual void update() = 0;

protected:

	Mesh* mesh = nullptr;   // surface mesh
	glm::dmat4 modelMat;    // modeling matrix
	Texture texture;

	// transfers modelViewMat to the GPU
	virtual void uploadMvM(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class EjesRGB : public Entity 
{
public:
	EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(Camera const& cam);
	virtual void update() {};
};

//-------------------------------------------------------------------------

class Poliespiral : public Entity
{
public:
	Poliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert);
	~Poliespiral();
	virtual void render(Camera const& cam);
	virtual void update() {};
};

//-------------------------------------------------------------------------

class Dragon : public Entity
{
public:
	Dragon(GLuint numVert);
	~Dragon();
	virtual void render(Camera const& cam);
	virtual void update() {};
};

//-------------------------------------------------------------------------

class TrianguloRGB : public Entity
{
public:
	TrianguloRGB(GLdouble r);
	~TrianguloRGB();
	virtual void render(Camera const& cam);
	virtual void update() {};
};

//-------------------------------------------------------------------------

class RectanguloRGB : public Entity
{
public:
	RectanguloRGB(GLdouble w, GLdouble h);
	~RectanguloRGB();

	virtual void render(Camera const& cam);
	virtual void update() {};
};

//-------------------------------------------------------------------------

class TrianguloAnimado : public Entity {
protected:
	GLdouble angle = 0;
public:
	TrianguloAnimado(GLdouble r);
	~TrianguloAnimado();
	virtual void render(Camera const& cam);
	virtual void update();
};

//-------------------------------------------------------------------------

class Estrella3D : public Entity {
protected:
	GLdouble angle;
public:
	Estrella3D(GLdouble re, GLdouble np, GLdouble h);
	~Estrella3D();

	Texture texture;

	virtual void render(Camera const& cam);
	virtual void update();
};

//-------------------------------------------------------------------------

class Caja : public Entity {
public:
	Caja(GLdouble l);
	~Caja();

	Texture texture;

	virtual void render(Camera const& cam);
	virtual void update();
};

//-------------------------------------------------------------------------

class RectanguloTexCor : public Entity
{
public:
	RectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	~RectanguloTexCor();

	Texture texture;
	virtual void render(Camera const& cam);
	virtual void update() {};
};

//-------------------------------------------------------------------------

class Estrella3DTexCor : public Entity {
protected:
	GLdouble angle;
public:
	Estrella3DTexCor(GLdouble re, GLdouble np, GLdouble h);
	~Estrella3DTexCor();

	Texture texture;

	virtual void render(Camera const& cam);
	virtual void update() {};
};

//-------------------------------------------------------------------------

class CajaTexCor : public Entity {
public:
	CajaTexCor(GLdouble l);
	~CajaTexCor();

	Texture texture;
	Texture texture1;

	virtual void render(Camera const& cam);
	virtual void update() {};
};

//-------------------------------------------------------------------------

class ParedTexCor : public Entity {
public:
	ParedTexCor(GLdouble w, GLdouble h);
	~ParedTexCor();

	Texture texture;

	virtual void render(Camera const& cam);
	virtual void update() {};
};

//-------------------------------------------------------------------------

#endif //_H_Entities_H_