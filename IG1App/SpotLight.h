#pragma once
#include "PosLight.h"
#include <GL/freeglut.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

class SpotLight : public PosLight {
protected:
	glm::fvec4 spotDir = { 0.0, -1.0, 0.0, 0 };
public:
	SpotLight();
	virtual ~SpotLight();

	virtual void upload(glm::dmat4 const &modelMat) {
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixd(value_ptr(modelMat));
		glLightf(id, GL_SPOT_CUTOFF, 90);
		glLightf(id, GL_SPOT_EXPONENT, 4);
		//glLightf(id, GL_SPOT_DIRECTION, value_ptr(spotDir));
		//glLightf(id, GL_POSITION, value_ptr(position));
	}

	virtual void setDir(glm::fvec3 dir) { spotDir = glm::fvec4(dir, 0); }
	virtual void setExponent(double exponent) { glLightf(id, GL_SPOT_EXPONENT, exponent); }
	virtual void setAngle(double angle) { glLightf(id, GL_SPOT_CUTOFF, angle); }
};

