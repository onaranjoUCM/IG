#pragma once
#include <GL/freeglut.h>

#include <glm.hpp>
#include <gtc/type_ptr.hpp>

#include "PosLight.h"

class SpotLight : public PosLight {
 protected:
  glm::fvec4 spotDir = {0.0, -1.0, 0.0, 0};

 public:
  SpotLight();
  virtual ~SpotLight();

  virtual void upload(glm::dmat4 const &modelMat) {
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(value_ptr(modelMat));
    glLightf(id, GL_SPOT_CUTOFF, 90);
    glLightf(id, GL_SPOT_EXPONENT, 4);
  }

  void setDir(glm::fvec3 newDir) { spotDir = glm::fvec4(newDir, 1.0); }
};
