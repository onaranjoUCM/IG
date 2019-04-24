#include "Scene.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include "Material.h"

using namespace glm;

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(0.0, 0.0, 0.2, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  // enable Depth test 
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_CULL_FACE);
     
  // lights
  dirLight = new DirLight();
  dirLight->setDir({0, 0.25, 1});
  dirLight->uploadLI();
  dirLight->enable();

  camLight = new SpotLight();
  camLight->uploadLI();
  camLight->enable();

  // textures  
  for (int i = 0; i < textNames.size(); i++) {
	  Texture* t = new Texture();
	  t->load("Images/" + textNames[i] + ".bmp");
	  textures.push_back(t);
  }
  // meshes

  // Graphics objects (entities) of the scene
  escenaIlum();
  
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

void Scene::escena2D() {
	grObjects.clear();
	
	EjesRGB* ejes = new EjesRGB(200.0);
	grObjects.push_back(ejes);

	Poliespiral* poliespiral = new Poliespiral({ 0, 0 }, 0, 160, 1, 1, 50);
	glm::dmat4 m = ejes->getModelMat();
	m = translate(m, dvec3(50, 50, 0));
	poliespiral->setModelMat(m);
	grObjects.push_back(poliespiral);

	Dragon* dragon = new Dragon(3000);
	m = dragon->getModelMat();
	m = translate(m, dvec3(-50, 50, 0));
	dragon->setModelMat(m);
	grObjects.push_back(dragon);

	TrianguloRGB* triangulo = new TrianguloRGB(10);
	m = triangulo->getModelMat();
	m = translate(m, dvec3(50, -50, 0));
	triangulo->setModelMat(m);
	grObjects.push_back(triangulo);

	RectanguloRGB* rectangulo = new RectanguloRGB(40, 20);
	m = rectangulo->getModelMat();
	m = translate(m, dvec3(-50, -50, 0));
	rectangulo->setModelMat(m);
	grObjects.push_back(rectangulo);

	TrianguloAnimado* tAnimado = new TrianguloAnimado(10);
	m = tAnimado->getModelMat();
	m = translate(m, dvec3(0, -50, 0));
	tAnimado->setModelMat(m);
	tAnimado->modelMatIni = m;
	grObjects.push_back(tAnimado);

	Estrella3D* estrella = new Estrella3D(10, 6, 3);
	m = estrella->getModelMat();
	m = translate(m, dvec3(-50, 0, 0));
	estrella->setModelMat(m);
	estrella->modelMatIni = m;
	grObjects.push_back(estrella);

	Caja* caja = new Caja(10);
	m = caja->getModelMat();
	m = translate(m, dvec3(0, 50, 0));
	caja->setModelMat(m);
	grObjects.push_back(caja);
}

void Scene::escena3D() {
	grObjects.clear();
	RectanguloTexCor* suelo = new RectanguloTexCor(100, 100, 10, 10);
	glm::dmat4 m = suelo->getModelMat();
	m = rotate(m, radians(90.0), dvec3(1, 0, 0));
	m = translate(m, dvec3(-50, -50, 0));
	suelo->setModelMat(m);
	grObjects.push_back(suelo);

	CajaTexCor* caja = new CajaTexCor(10);
	m = caja->getModelMat();
	m = translate(m, dvec3(20, 5, 20));
	caja->setModelMat(m);
	grObjects.push_back(caja);

	RectanguloRGB * tapa = new RectanguloRGB(10, 10);
	m = tapa->getModelMat();
	m = translate(m, dvec3(15, 1, 15));
	m = rotate(m, radians(90.0), dvec3(1, 0, 0));
	tapa->setModelMat(m);
	grObjects.push_back(tapa);

	Estrella3DTexCor* estrella3D = new Estrella3DTexCor(6, 4, 3);
	m = estrella3D->getModelMat();
	m = translate(m, dvec3(20, 20, 20));
	estrella3D->setModelMat(m);
	estrella3D->modelMatIni = m;
	grObjects.push_back(estrella3D);

	Foto* foto = new Foto(50, 25, 1, 1);
	m = foto->getModelMat();
	m = translate(m, dvec3(-25, 1, -10));
	m = rotate(m, radians(90.0), dvec3(1, 0, 0));
	foto->setModelMat(m);
	grObjects.push_back(foto);

	ParedTexCor* pared = new ParedTexCor(100, 50);
	m = pared->getModelMat();
	m = translate(m, dvec3(0, 25, 0));
	pared->setModelMat(m);
	grObjects.push_back(pared);
}

void Scene::escenaIlum() {
	grObjects.clear();
	
	EjesRGB* ejes = new EjesRGB(200.0);
	grObjects.push_back(ejes);
	/*
	RectanguloTexCor* suelo = new RectanguloTexCor(100, 100, 10, 10);
	glm::dmat4 m = suelo->getModelMat();
	m = rotate(m, radians(90.0), dvec3(1, 0, 0));
	m = translate(m, dvec3(-50, -50, 0));
	suelo->setModelMat(m);
	grObjects.push_back(suelo);
	*/
	Esfera* tierra = new Esfera(10, "Images/earth.bmp");
	Material pewter = Material();
	pewter.setPewter();
	tierra->setMaterial(pewter);
	glm::dmat4 m = tierra->getModelMat();
	m = translate(m, dvec3(0, 100, 0));
	tierra->setModelMat(m);
	grObjects.push_back(tierra);

	Esfera* luna = new Esfera(20, "Images/moon.bmp");
	Material silver = Material();
	silver.setSilver();
	luna->setMaterial(silver);
	m = luna->getModelMat();
	m = translate(m, dvec3(-100, 100, 0));
	luna->setModelMat(m);
	grObjects.push_back(luna);

	Esfera* marte = new Esfera(30, "Images/mars.bmp");
	Material copper = Material();
	silver.setCopper();
	marte->setMaterial(copper);
	m = marte->getModelMat();
	m = translate(m, dvec3(100, 100, 0));
	marte->setModelMat(m);
	grObjects.push_back(marte);

	Esfera* sol = new Esfera(50, "Images/sun.bmp");
	Material gold = Material();
	gold.setGold();
	sol->setMaterial(gold);
	m = sol->getModelMat();
	m = translate(m, dvec3(0, 200, 0));
	sol->setModelMat(m);
	grObjects.push_back(sol);

	Esfera* jupiter = new Esfera(200, "Images/terreno.bmp");
	Material brass = Material();
	brass.setBrass();
	jupiter->setMaterial(brass);
	m = jupiter->getModelMat();
	m = translate(m, dvec3(0, -200, 200));
	jupiter->setModelMat(m);
	grObjects.push_back(jupiter);
}

void Scene::ToggleCamLight() {
	if (camLight->enabled) {
		camLight->disable();
		camLight->enabled = false;
	}
	else {
		camLight->enable();
		camLight->enabled = true;
	}
}

void Scene::ToggleSphereLight() {}

void Scene::ToggleDirLight() {
	if (dirLight->enabled) {
		dirLight->disable();
		dirLight->enabled = false;
	}
	else {
		dirLight->enable();
		dirLight->enabled = true;
	}
}
