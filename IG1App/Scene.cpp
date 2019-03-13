#include "Scene.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  // enable Depth test 
  glEnable(GL_TEXTURE_2D);
     
  // lights
  // textures  
  // meshes

  // Graphics objects (entities) of the scene
  //grObjects.push_back(new EjesRGB(200.0));
  //grObjects.push_back(new Poliespiral({ 0, 0 }, 0, 160, 1, 1, 50));
  //grObjects.push_back(new Dragon(3000));
  //grObjects.push_back(new TrianguloRGB(10));
  //grObjects.push_back(new RectanguloRGB(40, 20));
  //grObjects.push_back(new TrianguloAnimado(10));
  //grObjects.push_back(new Estrella3D(10, 6, 3));
  //grObjects.push_back(new Caja(10));
  // Escena3D
		RectanguloTexCor* suelo = new RectanguloTexCor(100, 100, 10, 10);
		glm::dmat4 m = suelo->getModelMat();
		m = rotate(m, radians(90.0), dvec3(1, 0, 0));
		m = translate(m, dvec3(-50, -50, 0));
		suelo->setModelMat(m);
		grObjects.push_back(suelo);

		CajaTexCor* caja = new CajaTexCor(10);
		m = caja->getModelMat();
		m = translate(m, dvec3(0, 5, 0));
		caja->setModelMat(m);
		grObjects.push_back(caja);
		
		RectanguloRGB * tapa = new RectanguloRGB(10, 10);
		m = tapa->getModelMat();
		m = translate(m, dvec3(-5, 1, -5));
		m = rotate(m, radians(90.0), dvec3(1, 0, 0));
		tapa->setModelMat(m);
		grObjects.push_back(tapa);
		
		Estrella3DTexCor* estrella1 = new Estrella3DTexCor(6, 4, 3);
		m = estrella1->getModelMat();
		m = translate(m, dvec3(0, 20, 0));
		estrella1->setModelMat(m);
		grObjects.push_back(estrella1);

		Estrella3DTexCor* estrella2 = new Estrella3DTexCor(6, 4, 3);
		m = estrella2->getModelMat();
		m = translate(m, dvec3(0, 20, 0));
		m = rotate(m, radians(180.0), dvec3(1, 0, 0));
		estrella2->setModelMat(m);
		grObjects.push_back(estrella2);

		ParedTexCor* pared = new ParedTexCor(100, 50); //PAREDES AQUI
		m = pared->getModelMat();
		m = translate(m, dvec3(0, 25, 0));
		pared->setModelMat(m);
		grObjects.push_back(pared);
}
//-------------------------------------------------------------------------

Scene::~Scene()
{ // free memory and resources   
  
  for (Entity* el: grObjects)
  {
	  delete el;  el = nullptr;
  }
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam)
{
	for (Entity* el: grObjects) {
		el->render(cam);
	}
}

//-------------------------------------------------------------------------

void Scene::update() {
	for (Entity* el : grObjects) {
		el->update();
	}
}