//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm.hpp>

//-------------------------------------------------------------------------

class Mesh 
{
public:
  static Mesh* generateAxesRGB(GLdouble l);
  static Mesh* generateTriangle(GLdouble r);
  static Mesh* generateTriangleRGB(GLdouble r);
  static Mesh* generateTriPyramid(GLdouble r, GLdouble h);
  static Mesh* generateContCubo(GLdouble l);
  static Mesh* generateCuadrado(GLdouble l);
  static Mesh* generateRectangle(GLdouble w, GLdouble h);
  static Mesh* generaDragon(GLuint numVert);
  static Mesh* generaPoliespiral(GLdouble verIniX, GLdouble verIniY, GLdouble angIni, GLdouble incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert);
  static Mesh* generateRectangleTex(GLdouble w, GLdouble h, GLuint x, GLuint y);
  static Mesh* generateCuboTex(GLdouble w, GLdouble h, GLuint x, GLuint y);
  static Mesh* generateTriPyramidTex(GLdouble r, GLdouble h);
  static Mesh* generatePoligon(GLdouble r, int n);
  static Mesh* generaMallaPorRevolucion(int m, int n, glm::dvec3* perfil);
  void takeVertex(glm::dvec3* v);
  Mesh(void) { };
  ~Mesh(void);
  virtual void draw();
  glm::dvec3* getVertices() { return vertices; };
  glm::dvec4* getColours() { return colors; };
  glm::dvec3* getNormals() { return normals; };
  void normalize(int mm, int nn);
   
protected:
   GLuint numVertices = 0;
   GLuint type = GL_POINTS;
   glm::dvec3* vertices = nullptr;
   glm::dvec3* normals = nullptr;
   glm::dvec4* colors = nullptr;
   /**
   Variable necesaria para poder añadir texturas a los objetos
   */
   glm::dvec2 * texCoords = nullptr;
};

class HipoMesh : public Mesh
{
public:
	HipoMesh(int nP, int nQ, GLfloat a, GLfloat b, GLfloat c);
	void creaBase(); // Guarda en base el polígono que aproxima la circunferencia del tubo
	void creaVerticesIniciales(); // Añade los primeros nP vértices
	void creaRodaja(int v); // Añade nP nuevos vértices, a partir de la componente v
	void cargaMatriz(GLdouble t); // Define la matriz m para t
	void normalize();
	glm::dvec3 curva(GLdouble t);
	glm::dvec3 derivada(GLdouble t);
	glm::dvec3 segundaDerivada(GLdouble t);
	glm::dvec3 multiplicar(int i);
	virtual void draw();
protected:
	int nP; // Número de lados del polígono que aproxima la circunferencia que define el tubo
	int nQ; // Número de rodajas que forman la hipotrocoide
	GLfloat a, b, c; // Valores de los parámetros de la ecuación de la hipotrocoide
	glm::dmat4 m; // Matriz de paso de coordenadas locales a globales
	glm::dvec3* base; // Perfil del nP-ágono que aproxima la circunferencia que define el tubo
	glm::dvec3* vert;
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_