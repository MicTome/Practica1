#include "Entities.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include <stdio.h>

using namespace glm;

//-------------------------------------------------------------------------

void Entity::render(dmat4 const& modelViewMat) 
{ 
	setMvM(modelViewMat); 
	//da el color si le has dado alguno
	glColor3f(re,gr,bl);
	draw(); 
}
//-------------------------------------------------------------------------

void Entity::draw() 
{ 
  if (mesh != nullptr) 
    mesh -> draw(); 
}

/**Metodo para cambiar el color de la matriz de Entity
*/
void Entity::setColor(GLfloat x, GLfloat y, GLfloat z)
{
	re = x;
	gr = y;
	bl = z;
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
	/**
	Se dibuja el objeto con lineas del color dado y el grosor, por delante y por detras
	*/
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0, 0.0, 1.0);
	glLineWidth(2);
	mesh->draw();
	glLineWidth(1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

Poligon::Poligon(GLdouble r, int n) : Entity()
{
	mesh = Mesh::generatePoligon(r, n);
	rectangle = Mesh::generateRectangleTex(r, 100.0, 0, 0);
	texture.load("..\\Bmps\\picos.bmp");
}
//-------------------------------------------------------------------------

void Poligon::draw()
{
	/**
	Se dibuja el objeto con lineas del color dado y el grosor, por delante y por detras
	*/
	
	
}

void Poligon::render(dmat4 const& modelViewMat)
{
	setMvM(modelViewMat);

	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);
	//Solo por el frente, por detras se queda invisible (no se ve)
	glCullFace(GL_BACK);
	//Enlaza la textura con el objeto
	
	glLineWidth(4);
	glColor3f(0.0, 0.0, 0.0);
	dmat4 aMat = modelViewMat * modelMat;
	texture.bind();
	mesh->draw();
	texture.unbind();
	//Se traslada y se crea una de las piramides
	aMat = translate(aMat, dvec3(0.0, 0.0, 100.0));
	glLoadMatrixd(value_ptr(aMat));
	texture.bind();
	mesh->draw();
	texture.unbind();
	aMat = scale(aMat, dvec3(1.0, 0.5, 1.0));
	aMat = rotate(aMat, radians(90.0), dvec3(1, 0, 0));
	aMat = translate(aMat, dvec3(0.0, -50.0, -175.0));
	glLoadMatrixd(value_ptr(aMat));
	glCullFace(GL_FRONT);
	texture.bind();
	rectangle->draw();
	texture.unbind();
	aMat = scale(aMat, dvec3(1.0, 1.0, 2.0));
	aMat = rotate(aMat, radians(-120.0), dvec3(0, 1, 0));
	aMat = translate(aMat, dvec3(75.0, 0.0, 40.0));
	glLoadMatrixd(value_ptr(aMat));
	texture.bind();
	rectangle->draw();
	texture.unbind();
	aMat = translate(aMat, dvec3(75.0, 0.0, -40.0));
	aMat = rotate(aMat, radians(-120.0), dvec3(0, 1, 0));
	
	glLoadMatrixd(value_ptr(aMat));
	texture.bind();
	rectangle->draw();
	texture.unbind();

	aMat = rotate(aMat, radians(-120.0), dvec3(0, 1, 0));
	aMat = translate(aMat, dvec3(75.0, 0.0, 45.0));
	glLoadMatrixd(value_ptr(aMat));
	texture.bind();
	rectangle->draw();
	texture.unbind();

	aMat = translate(aMat, dvec3(75.0, 0.0, -42.0));
	aMat = rotate(aMat, radians(-120.0), dvec3(0, 1, 0));
	glLoadMatrixd(value_ptr(aMat));
	texture.bind();
	rectangle->draw();
	texture.unbind();
	aMat = translate(aMat, dvec3(-75.0, 0.0, 45.0));
	aMat = rotate(aMat, radians(-120.0), dvec3(0, 1, 0));
	glLoadMatrixd(value_ptr(aMat));
	texture.bind();
	rectangle->draw();
	texture.unbind();
	glLineWidth(1);
	
	glDisable(GL_CULL_FACE);
	
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

/**
Para crear cualquier objeto, se llama a su mesh para crearlo
l: lado
h: altura
*/
TriPyramid::TriPyramid(GLdouble l, GLdouble h) : Entity()
{
	mesh = Mesh::generateTriPyramid(l, h);
}
//-------------------------------------------------------------------------

/**
En los draw se dibujan los objetos, a no ser que tenga un render
*/
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

/**
l: lado
h: altura
*/
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

/**
render para generar un diabolo real, dado que en el constructor solo tienes una tripiramide
*/
void Diabolo::render(dmat4 const& modelViewMat)
{
	setMvM(modelViewMat);

	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;

	aMat = rotate(aMat, radians(this->rotationZ), dvec3(0, 0, 1));
	//Se traslada y se crea una de las piramides
	glColor3f(0.0, 0.0, 1.0);
	aMat = translate(aMat, dvec3(0.0, 0.0, -this->height));
	glLoadMatrixd(value_ptr(aMat));
	draw();

	//Se crea la segunda piramide del mismo lado
	glColor3f(0.0, 1.0, 0.0);
	aMat = rotate(aMat, radians(180.0), dvec3(0, 0, 1));
	glLoadMatrixd(value_ptr(aMat));
	draw();
	
	//Se crea la tercera, rotando y trasladando para estar punta con punta
	glColor3f(1.0, 0.0, 0.0);
	aMat = translate(aMat, dvec3(0.0, 0.0, this->height*2));
	aMat = rotate(aMat, radians(180.0), dvec3(1, 0, 0));
	glLoadMatrixd(value_ptr(aMat));
	draw();

	//La ultima que se junta con la anterior
	glColor3f(0.0, 0.0, 0.0);
	aMat = rotate(aMat, radians(180.0), dvec3(0, 0, 1));
	glLoadMatrixd(value_ptr(aMat));
	draw();
}

void::Diabolo::rotateZ(){
	this->rotationZ += 10.0;
}


//-------------------------------------------------------------------------

/**
w: ancho
h: altura
Deberian ser siempre los mismos
Tienes un mes con un rectangulo y cun cubomesh con el cubo
*/
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

	//Dibujamos los laterales del cubo
	glMatrixMode(GL_MODELVIEW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2);
	glColor3f(0.0, 0.0, 0.0);
	dmat4 aMat = modelViewMat * modelMat;
	cubeMesh->draw();
	
	//Dibujamos la base del cubo
	aMat = translate(aMat, dvec3(0, -this->h/2, 0));
	aMat = rotate(aMat, radians(90.0), dvec3(1, 0, 0));
	glLoadMatrixd(value_ptr(aMat));
	mesh->draw();

	//Dibujamos la tapa inclinada del mismo, trasladando y rotando hasta conseguir la inclinacion adecuada
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
/**
l: lado
h: altura
x: numero de veces que se repite la textura en x
y: igual que el de arriba con y
Se carga la textura colocada en esa ruta
*/
RectanguloTex::RectanguloTex(GLdouble w, GLdouble h, GLuint x, GLuint y) : Entity()
{
	mesh = Mesh::generateRectangleTex(w, h, x, y);
	texture.load("..\\Bmps\\container2.bmp");
}
//-------------------------------------------------------------------------

void RectanguloTex::draw()
{
	//Activa el uso de texturas en el objeto
    glEnable(GL_CULL_FACE);
	//Solo por el frente, por detras se queda invisible (no se ve)
    glCullFace(GL_FRONT);
	//Enlaza la textura con el objeto
	texture.bind();
	mesh->draw();
	//La desenlaza
	texture.unbind();
}

//-------------------------------------------------------------------------

/**
l: lado
h: altura
x: veces que se repite la textura en x
y: veces que se repite la textura en y
xt: valor de traslacion en x
yt: valor de traslacion en y
zt: valor de traslacion en z
Este cubo es exactamente como el anterior, pero se añaden dos texturas con texture (la basica) e intTex (la del cubo)
*/
CuboTex::CuboTex(GLdouble w, GLdouble h, GLuint x, GLuint y, GLdouble xt, GLdouble yt, GLdouble zt) : Entity()
{
    mesh = Mesh::generateRectangleTex(w, h, x, y);
    contCuboMesh = Mesh::generateCuboTex(w, h, x, y);
    this->h = h;
    this->w = w;
	this->translateX = xt;
	this->translateY = yt;
	this->translateZ = zt;
	texture.load("..\\Bmps\\container2.bmp");
	intTex.load("..\\Bmps\\picos.bmp");
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
	aMat = translate(aMat, dvec3(this->translateX, this->translateY, this->translateZ));
	glLoadMatrixd(value_ptr(aMat));
	//En cada parte del objeto que se va a dibujar, se coloca la textura indicada en la cara que se quiera
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    texture.bind();
    contCuboMesh->draw();
    texture.unbind();

	glCullFace(GL_BACK);
	intTex.bind();
	contCuboMesh->draw();
	intTex.unbind();

    aMat = translate(aMat, dvec3(0, -this->h / 2, 0));
    aMat = rotate(aMat, radians(-90.0), dvec3(1, 0, 0));
    glLoadMatrixd(value_ptr(aMat));
	glCullFace(GL_FRONT);
    texture.bind();
    mesh->draw();
    texture.unbind();
	glCullFace(GL_BACK);
	intTex.bind();
	mesh->draw();
	intTex.unbind();
	
    aMat = translate(aMat, dvec3(0, 0, this->h / 2));
    aMat = rotate(aMat, radians(90.0), dvec3(1, 0, 0));
    
    aMat = translate(aMat, dvec3(0, this->h, 0));
	aMat = rotate(aMat, radians(-90.0), dvec3(1, 0, 0));
    aMat = translate(aMat, dvec3(0, (h / 2 - (sin(radians(45.0)) * this->h) / 2), -(h / 2 - (sin(radians(45.0)) * this->h) / 2)));
	
    aMat = rotate(aMat, radians(-45.0), dvec3(1, 0, 0));
    aMat = rotate(aMat, radians(180.0), dvec3(1, 0, 0));
    glLoadMatrixd(value_ptr(aMat));
	glCullFace(GL_FRONT);
    texture.bind();
    mesh->draw();
    texture.unbind();
	glCullFace(GL_BACK);
	intTex.bind();
	mesh->draw();
	intTex.unbind();
    
	glDisable(GL_CULL_FACE);
}

//-------------------------------------------------------------------------

/**
l: lado
h: altura
Se añade la textura
*/
TriPyramidTex::TriPyramidTex(GLdouble l, GLdouble h) : Entity()
{
	mesh = Mesh::generateTriPyramidTex(l, h);
	texture.load("..\\Bmps\\floris.bmp");
}

//-------------------------------------------------------------------------

void TriPyramidTex::draw()
{
}

//-------------------------------------------------------------------------

/**
l: lado
h: altura
xt: traslacion en x
yt: traslacion en y
zt: traslacion en z
*/
DiaboloTex::DiaboloTex(GLdouble r, GLdouble h, GLdouble xt, GLdouble yt, GLdouble zt) : Entity()
{
	rotationZ = 0;
	radius = r;
	height = h;
	mesh = Mesh::generateTriPyramidTex(r, h);
	this->translateX = xt;
	this->translateY = yt;
	this->translateZ = zt;
	texture.load("..\\Bmps\\earth24.bmp");
}

//-------------------------------------------------------------------------

/**
Se puede hacer en el render, objeto a objeto, pero aqui, se pone la textura en cada cara, delante y detras
*/
void DiaboloTex::draw()
{
	glEnable(GL_CULL_FACE);

	glCullFace(GL_FRONT);
	texture.bind();
	mesh->draw();
	texture.unbind();

	glCullFace(GL_BACK);
	texture.bind();
	mesh->draw();
	texture.unbind();
	glDisable(GL_CULL_FACE);
}

//-------------------------------------------------------------------------

void DiaboloTex::render(dmat4 const& modelViewMat)
{
	setMvM(modelViewMat);


	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;

	aMat = translate(aMat, dvec3(this->translateX, this->translateY, this->translateZ));
	glLoadMatrixd(value_ptr(aMat));

	aMat = rotate(aMat, radians(this->rotationZ), dvec3(0, 0, 1));
	//aMat
	//glColor3f(0.0, 0.0, 1.0);
	aMat = translate(aMat, dvec3(0.0, 0.0, -this->height));
	glLoadMatrixd(value_ptr(aMat));
	draw();

	//glColor3f(0.0, 1.0, 0.0);
	aMat = rotate(aMat, radians(180.0), dvec3(0, 0, 1));
	glLoadMatrixd(value_ptr(aMat));
	draw();

	//glColor3f(1.0, 0.0, 0.0);
	aMat = translate(aMat, dvec3(0.0, 0.0, this->height * 2));
	aMat = rotate(aMat, radians(180.0), dvec3(1, 0, 0));
	glLoadMatrixd(value_ptr(aMat));
	draw();

	//glColor3f(0.0, 0.0, 0.0);
	aMat = rotate(aMat, radians(180.0), dvec3(0, 0, 1));
	glLoadMatrixd(value_ptr(aMat));
	draw();
}

void::DiaboloTex::rotateZ() {
	this->rotationZ += 10.0;
}

//-------------------------------------------------------------------------

/**
l: lado
h: altura
x: veces que se repite la textura en x
y: veces que se repite la textura en y
*/
Suelo::Suelo(GLdouble w, GLdouble h, GLuint x, GLuint y) : Entity()
{
	mesh = Mesh::generateRectangleTex(w, h, x, y);
	this->scaleX = x;
	this->scaleY = y;
	texture.load("..\\Bmps\\baldosa1.bmp");
}
//-------------------------------------------------------------------------

void Suelo::draw()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	texture.bind();
	mesh->draw();
	texture.unbind();
	glDisable(GL_CULL_FACE);
}

