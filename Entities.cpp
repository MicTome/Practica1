#include "Entities.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Entity::render(dmat4 const& modelViewMat) 
{ 
	setMvM(modelViewMat); 
	draw(); 
}
//-------------------------------------------------------------------------

void Entity::draw() 
{ 
  if (mesh != nullptr) 
    mesh -> draw(); 
}
//-------------------------------------------------------------------------

void Entity::setMvM(dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
}
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Entity() 
{
  mesh = Mesh::generateAxesRGB(l);
}
//-------------------------------------------------------------------------

void EjesRGB::draw()
{
  glLineWidth(2);
  mesh->draw();
  glLineWidth(1);
}
//-------------------------------------------------------------------------

Triangle::Triangle(GLdouble l) : Entity()
{
	mesh = Mesh::generateTriangle(l);
}
//-------------------------------------------------------------------------

void Triangle::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0, 0.0, 1.0);
	glLineWidth(2);
	mesh->draw();
	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
//-------------------------------------------------------------------------

TriangleRGB::TriangleRGB(GLdouble l) : Entity()
{
	mesh = Mesh::generateTriangleRGB(l);
}
//-------------------------------------------------------------------------

void TriangleRGB::draw()
{
	glLineWidth(2);
	mesh->draw();
	glLineWidth(1);
}
//-------------------------------------------------------------------------

TriPyramid::TriPyramid(GLdouble l, GLdouble h) : Entity()
{
	mesh = Mesh::generateTriPyramid(l, h);
}
//-------------------------------------------------------------------------

void TriPyramid::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0, 0.0, 1.0);
	glLineWidth(2);
	mesh->draw();
	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

//-------------------------------------------------------------------------

ContCubo::ContCubo(GLdouble l) : Entity()
{
	mesh = Mesh::generateContCubo(l);
}
//-------------------------------------------------------------------------

void ContCubo::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0, 0.0, 1.0);
	glLineWidth(2);
	mesh->draw();
	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

Diabolo::Diabolo(GLdouble l, GLdouble h) : Entity()
{
	rotationZ = 0;
	side = l;
	height = h;
	mesh = Mesh::generateTriPyramid(side, height);
}

//-------------------------------------------------------------------------

void Diabolo::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2);
	mesh->draw();
	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Diabolo::render(dmat4 const& modelViewMat)
{
	setMvM(modelViewMat);

	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;

	aMat = rotate(aMat, radians(this->rotationZ), dvec3(0, 0, 1));
	//aMat
	glColor3f(0.0, 0.0, 1.0);
	aMat = translate(aMat, dvec3(0.0, 0.0, -this->height));
	glLoadMatrixd(value_ptr(aMat));
	draw();

	glColor3f(0.0, 1.0, 0.0);
	aMat = rotate(aMat, radians(180.0), dvec3(0, 0, 1));
	glLoadMatrixd(value_ptr(aMat));
	draw();

	glColor3f(1.0, 0.0, 0.0);
	aMat = translate(aMat, dvec3(0.0, 0.0, this->height*2));
	aMat = rotate(aMat, radians(180.0), dvec3(1, 0, 0));
	glLoadMatrixd(value_ptr(aMat));
	draw();

	glColor3f(0.0, 0.0, 0.0);
	aMat = rotate(aMat, radians(180.0), dvec3(0, 0, 1));
	glLoadMatrixd(value_ptr(aMat));
	draw();
}

void::Diabolo::rotateZ(){
	this->rotationZ += 10.0;
}


//-------------------------------------------------------------------------

Cubo::Cubo(GLdouble w, GLdouble h) : Entity()
{
	mesh = Mesh::generateRectangle(w, h);
	cubeMesh = Mesh::generateContCubo(w);
	this->h = h;
	this->w = w;
}
//-------------------------------------------------------------------------

void Cubo::draw()
{
}

