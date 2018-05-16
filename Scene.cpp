#include "Scene.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
	
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  

  
  //camera->setAZ();
    
  // lights
  glClearColor(0.6f, 0.7f, 0.8f, 1.0); // Fondo azul (o el que prefieras)
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0); // Light0
  GLfloat d[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
  GLfloat a[] = { 0.3f, 0.3f, 0.3f, 1.0f };
  glLightfv(GL_LIGHT0, GL_AMBIENT, a);
  GLfloat s[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  glLightfv(GL_LIGHT0, GL_SPECULAR, s);
  GLfloat p[] = { 500.0f, 500.0f, 500.0f, 1.0f };
  glLightfv(GL_LIGHT0, GL_POSITION, p);
  camera->set3D();
  // textures  
  /**
  Necesario para poder usar texturas
  */
  glEnable(GL_TEXTURE_2D);
  // objets
  objetos.push_back(new EjesRGB(200.0));
  //objetos.push_back(new Triangle(100.0));
  //objetos.push_back(new TriangleRGB(100.0));
  //objetos.push_back(new TriPyramid(100.0, 250.0));
  //objetos.push_back(new ContCubo(100.0));
  //objetos.push_back(new Diabolo(100.0, 250.0));
  //objetos.push_back(new Cubo(100.0, 100.0));
  //objetos.push_back(new Dragon(3000));
  //objetos.push_back(new Poliespiral(0.0, 0.0, 0.0, 160.0, 1.0, 1.0, 50));
  //objetos.push_back(new Poliespiral(0.0, 0.0, 0.0, 72.0, 30.0, 0.001, 5));
  //objetos.push_back(new Poliespiral(0.0, 0.0, 0.0, 60.0, 0.5, 0.5, 100));
  //objetos.push_back(new Poliespiral(0.0, 0.0, 0.0, 89.5, 0.5, 0.5, 100));
  //objetos.push_back(new Poliespiral(0.0, 0.0, 0.0, 45.0, 1.0, 1.0, 50));
  //objetos.push_back(new RectanguloTex(100.0, 100.0, 0, 0));
  //objetos.push_back(new CuboTex(50.0, 50.0, 0, 0, 50.0, 50.0, 50.0));
  //objetos.push_back(new DiaboloTex(100.0, 200.0, -200.0, 100.0, -200.0));
  //objetos.push_back(new Suelo(100.0, 100.0, 10, 10));
  //objetos.push_back(new Grass(100.0, 100.0, 0, 0, 200.0, 50.0, -200.0));
  //objetos.push_back(new GlassPot(100.0, 100.0, 0, 0, 200.0, 50.0, -200.0));
  //objetos.push_back(new Poligon(100.0, 6));
  //objetos.push_back(new MPR(50));
  Hipotrocoide* hipo = new Hipotrocoide(6, 300, 7, 4, 2);//x, 300, 70, 40, 20 (para hacerla grande, pon estos y los que hay en los metodos de la hipomesh
  objetos.push_back(hipo);

  //BB8
  //Entidad compuesta de BB8
  CompoundEntity* robot = new CompoundEntity();
  //Metemos el robot en los objetos de la escena
  objetos.push_back(robot);
  robot->modelMat = glm::rotate(robot->modelMat, glm::radians(-45.0), glm::dvec3(0, 1, 0));
  //Escala para que coincida dentro de la hipotrocoide en su tamaño original, comentar y escalar con la hipotrocoide en grande
  robot->modelMat = glm::scale(robot->modelMat, glm::dvec3(0.003, 0.003, 0.003));
  //Cabeza BB8
  RevolutionsShpere* cabeza = new RevolutionsShpere(50);
  //Se le da el color a la pieza
  cabeza->setColor(1.0, 1.0, 1.0);
  //Se coloca
  cabeza->modelMat = glm::translate(cabeza->modelMat, glm::dvec3(0, 80, 0));
  //Se mete dentr0 de los objetos del robot
  robot->entities.push_back(cabeza);
  Sphere* ojo = new Sphere(5.0, 30, 30);
  ojo->modelMat = glm::translate(ojo->modelMat, glm::dvec3(40, 110, 0));
  ojo->setColor(0.0, 0.0, 0.0);
  robot->entities.push_back(ojo);
  Sphere* ojoGrande = new Sphere(15.0, 30, 30);
  ojoGrande->modelMat = glm::translate(ojoGrande->modelMat, glm::dvec3(25, 105, 25));
  ojoGrande->setColor(0.0, 0.0, 0.0);
  robot->entities.push_back(ojoGrande);
  //Cuerpo BB8
  Sphere* cuerpo = new Sphere(90, 30, 30);
  cuerpo->setColor(1.0, 1.0, 0.75);
  robot->entities.push_back(cuerpo);

  /**
  Los objetos opacos van primero, los semitransparentes o transparentes segundos y por ultimo los translucidos
  */

}
//-------------------------------------------------------------------------

Scene::~Scene()
{ // free memory and resources 
  
  for each (Entity* it in objetos)
  {
	  delete it;
  }
}
//-------------------------------------------------------------------------

void Scene::render()
{
	glMatrixMode(GL_MODELVIEW);

	for each (Entity* it in objetos)
	{
		it->render(camera->getViewMat());
	}
	/**
	Permite añadir varios puntos de vista, en esta ocasion son 4
	*/
	/*Viewport* viewport = camera->getVP();
	viewport->setSize(viewport->getW() / 2, viewport->getH() / 2);
	int i = 0;
	for (Entity* it : objetos)
	{
		switch (i) {
		case 0:
			viewport->setPos(0, 0);
			break;
		case 1:
			viewport->setPos(viewport->getW(), 0);
			break;
		case 2:
			viewport->setPos(0, viewport->getH());
			break;
		case 3:
			viewport->setPos(viewport->getW(), viewport->getH());
			break;
		default:
			break;
		}

		it->render(camera->getViewMat());
		i++;
	}
	viewport->setSize(viewport->getW() * 2, viewport->getH() * 2);
	viewport->setPos(0, 0);*/
}
//-------------------------------------------------------------------------

/**
Metodos para poder obtener los objetos dados, en el main se llama a esta funcion y desde alli se puede llamar a las funciones de los objetos
para despues llamar al
*/
Diabolo* Scene::getDiabolo(){
	return (Diabolo*)objetos.back();
}

DiaboloTex* Scene::getDiaboloTex(){
	return (DiaboloTex*)objetos[2];
}