//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include <vector>
#include "Camera.h"
#include "Entities.h"

//-------------------------------------------------------------------------

class Scene	: public CompoundEntity
{ 
public:
    Scene(Camera* cam): camera(cam) { };
	  ~Scene();
    void init();
	  void render();    
	  Diabolo* getDiabolo();
	  DiaboloTex* getDiaboloTex();
	  void rotateBody();
	  void route();
	  void moveBB8();
protected:
	  glm::dvec3* vf;
	  Camera* camera;
	  int move = 0, numL, numR;
	  int a, b, c;
	  std::vector<Entity*> objetos;
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_