//-------------------------------------------------------------------------

void Suelo::render(dmat4 const& modelViewMat)
{
	setMvM(modelViewMat);

	//Se escala y se gira el suelo
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	aMat = scale(aMat, dvec3((GLdouble)this->scaleX, 1.0, (GLdouble)this->scaleY));
	aMat = rotate(aMat, radians(90.0), dvec3(1, 0, 0));
	glLoadMatrixd(value_ptr(aMat));
	draw();
}

/**
w: lado
h: altura
x: repeticion de la textura en x
y: repeticion de la textura en y
xt, yt, zt: traslaciones

Es un cubo de cristal
*/
GlassPot::GlassPot(GLdouble w, GLdouble h, GLuint x, GLuint y, GLdouble xt, GLdouble yt, GLdouble zt) : Entity()
{
	mesh = Mesh::generateCuboTex(w, h, x, y);
	this->h = h;
	this->w = w;
	this->translateX = xt;
	this->translateY = yt;
	this->translateZ = zt;
	//alpha a 100 para hacerlo transparente
	texture.load("..\\Bmps\\window.bmp", 100);
}

//-------------------------------------------------------------------------

void GlassPot::draw()
{
}

void GlassPot::render(dmat4 const& modelViewMat)
{
	//Se activa el blend para poder cambiar el canal de alpha
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	setMvM(modelViewMat);
	dmat4 aMat = modelViewMat * modelMat;
	aMat = scale(aMat, dvec3(2.0, 2.0, 2.0));
	aMat = translate(aMat, dvec3(this->translateX, this->translateY, this->translateZ));
	glLoadMatrixd(value_ptr(aMat));
	texture.bind();
	mesh->draw();
	texture.unbind();
	glDisable(GL_BLEND);
}

