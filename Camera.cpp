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

void Camera::setAZ() 
{
  eye= dvec3(0, 0, 500);
  look= dvec3(0, 0, 0);
  up= dvec3(0, 1, 0);
  viewMat = lookAt(eye, look, up);
  setVM();
}
//-------------------------------------------------------------------------

void Camera::set3D() 
{
  eye= dvec3(500, 500, 500);
  look= dvec3(0, 10, 0);
  up= dvec3(0, 1, 0);
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

void Camera::setPM() 
{
  projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixd(value_ptr(projMat));
  glMatrixMode(GL_MODELVIEW);
}
//-------------------------------------------------------------------------


void Camera::moveLR(GLdouble t)
{
	dvec3 n = normalize(eye - look);
	dvec3 u = normalize(cross(up, n));
	look += u * t;
	eye += u * t;
	viewMat = lookAt(eye, look, up);
	setVM();
}

void Camera::moveUD(GLdouble t)
{
	dvec3 n = normalize(eye - look);
	dvec3 u = normalize(cross(up, n));
	dvec3 v = cross(n, u);
	look += v * t;
	eye += v * t;
	viewMat = lookAt(eye, look, up);
	setVM();
}

void Camera::moveFB(GLdouble t)
{
	dvec3 n = normalize(eye - look);
	dvec3 u = normalize(cross(up, n));
	dvec3 v = cross(n, u);
	eye += -n * t;
	look += t * -n;
	viewMat = lookAt(eye, look, up);
	setVM();
}

void Camera::rotatePY(GLdouble incrPitch, GLdouble incrYaw){
	pitchv += incrPitch;
	yawv += incrYaw;
	dvec3 n = normalize(eye - look);
	if (pitchv > 89.5) pitchv = 89.5;
	if (pitchv < -89.5) pitchv = -89.5;
	if (yawv > 89.5) yawv = 89.5;
	if (yawv < -89.5) yawv = -89.5;
	dvec3 front = -n;
	front.x = sin(radians(yawv)) * cos(radians(pitchv));
	front.y = sin(radians(pitchv));
	front.z = -cos(radians(yawv)) * cos(radians(pitchv));
	front = normalize(front);
	viewMat = lookAt(eye, eye + front, up); 
	setVM();
}