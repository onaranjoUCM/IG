#pragma once
#include <GL/freeglut.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

class Light { // abstract class
protected:
  static GLuint cont;                // valor inicial: cont = 0
  GLuint id = GL_LIGHT0 + GL_MAX_LIGHTS; // GL_LIGHTi
  glm::fvec4 ambient = {0.1, 0.1, 0.1, 1};
  glm::fvec4 diffuse = {0.5, 0.5, 0.5, 1};
  glm::fvec4 specular = {0.5, 0.5, 0.5, 1};

public: // id: identificador interno (GPU) de la luz
	bool enabled = false;
  Light() {
    if (cont < GL_MAX_LIGHTS) {
      id = GL_LIGHT0 + cont;
      ++cont;
    }
  };
  virtual ~Light() { disable(); }
  virtual void uploadLI() {
    glLightfv(id, GL_AMBIENT, value_ptr(ambient));
    glLightfv(id, GL_DIFFUSE, value_ptr(diffuse));
    glLightfv(id, GL_SPECULAR, value_ptr(specular));
  };
  void setAmb(glm::fvec4 amb) { ambient = amb; }
  virtual void upload(glm::dmat4 const &modelViewMat) = 0;

  void disable() {
    if (id < GL_LIGHT0 + GL_MAX_LIGHTS) {
      glDisable(id);
    }
  };

  void enable() {
    if (id < GL_LIGHT0 + GL_MAX_LIGHTS) {
      glEnable(id);
    }
  };
};