/**
w: lado
h: altura
x: repeticion de la textura en x
y: repeticion de la textura en y
xt, yt, zt: traslaciones

Hierba sin el blanco
*/
Grass::Grass(GLdouble w, GLdouble h, GLuint x, GLuint y, GLdouble xt, GLdouble yt, GLdouble zt) : Entity()
{
	mesh = Mesh::generateRectangleTex(w, h, x, y);
	this->translateX = xt;
	this->translateY = yt;
	this->translateZ = zt;
	texture.load("..\\Bmps\\grass.bmp", ivec3(0.0, 0.0, 0.0));
	//Necesario si quieres quitar los limites en color que provoca el uso de G_REPEAT
	texture.wrap(GL_CLAMP);
}
//-------------------------------------------------------------------------

void Grass::draw()
{

}

//-------------------------------------------------------------------------

void Grass::render(dmat4 const& modelViewMat)
{
	setMvM(modelViewMat);
	//Se activa el blend para poder hacer trasparencias
	//Se desactiva la mascara (la cual provoca que se mezclen los colores de la textura actual con la del fondo)
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	//Por defecto son 0 y 1
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;

	aMat = scale(aMat, dvec3((2.0, 2.0, 2.0)));
	aMat = translate(aMat, dvec3(this->translateX, this->translateY, this->translateZ));
	aMat = rotate(aMat, radians(45.0), dvec3(0, 1, 0));
	glLoadMatrixd(value_ptr(aMat));
	texture.bind();
	mesh->draw();
	texture.unbind();

	aMat = rotate(aMat, radians(90.0), dvec3(0, 1, 0));
	glLoadMatrixd(value_ptr(aMat));
	
	texture.bind();
	mesh->draw();
	texture.unbind();
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
}

