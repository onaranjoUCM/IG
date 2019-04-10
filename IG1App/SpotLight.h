#pragma once
#include "PosLight.h"
#include <GL/freeglut.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

class SpotLight : public PosLight {
public:
	SpotLight();
	virtual ~SpotLight();
};

