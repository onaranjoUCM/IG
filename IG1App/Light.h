#pragma once
#include <GL/freeglut.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

class Light { // abstract class
protected:
	/*static*/ GLuint cont; // valor inicial: cont = 0
	GLuint id = GL_LIGHT0 + GL_MAX_LIGHTS; // GL_LIGHTi
public: // id: identificador interno (GPU) de la luz
	Light() {
		if (cont < GL_MAX_LIGHTS) {
			id = GL_LIGHT0 + cont;
			++cont;
		}
	};
	virtual ~Light() { disable(); }
	virtual void uploadLI() {};
	virtual void upload(glm::dmat4 const& modelViewMat) = 0;
	void disable() { if (id < GL_LIGHT0 + GL_MAX_LIGHTS) { glDisable(id); } };
	void enable() { if (id < GL_LIGHT0 + GL_MAX_LIGHTS) { glEnable(id); } };
};