/**Cono por revolucion. El perfil dibuja el cono
*/
MPR::MPR(int n) : Entity() {
	this->m = 3; //número de puntos del perfil
	this->n = n;
	dvec3* perfil = new dvec3[3];
	perfil[0] = dvec3(0.0, 0.0, 0.0);
	perfil[1] = dvec3(50.0, 0.0, 0.0);
	perfil[2] = dvec3(0.0, 100.0, 0.0);
	this->mesh = Mesh::generaMallaPorRevolucion(m, n, perfil);
}

void MPR::draw() {
	dvec3* vertices = mesh->getVertices();
	dvec4* colors = mesh->getColours();
	mesh->normalize(m, n);
	dvec3* normals = mesh->getNormals();


	glColor3f(1.0, 0.0, 0.0);
	if (vertices != nullptr) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vertices);
		if (colors != nullptr) {
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_DOUBLE, 0, colors);
		}
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_DOUBLE, 0, normals);
		// Después del dibujo de los elementos por índices,
		// se deshabilitan los vertex arrays, como es habitual
		// Definición de las caras
		for (int i = 0; i < n; i++){ // Unir el perfil i-ésimo con el (i+1)%n-ésimo
			for (int j = 0; j < m - 1; j++) { // Esquina inferior-izquierda de una cara
				int indice = i*m + j;
				unsigned int stripIndices[] =
				{ indice, std::fmod((indice + m), (n*m)),
				std::fmod((indice + m + 1), (n*m)), indice + 1 };
				glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, stripIndices);
				// o GL_POLYGON, si se quiere las caras con relleno
			}
		}
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}
/**nP numero de lados del poligono
nQ numero de rodajas
a, b, c valores de la curva
*/
Hipotrocoide::Hipotrocoide(int nP, int nQ, GLfloat a, GLfloat b, GLfloat c) : Entity()
{
	this->nP = nP;
	this->nQ = nQ;
	this->a = a;
	this->b = b;
	this->c = c;
	re = 1.0;
	gr = 0.0;
	bl = 0.0;
	this->setColor(re, gr, bl);
	mesh = new HipoMesh(this->nP, this->nQ, this->a, this->b, this->c);
}

