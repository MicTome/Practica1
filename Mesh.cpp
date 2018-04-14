#include "Mesh.h"

using namespace glm;

//-------------------------------------------------------------------------

Mesh ::~Mesh(void) 
{
  delete[] vertices;
  delete[] colors;
  delete[] texCoords;
}
//-------------------------------------------------------------------------

void Mesh::draw() 
{
  if (vertices != nullptr) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertices);  // number of coordinates per vertex, type of each coordinate 
	if (colors != nullptr) {
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4, GL_DOUBLE, 0, colors);   // number of coordinates per color, type of each coordinate 
	}
	/**
	Se añaden las texturas al objeto siempre que haya una en el mismo
	*/
	  if (texCoords != nullptr){
		  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		  glTexCoordPointer(2, GL_DOUBLE, 0, texCoords);
	  }
	
    glDrawArrays(type, 0, numVertices);   // kind of primitives, first, count

	  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh * Mesh::generateAxesRGB(GLdouble l)
{
  Mesh* m = new Mesh();
  m->type = GL_LINES;
  m->numVertices = 6;

  m->vertices = new dvec3[m->numVertices];
  m->vertices[0] = dvec3(0.0, 0.0, 0.0);   
  m->vertices[1] = dvec3(l, 0.0, 0);
  m->vertices[2] = dvec3(0, 0.0, 0.0);
  m->vertices[3] = dvec3(0.0, l, 0.0); 
  m->vertices[4] = dvec3(0.0, 0.0, 0.0);
  m->vertices[5] = dvec3(0.0, 0.0, l);

  m->colors = new dvec4[m->numVertices];
  m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[2] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[3] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[4] = dvec4(0.0, 0.0, 1.0, 1.0);
  m->colors[5] = dvec4(0.0, 0.0, 1.0, 1.0);
 
  return m; 
}
//-------------------------------------------------------------------------

/**
El triangulo se genera a base de senos y cosenos de 90 grados, sumando hasta llegar a los 3 vertices
*/
Mesh * Mesh::generateTriangle(GLdouble r)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLES;
	m->numVertices = 3;
	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(r*cos(radians(90.0)), r*sin(radians(90.0)), 0.0);
	m->vertices[1] = dvec3(r*cos(radians(90.0 + 120.0)), r*sin(radians(90.0 + 120.0)), 0);
	m->vertices[2] = dvec3(r*cos(radians(90.0 + 120.0 + 120.0)), r*sin(radians(90.0 + 120.0 + 120.0)), 0.0);

	return m;
}

//-------------------------------------------------------------------------

/**
Igual que el anterior pero se le añade un color por vertice
*/
Mesh * Mesh::generateTriangleRGB(GLdouble r)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLES;
	m->numVertices = 3;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(r*cos(radians(90.0)), r*sin(radians(90.0)), 0.0);
	m->vertices[1] = dvec3(r*cos(radians(90.0 + 120.0)), r*sin(radians(90.0 + 120.0)), 0);
	m->vertices[2] = dvec3(r*cos(radians(90.0 + 120.0 + 120.0)), r*sin(radians(90.0 + 120.0 + 120.0)), 0.0);

	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);

	return m;
}

//-------------------------------------------------------------------------

/**
En este caso, la altura tiene su vertice, por lo que se necesita hacer un triangulo despues del vertice en altura
Es necesario cerrar el triangulo con un vertice de mas al primero del triangulo
*/
Mesh * Mesh::generateTriPyramid(GLdouble r, GLdouble h)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_FAN;
	m->numVertices = 5;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(0.0, 0.0, h);
	m->vertices[1] = dvec3(r*cos(radians(90.0)), r*sin(radians(90.0)), 0.0);
	m->vertices[2] = dvec3(r*cos(radians(90.0 + 120.0)), r*sin(radians(90.0 + 120.0)), 0);
	m->vertices[3] = dvec3(r*cos(radians(90.0 + 120.0 + 120.0)), r*sin(radians(90.0 + 120.0 + 120.0)), 0.0);
	m->vertices[4] = m->vertices[1];

	/*m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);
	m->colors[3] = dvec4(0.0, 0.0, 1.0, 1.0);*/

	return m;
}

