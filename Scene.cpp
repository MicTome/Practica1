#include "Scene.h"

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  
  /**
  Necesario para poder usar texturas
  */
  glEnable(GL_TEXTURE_2D);
  
  camera->setAZ();
    
  // lights
  // textures  

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
  objetos.push_back(new CuboTex(100.0, 100.0, 0, 0, 50.0, 50.0, 50.0));
  objetos.push_back(new DiaboloTex(100.0, 200.0, -200.0, 100.0, -200.0));
  objetos.push_back(new Suelo(100.0, 100.0, 10, 10));
  objetos.push_back(new Grass(100.0, 100.0, 0, 0, 200.0, 50.0, -200.0));
  objetos.push_back(new GlassPot(100.0, 100.0, 0, 0, 200.0, 50.0, -200.0));

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