void Hipotrocoide::draw() {
	
	//glColor3f(re, gr, bl);
	this->mesh->draw();
}

Sphere::Sphere(GLdouble l, int meridianos, int paralelos) : QuadricEntity() {
	r = l;
	m = meridianos;
	p = paralelos;
	sphere = gluNewQuadric();
	//gluQuadricTexture(sphere, GLU_TRUE);
	//texture.load("..\\Bmps\\window.bmp");
}

void Sphere::draw() {
	//this->setColor(res, grs, bls);
	//glColor3f(re, gr, bl);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	//texture.bind(GL_MODULATE);
	gluSphere(sphere, r, m, p);
	//texture.unbind();
}

Cylinder::Cylinder(GLdouble baseRadio, GLdouble topRadio, GLdouble altura, int lados, int rodajas) : QuadricEntity() {
	br = baseRadio;
	tr = topRadio;
	h = altura;
	l = lados;
	r = rodajas;
	cylinder = gluNewQuadric();
	//gluQuadricTexture(sphere, GLU_TRUE);
	//texture.load("..\\Bmps\\window.bmp");
}

void Cylinder::draw() {
	//this->setColor(res, grs, bls);
	//glColor3f(re, gr, bl);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	//texture.bind(GL_MODULATE);
	gluCylinder(cylinder, br, tr, h, l, r);
	//texture.unbind();
}