//-------------------------------------------------------------------------

/**
El cubo (laterales) se genera a partir de la mitad de la longitud de lado dada
Se crean los 4 vertices iniciales y se completan hasta llegar a cerrarse.
Tiene los 8 vertices de un cubo normal, mas 2 para cerrarlo.
*/
Mesh * Mesh::generateContCubo(GLdouble l)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_STRIP;
	m->numVertices = 10;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(-l / 2, l / 2, -l / 2);
	m->vertices[1] = dvec3(-l / 2, -l / 2, -l / 2);
	m->vertices[2] = dvec3(l / 2, l / 2, -l / 2);
	m->vertices[3] = dvec3(l / 2, -l / 2, -l / 2);

	m->vertices[4] = dvec3(l / 2, l / 2, l / 2);
	m->vertices[5] = dvec3(l / 2, -l / 2, l / 2);
	m->vertices[6] = dvec3(-l / 2, l / 2, l / 2);
	m->vertices[7] = dvec3(-l / 2, -l / 2, l / 2);

	m->vertices[8] = dvec3(-l / 2, l / 2, -l / 2);
	m->vertices[9] = dvec3(-l / 2, -l / 2, -l / 2);

	return m;
}

//-------------------------------------------------------------------------

/**
Simplificación del cubo, igual que antes pero solo son 4 vertices
*/
Mesh * Mesh::generateRectangle(GLdouble w, GLdouble h)
{
	Mesh* m = new Mesh();
	m->type = GL_TRIANGLE_STRIP;
	m->numVertices = 4;

	m->vertices = new dvec3[m->numVertices];
	m->vertices[0] = dvec3(w/2, -h/2, 0);
	m->vertices[1] = dvec3(w / 2, h / 2,0);
	m->vertices[2] = dvec3(-w / 2, -h / 2,0);
	m->vertices[3] = dvec3(-w / 2, h / 2,0);
	return m;
}


//-------------------------------------------------------------------------

/**
Opcional
*/
Mesh * Mesh::generaDragon(GLuint numVert)
{
	GLdouble x = 0.0;
	GLdouble y = 0.0;
	GLdouble PR1 = 0.787473;
	GLdouble PR2 = 1 - PR1;
	GLdouble tx = 0.0;
	GLdouble ty = 0.0;
	Mesh* m = new Mesh();
	m->type = GL_POINTS;
	m->numVertices = numVert+1;
	m->vertices = new dvec3[m->numVertices];

	for (int i = 0; i < numVert; i++){
		if (i == 0){
			m->vertices[i] = dvec3(x, y, 0.0);
		}
		else{
			double azar = rand() / double(RAND_MAX);
			if (azar < PR1){
				tx = 0.824074 * x + 0.281482 * y - 0.882290;
				ty = -0.212346 * x + 0.864198 * y - 0.110607;
				m->vertices[i] = dvec3(tx, ty, 0.0);
				x = tx;
				y = ty;
			}
			else{
				tx = 0.088272 * x + 0.520988 * y + 0.785360;
				ty = -0.463889 * x - 0.377778 * y + 8.095795;
				m->vertices[i] = dvec3(tx, ty, 0.0);
				x = tx;
				y = ty;
			}
		}
	}
	tx = 0.088272 * x + 0.520988 * y + 0.785360;
	ty = -0.463889 * x - 0.377778 * y + 8.095795;
	m->vertices[numVert] = dvec3(tx, ty, 0.0);
	return m;
}

//----------------------------------------------------------------------------

