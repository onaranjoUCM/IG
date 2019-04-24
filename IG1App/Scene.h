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
#include <string>

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

	void ToggleCamLight();
	void ToggleSphereLight();
	void ToggleDirLight();

protected:
	  std::vector<Entity*> grObjects;  // Entities (graphics objects) of the scene
	  std::vector<std::string> textNames = {"sun", "moon", "earth", "mars", "terreno"};
	  std::vector<Texture*> textures;
	  DirLight* dirLight;
	  SpotLight* camLight;
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_

