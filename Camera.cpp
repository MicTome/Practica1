#include "Camera.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

 void Viewport::setSize(GLsizei aw, GLsizei ah) 
 { 
   w = aw; 
   h = ah; 
   set(); 
 }
 //-------------------------------------------------------------------------

 void Viewport::setPos(GLdouble aw, GLdouble ah)
 {
	 x = aw;
	 y = ah;
	 set();
 }
 //-------------------------------------------------------------------------

 void Viewport::set() 
 { 
   glViewport(x, y, w, h);
 }
//-------------------------------------------------------------------------

 /**
 Vista con la que se inicia
Se le da valores a todos los atributos de la camara
pitch y yaw necesitan esa formula para funcionar correctamente
*/
void Camera::setAZ() 
{
  eye= dvec3(0, 0, 500);
  look= dvec3(0, 0, 0);
  up= dvec3(0, 1, 0);
  n = normalize(eye - look);
  right = normalize(cross(up, n));
  front = -n;
  pitchv = degrees(asin(front.y));
  yawv = degrees(atan(radians(front.x), radians(-front.z)));
  viewMat = lookAt(eye, look, up);
  setVM();
}
//-------------------------------------------------------------------------
/**
Vista al pulsar l, igual que antes
*/
void Camera::set3D() 
{
  eye= dvec3(500, 500, 500);
  look= dvec3(0, 10, 0);
  up= dvec3(0, 1, 0);
  n = normalize(eye - look);
  right = normalize(cross(up, n));
  front = -n;
  pitchv = degrees(asin(front.y));
  yawv = degrees(atan(radians(front.x), radians(-front.z)));
  viewMat = lookAt(eye, look, up);
  setVM();
}
//-------------------------------------------------------------------------

void Camera::setVM() 
{
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixd(value_ptr(viewMat));
}
//-------------------------------------------------------------------------

void Camera::pitch(GLdouble a) 
{  
  rotatePY(a, 0.0);
  //viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(1.0, 0, 0));
}
//-------------------------------------------------------------------------
void Camera::yaw(GLdouble a)
{
	rotatePY(0.0, a);
  //viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 1.0, 0));
}
//-------------------------------------------------------------------------
void Camera::roll(GLdouble a)
{
  viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 0, 1.0));
}
//-------------------------------------------------------------------------

void Camera::scale(GLdouble s)
{ 
  factScale -= s; 
  if (s < 0) s = 0.01;
  setPM(); 
}
//-------------------------------------------------------------------------

void Camera::setSize(GLdouble aw, GLdouble ah) 
{
  xRight = aw / 2.0;
  xLeft = -xRight;
  yTop = ah / 2.0;
  yBot = -yTop;
 
  setPM();
}
//-------------------------------------------------------------------------

/**
Metodo que decide si se ve en perspectiva o en ortogonal, se cambia de una a otra pulsando p
*/
void Camera::setPM() 
{
	if (orto){
		projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixd(value_ptr(projMat));
		glMatrixMode(GL_MODELVIEW);
	}
	else{
		glMatrixMode(GL_PROJECTION);
		projMat = frustum(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, yTop, farVal);
		glLoadMatrixd(value_ptr(projMat));
		glMatrixMode(GL_MODELVIEW);
	}
}
//-------------------------------------------------------------------------

/**
Se mueve a izquierda y derecha, right es u, la ortogonal a up y n
*/
void Camera::moveLR(GLdouble t)
{
	eye += right * t;
	viewMat = lookAt(eye, eye + front, up);
	setVM();
}

/**
Se mueve arriba y abajo con x,z, v es la ortogonal de n y u
*/
void Camera::moveUD(GLdouble t)
{
	dvec3 v = cross(n, right);
	eye += v * t;
	viewMat = lookAt(eye, eye + front, up);
	setVM();
}

/**
Se mueve hacia el frente y hacia atras con w,s
*/
void Camera::moveFB(GLdouble t)
{
	eye += front * t;
	viewMat = lookAt(eye, eye + front, up);
	setVM();
}

/**
Metodo de las diapositivas, se actualizan pitch, yaw, front y el viewMat
*/
void Camera::rotatePY(GLdouble incrPitch, GLdouble incrYaw){
	pitchv += incrPitch;
	yawv += incrYaw;
	
	if (pitchv > 89.5) pitchv = 89.5;
	if (pitchv < -89.5) pitchv = -89.5;
	//if (yawv > 89.5) yawv = 89.5;
	//if (yawv < -89.5) yawv = -89.5;
	
	front.x = sin(radians(yawv)) * cos(radians(pitchv));
	front.y = sin(radians(pitchv));
	front.z = -cos(radians(yawv)) * cos(radians(pitchv));
	viewMat = lookAt(eye, eye + front, up);
	
}

//Cambia con p de un a otro
void Camera::setPrj(){
	orto = !orto;
	setPM();
}



/**
Ejemplo: realizar una trayectoria circular alrededor de la escena.
eye.x = cos(radians(++ang)) * radius;
eye.z = -sin(radians(ang)) * radius;
viewMat = lookAt(eye, vec3(0.0, 0.0, 0.0), (0.0, 1.0, 0.0));


 Movimiento horizontal en el eje X del sistema global
eye.x += incX; -> Cambia la dirección de vista
viewMat = lookAt(eye, vec3(0.0, 0.0, 0.0), (0.0, 1.0, 0.0));


 Movimiento horizontal en el eje U del sistema de la cámara
eye += U * incX; -> Cambia la dirección de vista
viewMat = lookAt(eye, vec3(0.0, 0.0, 0.0), (0.0, 1.0, 0.0));

Relativos a la propia cámara
 Mover la cámara en uno de sus ejes: mover el ojo (eye)
 Eje u: eye += u * speed
 Eje v: eye += v * speed
 Eje n: eye += n * speed
También modifica la dirección de vista: -(eye – look)
 Si no queremos cambiar la dirección de vista -> mover look de la
misma forma.
*/