Disk::Disk(GLdouble intRadio, GLdouble extRadio, int lados, int anillos) : QuadricEntity() {
	ir = intRadio;
	or = extRadio;
	l = lados;
	r = anillos;
	disk = gluNewQuadric();
	//gluQuadricTexture(disk, GLU_TRUE);
	//texture.load("..\\Bmps\\window.bmp");
}

void Disk::draw() {
	//this->setColor(res, grs, bls);
	//glColor3f(re, gr, bl);
	gluQuadricDrawStyle(disk, GLU_FILL);
	//texture.bind(GL_MODULATE);
	gluDisk(disk, ir, or, l, r);
	//texture.unbind();
}

PartialDisk::PartialDisk(GLdouble intRadio, GLdouble extRadio, int lados, int anillos, GLdouble startAngle, GLdouble sweepAngle) : QuadricEntity() {
	ir = intRadio;
	or = extRadio;
	l = lados;
	r = anillos;
	sta = startAngle;
	swa = sweepAngle;
	pdisk = gluNewQuadric();
	//gluQuadricTexture(pdisk, GLU_TRUE);
	//texture.load("..\\Bmps\\window.bmp");
}

void PartialDisk::draw() {
	//this->setColor(res, grs, bls);
	//glColor3f(re, gr, bl);
	gluQuadricDrawStyle(pdisk, GLU_FILL);
	//texture.bind(GL_MODULATE);
	gluPartialDisk(pdisk, ir, or, l, r, sta, swa);
	//texture.unbind();
}

void CompoundEntity::draw(){
	
}

/**Esta clase sirve como array del resto de entidades menores.
render dibuja la matriz de cada uno 
**Mirar al principio de los comentarios largos para ver la estructura de herencias**
*/
void CompoundEntity::render(dmat4 const& modelViewMat){
	setMvM(modelViewMat);
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	for each (Entity* it in entities) {
		it->render(aMat);
	}
}

/**Circunfenrencia rota para la cabeza
el perfil dibuja una curva hecha a mano
*/
RevolutionsShpere::RevolutionsShpere(int n) : Entity() {
	this->m = 22; //número de puntos del perfil
	this->n = n;
	dvec3* perfil = new dvec3[22];
	perfil[0] = dvec3(0.0, 0.0, 0.0);
	perfil[1] = dvec3(45.0, 0.0, 0.0);
	perfil[2] = dvec3(50.0, 5.0, 0.0);
	perfil[3] = dvec3(50.0, 12.0, 0.0);
	perfil[4] = dvec3(49.5, 17.0, 0.0);
	perfil[5] = dvec3(49.0, 19.0, 0.0);
	perfil[6] = dvec3(48.5, 21.0, 0.0);
	perfil[7] = dvec3(47.2, 23.0, 0.0);
	perfil[8] = dvec3(46.7, 25.0, 0.0);
	perfil[7] = dvec3(46.2, 27.0, 0.0);
	perfil[8] = dvec3(45.0, 29.0, 0.0);
	perfil[9] = dvec3(43.8, 31.0, 0.0);
	perfil[10] = dvec3(42.0, 33.0, 0.0);
	perfil[11] = dvec3(40.0, 35.0, 0.0);
	perfil[12] = dvec3(37.5, 37.0, 0.0);
	perfil[13] = dvec3(35.0, 39.0, 0.0);
	perfil[14] = dvec3(32.5, 41.0, 0.0);
	perfil[15] = dvec3(29.5, 43.0, 0.0);
	perfil[16] = dvec3(25.0, 45.0, 0.0);
	perfil[17] = dvec3(20.0, 47.0, 0.0);
	perfil[18] = dvec3(15.0, 49.0, 0.0);
	perfil[19] = dvec3(9.5, 50.0, 0.0);
	perfil[20] = dvec3(4.0, 51.0, 0.0);
	perfil[21] = dvec3(0.0, 51.5, 0.0);
	this->mesh = Mesh::generaMallaPorRevolucion(m, n, perfil);
}

