//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Mesh.h"
#include "DirLight.h"
#include "SpotLight.h"
#include "PosLight.h"

#include <vector>

//-------------------------------------------------------------------------

class Scene	
{ 
public:
    Scene() { };
	~Scene();
    void init(); 

    void render(Camera const& cam);
	void update();

	void escena2D();
	void escena3D();
	void escenaIlum();

protected:
	  std::vector<Entity*> grObjects;  // Entities (graphics objects) of the scene
	  DirLight* dirLight;
	  SpotLight* camLight;
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_