void Cubo::render(dmat4 const& modelViewMat)
{
	setMvM(modelViewMat);

	glMatrixMode(GL_MODELVIEW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2);
	glColor3f(0.0, 0.0, 0.0);
	dmat4 aMat = modelViewMat * modelMat;
	cubeMesh->draw();
	
	aMat = translate(aMat, dvec3(0, -this->h/2, 0));
	aMat = rotate(aMat, radians(90.0), dvec3(1, 0, 0));
	glLoadMatrixd(value_ptr(aMat));
	mesh->draw();

	aMat = translate(aMat, dvec3(0, 0, -this->h / 2));
	aMat = rotate(aMat, radians(-90.0), dvec3(1, 0, 0));

	aMat = translate(aMat, dvec3(0, this->h, 0));
	aMat = translate(aMat, dvec3(0, -(h / 2 - (sin(radians(45.0)) * this->h) / 2), -(h / 2 - (sin(radians(45.0)) * this->h) / 2)));
	aMat = rotate(aMat, radians(45.0), dvec3(1, 0, 0));
	aMat = rotate(aMat, radians(180.0), dvec3(1, 0, 0));
	glLoadMatrixd(value_ptr(aMat));
	mesh->draw();
	
}

//-------------------------------------------------------------------------

Dragon::Dragon(GLuint numVert) : Entity()
{
	mesh = Mesh::generaDragon(numVert);
}
//-------------------------------------------------------------------------

void Dragon::draw()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0, 0.0, 1.0);
	glTranslated(-40.0, -170.0, 0.0);
	glScaled(40.0, 40.0, 1.0);
	glPointSize(2);
	mesh->draw();
	glPointSize(1);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

//-------------------------------------------------------------------------

Poliespiral::Poliespiral(GLdouble verIniX, GLdouble verIniY, GLdouble angIni, GLdouble incrAng,	GLdouble ladoIni, GLdouble incrLado, GLuint numVert) : Entity()
{
	mesh = Mesh::generaPoliespiral(verIniX, verIniY, angIni, incrAng, ladoIni, incrLado, numVert);
}
//-------------------------------------------------------------------------

void Poliespiral::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0, 0.0, 1.0);
	glLineWidth(2);
	mesh->draw();
	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

//-------------------------------------------------------------------------

Rectangulo::Rectangulo(GLdouble w, GLdouble h) : Entity()
{
	mesh = Mesh::generateRectangle(w, h);
}
//-------------------------------------------------------------------------

void Rectangulo::draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0, 0.0, 1.0);
	glLineWidth(2);
	mesh->draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

//-------------------------------------------------------------------------

RectanguloTex::RectanguloTex(GLdouble w, GLdouble h, GLuint x, GLuint y) : Entity()
{
	mesh = Mesh::generateRectangleTex(w, h, x, y);
	texture.load("..\\Bmps\\container.bmp");
}
//-------------------------------------------------------------------------

void RectanguloTex::draw()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
	texture.bind();
	mesh->draw();
	texture.unbind();
}

//-------------------------------------------------------------------------

CuboTex::CuboTex(GLdouble w, GLdouble h, GLuint x, GLuint y) : Entity()
{
    mesh = Mesh::generateRectangleTex(w, h, x, y);
    contCuboMesh = Mesh::generateCuboTex(w, h, x, y);
    this->h = h;
    this->w = w;
    texture.load("..\\Bmps\\container.bmp");
}

//-------------------------------------------------------------------------

void CuboTex::draw()
{
}

void CuboTex::render(dmat4 const& modelViewMat)
{
    setMvM(modelViewMat);
    
    //glMatrixMode(GL_MODELVIEW);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2);
    glColor3f(0.0, 0.0, 0.0);
    dmat4 aMat = modelViewMat * modelMat;
    

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    texture.bind();
    contCuboMesh->draw();
    texture.unbind();

    aMat = translate(aMat, dvec3(0, -this->h / 2, 0));
    aMat = rotate(aMat, radians(-90.0), dvec3(1, 0, 0));
    glLoadMatrixd(value_ptr(aMat));
    texture.bind();
    mesh->draw();
    texture.unbind();
	
    aMat = translate(aMat, dvec3(0, 0, this->h / 2));
    aMat = rotate(aMat, radians(90.0), dvec3(1, 0, 0));
    
    aMat = translate(aMat, dvec3(0, this->h, 0));
	aMat = rotate(aMat, radians(-90.0), dvec3(1, 0, 0));
    aMat = translate(aMat, dvec3(0, (h / 2 - (sin(radians(45.0)) * this->h) / 2), -(h / 2 - (sin(radians(45.0)) * this->h) / 2)));
	
    aMat = rotate(aMat, radians(-45.0), dvec3(1, 0, 0));
    aMat = rotate(aMat, radians(180.0), dvec3(1, 0, 0));
    glLoadMatrixd(value_ptr(aMat));
    texture.bind();
    mesh->draw();
    texture.unbind();
    
}

//-------------------------------------------------------------------------