void RevolutionsShpere::draw() {
	dvec3* vertices = mesh->getVertices();
	mesh->normalize(m, n);
	//this->setColor(res, grs, bls);
	//glColor3f(re, gr, bl);
	dvec3* normals = mesh->getNormals();
	if (vertices != nullptr) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vertices);

		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_DOUBLE, 0, normals);
		// Después del dibujo de los elementos por índices,
		// se deshabilitan los vertex arrays, como es habitual
		// Definición de las caras
		for (int i = 0; i < n; i++){ // Unir el perfil i-ésimo con el (i+1)%n-ésimo
			for (int j = 0; j < m - 1; j++) { // Esquina inferior-izquierda de una cara
				int indice = i*m + j;
				unsigned int stripIndices[] =
				{ indice, std::fmod((indice + m), (n*m)),
				std::fmod((indice + m + 1), (n*m)), indice + 1 };
				glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, stripIndices);
				// o GL_POLYGON, si se quiere las caras con relleno
			}
		}
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

/**En cuanto a la organizacion de las clases

Padre: Entity
Hijos de Etity: CompoundEntity, QuadricEntity, el resto
Hijos de CompundEntity: Scene
Hijos de QuadricEntity: Shpere, Cylinder, Disk, PartialDisk

*/



/**
Para transparencias se utiliza la componente Alpha de los colores
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
Si el fragmento en curso pasa el test de profundidad y
- es opaco (srcA = 1) -> srcBF =1 y dstBF = 0
reemplaza al color del buffer
- es transparente (srcA=0) -> srcBF =0 y dstBF = 1
el color del buffer no se modifica
- es translucido (srcA=0.5) -> srcBF = dstBF = 0.5
el color del buffer se multiplica por 0.5 y se suma el del fragmento
también multiplicado por 0.5

 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
Rectángulos: rojo translúcido (cercano), azul translúcido (lejano) y
verde opaco (en medio)

Orden de renderizado con objetos opacos y traslúcidos
1- Test de profundidad activado por defecto
Dibujar los objetos opacos
2- Usar el buffer de profundidad solo para lectura:
glDepthMask(GL_FALSE);
realiza el test pero no modifica el Z-Buffer
Dibujar los objetos traslúcidos
Los que están delante de los opacos mezclarán el color
3- glDepthMask(GL_TRUE)

El Frame Buffer consta de varios buffers del mismo tamaño
1. Colors buffers: front and back
2. Depth buffer: depth test
3. Stencil buffer: stencil test
Se configura al crear la ventana
glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH |
GLUT_STENCIL);
Se reinician a los valores establecidos
glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |
GL_STENCIL_BUFFER_BIT);
Los test permiten descartar fragmentos para que no aporten color al
Color Buffer. Primero se ejecuta el Depth Test, y después el Stencil Test.
Se pueden utilizar frame buffer auxiliares (Frame Buffer Objects)

Activar la escritura en el Stencil Buffer.
2. Renderizar objetos escribiendo solo en el stencil buffer
Desactivar la escritura en el Stencil buffer.
4. Renderizar objetos utilizando el contenido del Stencil buffer con el test


Ejemplos: Reflejos, sombras, perfiles
1. Renderizar el cubo de forma habitual
2. Activar la escritura en el stencil buffer (valor 1)
3. Renderizar el suelo escribiendo en el stencil buffer y no en el Z-buffer
4. Configurar el stencil test para que pasen los fragmentos con valor 1
en el stencil buffer
5. Renderizar el cubo invertido
6. Desactivar el Stencil buffer




EJEMPLO DE ANIMACION

glMatrixMode(GL_MODELVIEW);
for (int i = 0; i < n; i++) {
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
drawSnowFlake(vm);
glutSwapBuffers();
vm = rotate(vm, radians(5.0), dvec3(0.0,0.0,1.0));
}
*/