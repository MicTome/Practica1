//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include "Mesh.h"
#include "Texture.h"

//-------------------------------------------------------------------------

class Entity 
{
public:
  Entity() : modelMat(1.0) { };
  virtual ~Entity() { delete mesh; };

  virtual void render(glm::dmat4 const& modelViewMat);
  
protected:
  Texture texture;
  Mesh* mesh = nullptr;
  glm::dmat4 modelMat;
  virtual void draw();
  virtual void setMvM(glm::dmat4 const& modelViewMat);
};

//-------------------------------------------------------------------------

class EjesRGB : public Entity 
{
public:
  EjesRGB(GLdouble l);
  ~EjesRGB() { };
  virtual void draw();
};

//-------------------------------------------------------------------------

class Triangle : public Entity
{
public:
	Triangle(GLdouble l);
	~Triangle() { };
	virtual void draw();
};

class TriangleRGB : public Entity
{
public:
	TriangleRGB(GLdouble l);
	~TriangleRGB() { };
	virtual void draw();
};

class TriPyramid : public Entity
{
public:
	TriPyramid(GLdouble l, GLdouble h);
	~TriPyramid() { };
	virtual void draw();
};

class ContCubo : public Entity
{
public:
	ContCubo(GLdouble l);
	~ContCubo() { };
	virtual void draw();
};

class Diabolo : public Entity
{
public:
	Diabolo(GLdouble l, GLdouble h);
	~Diabolo() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void rotateZ();
private:
	GLdouble rotationZ;
	GLdouble side;
	GLdouble height;
};

class Cubo : public Entity
{
public:
	Cubo(GLdouble w, GLdouble h);
	~Cubo() { };
	virtual void draw();
	virtual void render(glm::dmat4 const& modelViewMat);
	Mesh* cubeMesh = nullptr;

private:
	GLdouble w;
	GLdouble h;
};

class Dragon : public Entity
{
public:
	Dragon(GLuint numVert);
	~Dragon() { };
	virtual void draw();
};

class Poliespiral : public Entity
{
public:
	Poliespiral(GLdouble verIniX, GLdouble verIniY, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert);
	~Poliespiral() { };
	virtual void draw();
};

class Rectangulo : public Entity
{
public:
	Rectangulo(GLdouble w, GLdouble h);
	~Rectangulo() { };
	virtual void draw();
};

class RectangleTex : public Entity
{
public:
	RectangleTex(GLdouble w, GLdouble h);
	~RectangleTex() { };
	virtual void draw();
};



#endif //_H_Entities_H_