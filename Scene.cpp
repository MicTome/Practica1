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
  GLfloat as[] = { 0.3f, 0.3f, 0.3f, 1.0f };
  glLightfv(GL_LIGHT0, GL_AMBIENT, as);
  GLfloat s[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  glLightfv(GL_LIGHT0, GL_SPECULAR, s);
  GLfloat p[] = { 600.0f, 600.0f, 600.0f, 1.0f };
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
  numL = 20;
  //Numero de rodajas, 502 para completar una hipotrocoide
  numR = 502;
  a = 7;
  b = 4;
  c = 2;
  //Permite escalar la hipotrocoide y adaptar el bb8 a la misma. Solo es necesario modificar esta variable
  scaleFactor = 50.0;
  Hipotrocoide* hipo = new Hipotrocoide(numL, numR, a, b, c);
  objetos.push_back(hipo);
  hipo->setModelMat(glm::scale(hipo->getModelMat(), glm::dvec3(scaleFactor, scaleFactor, scaleFactor)));
  //Cojo la matriz de la hipotrocoide
  mat = hipo->getMesh()->getMatriz();
  //BB8
  this->creaBB8();

  //Mueve el BB8 una vez por la matriz para colocarlo
  this->moveBB8();
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

//Rota el cuerpo del objeto 2 (BB8). El cuerpo es la 3º esfera del robot
void Scene::rotateBody(){
	CompoundEntity* c = (CompoundEntity*)objetos[2];
	CompoundEntity* ce = (CompoundEntity*)c->entities[1];
	ce->setModelMat(glm::rotate(ce->getModelMat(), glm::radians(7.0), glm::dvec3(1, 0, 0)));
}

/**
Mueve el BB8 por la hipotrocoide
*/
void Scene::moveBB8(){
	if (move == numR){
		move = 0;
	}
	if (move == 1 && !inclinar){
		this->inclinaCabeza();
		inclinar = true;
	}
	CompoundEntity* bb = (CompoundEntity*)objetos[2];
	glm::dmat4 aux =(mat.at(move));
	//Cambio la ultima fila por la curva (en X 3 en la matriz)
	aux[3][0] = aux[0][3] * scaleFactor;
	aux[3][1] = aux[1][3] * scaleFactor;
	aux[3][2] = aux[2][3] * scaleFactor;

	aux[0][3] = 0.0;
	aux[1][3] = 0.0;
	aux[2][3] = 0.0;
	GLdouble factor = 1.0/ (300.0 / scaleFactor);
	bb->setModelMat(aux);
	//Los valores en negativo hacen que en x, mire hacia la izquierda y en y, deje de estar boca abajo
	bb->setModelMat(glm::scale(bb->getModelMat(), glm::dvec3(-factor, -factor, factor)));
	//bb->setModelMat(glm::scale(bb->getModelMat(), glm::dvec3(-1.0, -1.0, 1.0)));
	bb->setModelMat(glm::rotate(bb->getModelMat(), glm::radians(-45.0), glm::dvec3(0, 1, 0)));
	move++;
}

void Scene::inclinaCabeza(){
	CompoundEntity* c = (CompoundEntity*)objetos[2];
	CompoundEntity* ce = (CompoundEntity*)c->entities[0];
	ce->setModelMat(glm::rotate(ce->getModelMat(), glm::radians(30.0), glm::dvec3(1, 0, -1)));
	ce->setModelMat(glm::translate(ce->getModelMat(), glm::dvec3(25.0, 10.0, 25.0)));
}

/**
Metodo que crea un BB8
*/
void Scene::creaBB8(){

	//Entidad compuesta de BB8
	CompoundEntity* robot = new CompoundEntity();
	//Metemos el robot en los objetos de la escena
	objetos.push_back(robot);

	//Cabeza BB8
	//Para las entidades compuestas siempre se hace lo siguiente. Se crea una
	CompoundEntity* cabeza = new CompoundEntity();
	//Se introduce dentro del vector de su contenedor (en este caso robot), como se hace con robot en los objetos de Scene
	robot->entities.push_back(cabeza);
	//Se hacen las transformaciones pertinentes al objeto compuesto
	cabeza->setModelMat(glm::translate(cabeza->getModelMat(), glm::dvec3(0, 85, 0)));
	//Cramos un objeto que pertenece a la entidad compuesta (cabeza)
	RevolutionsShpere* baseCabeza = new RevolutionsShpere(50);
	//Se le da el color a la pieza
	baseCabeza->setColor(1.0, 1.0, 1.0);
	//Se mete dentro de los objetos de la cabeza. Si se necesita hacer una transformacion, se hace antes de meterla en los objetos
	cabeza->entities.push_back(baseCabeza);
	Sphere* ojo = new Sphere(5.0, 30, 30);
	ojo->setModelMat(glm::translate(ojo->getModelMat(), glm::dvec3(43, 23, 12)));
	ojo->setColor(0.0, 0.0, 0.0);
	cabeza->entities.push_back(ojo);
	Sphere* ojoGrande = new Sphere(15.0, 30, 30);
	ojoGrande->setModelMat(glm::translate(ojoGrande->getModelMat(), glm::dvec3(20, 30, 25)));
	ojoGrande->setColor(0.0, 0.0, 0.0);
	cabeza->entities.push_back(ojoGrande);

	//Cuerpo BB8
	CompoundEntity* cuerpo = new CompoundEntity();
	robot->entities.push_back(cuerpo);
	cuerpo->setModelMat(glm::rotate(cuerpo->getModelMat(), glm::radians(45.0), glm::dvec3(0, 1, 0)));
	Sphere* centro = new Sphere(90.0, 30, 30);
	centro->setColor(0.96, 0.96, 0.6); //Difiere del color beige (0.96,0.96,0.86) para que se aprecie mas en pequeño
	cuerpo->entities.push_back(centro);
	//Esfera para ver si rota el cuerpo
	Sphere* rotador = new Sphere(20, 30, 30);
	rotador->setColor(0.0, 0.0, 0.0);
	rotador->setModelMat(glm::translate(rotador->getModelMat(), glm::dvec3(0, 0, 85)));
	cuerpo->entities.push_back(rotador);
}