/**
Opcional
*/
Mesh * Mesh::generaPoliespiral(GLdouble verIniX, GLdouble verIniY, GLdouble angIni, GLdouble incrAng,
	GLdouble ladoIni, GLdouble incrLado, GLuint numVert){
	Mesh* m = new Mesh();
	m->type = GL_LINE_STRIP;
	m->numVertices = numVert+1;
	m->vertices = new dvec3[m->numVertices];
	GLdouble x = verIniX;
	GLdouble y = verIniY;
	GLdouble tx = 0.0;
	GLdouble ty = 0.0;
	for (int i = 0; i < numVert; i++){
		if (i == 0){
			tx = x + ladoIni*cos(radians(angIni));
			ty = y + ladoIni*sin(radians(angIni));
			m->vertices[i] = dvec3(tx, ty, 0.0);
			x = tx;
			y = ty;
		}
		else{
			ladoIni += incrLado;
			angIni += incrAng;
			tx = x + ladoIni*cos(radians(angIni));
			ty = y + ladoIni*sin(radians(angIni));
			m->vertices[i] = dvec3(tx, ty, 0.0);
			x = tx;
			y = ty;
		}
	}
	ladoIni += incrLado;
	angIni += incrAng;
	tx = x + ladoIni*cos(radians(angIni));
	ty = y + ladoIni*sin(radians(angIni));
	m->vertices[numVert] = dvec3(tx, ty, 0.0);
	return m;
}

//-------------------------------------------------------------------------
/**
Se genera un traingulo que puede tener texturas, esta se coloca en las coordenadas 
0.1--1.1
|	   |
|	   |
0,0--1.0  Los +y, +x son para añadir mas veces la misma textura
*/
Mesh * Mesh::generateRectangleTex(GLdouble w, GLdouble h, GLuint x, GLuint y)
{
	Mesh *m = generateRectangle(w, h);
	m->texCoords = new dvec2[m->numVertices];
	m->texCoords[0] = dvec2(0, 0);
	m->texCoords[1] = dvec2(0, 1+y);
	m->texCoords[2] = dvec2(1+x, 0);
	m->texCoords[3] = dvec2(1+x, 1+y);
	return m;
}

/**Se genera un cubo que puede tener texturas, esta se coloca en las coordenadas
0.1--1.1--2.1--3.1--4.1
|	   |    |    |    |
|	   |    |    |    |
0,0--1.0--2.0--3.0--4.0 Los +y es igual que antes
*/
Mesh* Mesh::generateCuboTex(GLdouble w, GLdouble h, GLuint x, GLuint y)
{
	Mesh *m = generateContCubo(w);
	m->texCoords = new dvec2[m->numVertices];
	m->texCoords[0] = dvec2(0, 0);
	m->texCoords[1] = dvec2(0, 1 + y);
	m->texCoords[2] = dvec2(1, 0);
	m->texCoords[3] = dvec2(1, 1 + y);
	m->texCoords[4] = dvec2(2, 0);
	m->texCoords[5] = dvec2(2, 1 + y);
	m->texCoords[6] = dvec2(3, 0);
	m->texCoords[7] = dvec2(3, 1 + y);
	m->texCoords[8] = dvec2(4, 0);
	m->texCoords[9] = dvec2(4, 1 + y);
	return m;
}

//-------------------------------------------------------------------------
/**Se genera una piramide que puede tener texturas, esta se coloca en las coordenadas
Del 1 al 4 son los vertices de la parte inferior de la piramide, como son triangulos, comparten varios vertices
Estos son los repetidos.
El 0.5 en el 0, es para que se llegue hasta la mitad de la textura
*/
Mesh* Mesh::generateTriPyramidTex(GLdouble r, GLdouble h)
{
	Mesh *m = generateTriPyramid(r, h);
	m->texCoords = new dvec2[m->numVertices];
	m->texCoords[0] = dvec2(0.5, 0.5);
	m->texCoords[1] = dvec2(0, 0);
	m->texCoords[2] = dvec2(1, 0);
	m->texCoords[3] = dvec2(0, 0);
	m->texCoords[4] = dvec2(1, 0);
	return m;

}