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

//-------------------------------------------------------------------------

#endif //_H_Scene_H_