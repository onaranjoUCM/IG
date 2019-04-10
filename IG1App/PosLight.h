#pragma once
#include "Light.h"
#include <GL/freeglut.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

class PosLight : public Light {
protected:
	glm::fvec4 position = { 0, 0, 0, 1 }; // w=1 -> punto
public:
	PosLight() : Light() { }; // Constructora con parámetros !!!
	virtual void upload(glm::dmat4 const& modelViewMat) {
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixd(value_ptr(modelViewMat));
		glLightfv(id, GL_POSITION, value_ptr(position));
		uploadLI();
	};
	void setPos(glm::fvec3 pos) { position = glm::fvec4(pos, 1.0); };
};