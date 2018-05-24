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
  numL = 6;
  numR = 252;
  a = 7;
  b = 4;
  c = 2;
  Hipotrocoide* hipo = new Hipotrocoide(numL, numR, a, b, c);//x, 300, 70, 40, 20 (para hacerla grande, pon estos y los que hay en los metodos de la hipomesh
  objetos.push_back(hipo);
  //hipo->modelMat = glm::scale(hipo->modelMat, glm::dvec3(30.0, 30.0, 30.0));
  this->route();
  //BB8
  //Entidad compuesta de BB8
  CompoundEntity* robot = new CompoundEntity();
  //Metemos el robot en los objetos de la escena
  objetos.push_back(robot);
  //robot->modelMat = glm::rotate(robot->modelMat, glm::radians(-45.0), glm::dvec3(0, 1, 0));

  //Escala para que coincida dentro de la hipotrocoide en su tamaño original, comentar y escalar con la hipotrocoide en grande
  robot->modelMat = glm::scale(robot->modelMat, glm::dvec3(0.003, 0.003, 0.003));
  robot->modelMat = glm::translate(robot->modelMat, glm::dvec3(4.8*300.0, -0.13*300.0, 0.97*300.0));
  
  //Cabeza BB8
  RevolutionsShpere* cabeza = new RevolutionsShpere(50);
  //Se le da el color a la pieza
  cabeza->setColor(1.0, 1.0, 1.0);
  //Se coloca
  cabeza->modelMat = glm::translate(cabeza->modelMat, glm::dvec3(0, 85, 0));
  //Se mete dentr0 de los objetos del robot
  robot->entities.push_back(cabeza);
  Sphere* ojo = new Sphere(5.0, 30, 30);
  ojo->modelMat = glm::translate(ojo->modelMat, glm::dvec3(50, 100, 10));
  ojo->setColor(0.0, 0.0, 0.0);
  robot->entities.push_back(ojo);
  Sphere* ojoGrande = new Sphere(15.0, 30, 30);
  ojoGrande->modelMat = glm::translate(ojoGrande->modelMat, glm::dvec3(25, 110, 25));
  ojoGrande->setColor(0.0, 0.0, 0.0);
  robot->entities.push_back(ojoGrande);
  //Cuerpo BB8
  CompoundEntity* cuerpo = new CompoundEntity();
  robot->entities.push_back(cuerpo);
  cuerpo->modelMat = glm::rotate(cuerpo->modelMat, glm::radians(45.0), glm::dvec3(0, 1, 0));
  Sphere* centro = new Sphere(90.0, 30, 30);
  centro->setColor(0.96, 0.96, 0.86);
  cuerpo->entities.push_back(centro);
  //Esfera para ver si rota el cuerpo
  Sphere* rotador = new Sphere(20, 30, 30);
  rotador->setColor(0.0, 0.0, 0.0);
  rotador->modelMat = glm::translate(rotador->modelMat, glm::dvec3(0, 0, 85));
  cuerpo->entities.push_back(rotador);

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
	CompoundEntity* ce = (CompoundEntity*)c->entities[3];
	ce->modelMat = glm::rotate(ce->modelMat, glm::radians(7.0), glm::dvec3(1, 0, 0));
}


/**Metodo para calcular el punto intermedio de los vertices de la hipotrocoide y sirve para 
obtener la ruta a seguir por el objeto
*/
void Scene::route(){
	//En vf acaba el valor final de este metodo
	vf = new glm::dvec3[numR];
	//Obtengo los vertices de la hipotrocoide
	glm::dvec3* vert = objetos[1]->mesh->getVertices();
	glm::dvec3* ve = new glm::dvec3[numR];
	glm::dvec3* v0 = new glm::dvec3[numR];
	glm::dvec3* vMit = new glm::dvec3[numR];
	
	int j = 0;
	int i = 0;
	//Recorro todos los vectores poligono a poligono cogiendo el vector 0 de esa rodaja y el de la mitad
	while (i < (numL*numR)){
		vMit[j] = vert[i + (numL/2)];
		v0[j] = vert[i];
		i += numL;
		j++;
	}
	i = 0;
	//Calculo el centro de entre esos dos vertices
	while (i < numR){
		ve[i] = (vMit[i] + v0[i]) / 2.0;
		i++;
	}
	//Calculo el vector traslacion entre el vertice actual y el siguiente
	i = 0;
	while (i < numR){
		if (i == numR-1){
			vf[i].x = ve[0].x - ve[i].x;
			vf[i].y = ve[0].y - ve[i].y;
			vf[i].z = ve[0].z - ve[i].z;
		}
		else{
			vf[i].x = ve[i + 1].x - ve[i].x;
			vf[i].y = ve[i + 1].y - ve[i].y;
			vf[i].z = ve[i + 1].z - ve[i].z;
		}
	i++;
	}
}

void Scene::moveBB8(){
	if (move >= numR){
		move = 0;
	}
	CompoundEntity* bb = (CompoundEntity*)objetos[2];
	bb->modelMat = glm::translate(bb->modelMat, glm::dvec3(vf[move].x*330.0, vf[move].y*330.0, vf[move].z*330.0));
	move++;
}