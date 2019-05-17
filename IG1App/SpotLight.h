#pragma once
#include <GL/freeglut.h>

#include <glm.hpp>
#include <gtc/type_ptr.hpp>

#include "PosLight.h"

class SpotLight : public PosLight {
 protected:
  glm::fvec4 spotDir = {0.0, -1.0, 0.0, 0};

 public:
	 SpotLight() : PosLight() {};
  virtual ~SpotLight();

  virtual void upload(glm::dmat4 const &modelMat) {
	  PosLight::upload(modelMat);
	  glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(value_ptr(modelMat));
    glLightf(id, GL_SPOT_CUTOFF, 30);
    glLightf(id, GL_SPOT_EXPONENT, 4);
	glGetLightfv(id, GL_SPOT_DIRECTION, value_ptr(spotDir));
  }

  void setDir(glm::fvec3 newDir) { spotDir = glm::fvec4(newDir, 1.0); }
  void setPos(glm::fvec3 pos) { position = glm::fvec4(pos, 1.0); };
};
