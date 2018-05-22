//#include <Windows.h>
//#include <gl/GL.h>
//#include <gl/GLU.h>
//#include <GL/glut.h>

#include <GL/freeglut.h>

#include "Camera.h"
#include "Scene.h"

#include <iostream>
using namespace std;

//---------- Global variables -------------------------------------------------------------

// Viewport position and size
Viewport viewPort(800, 600);   

// Camera position, view volume and projection
Camera camera(&viewPort);    
/**
mCoord atributo necesario para guardar las coordenadsa del raton, la x y la inversa de la y (que se da alreves cuando obtienes la
coordenada. Mirar motion y mouse.
*/
glm::dvec2 mCoord;
// Scene entities
Scene scene(&camera);   

//----------- Callbacks ----------------------------------------------------
/**
Para realizar un callback, necesitas crear un metodo aqui, y en el main llamar a la funcion glut de los callbacks
*/
void display();
void resize(int newWidth, int newHeight);
void key(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);
void motion(int x, int y);
void mouse(int button, int state, int x, int y);

//-------------------------------------------------------------------------

int main(int argc, char *argv[])
{
  cout << "Starting console..." << '\n';

  // Initialization
  glutInit(&argc, argv);

  glutInitContextVersion(3, 3);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);   
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS); 
  glutInitWindowSize(800, 600);   // window size
  //glutInitWindowPosition (140, 140);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);   // | GLUT_STENCIL  
  
  int win = glutCreateWindow( "Freeglut-project" );  // window's identifier
  
  // Callback registration
  /**
  Llamada a los callbacks con la funcion creada, cada uno admite una funcion de X parametros
  */
  glutReshapeFunc(resize);
  glutKeyboardFunc(key);
  glutSpecialFunc(specialKey);
  glutDisplayFunc(display);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
 
  cout << glGetString(GL_VERSION) << '\n';
  cout << glGetString(GL_VENDOR) << '\n';
 
  scene.init();    // after creating the context
   
  glutMainLoop(); 
    
  //cin.sync();   cin.get();
  glutDestroyWindow(win);  // Destroy the context 

  return 0;
}
//-------------------------------------------------------------------------

void display()   // double buffer
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  


  scene.render();   

  glutSwapBuffers();  
}
//-------------------------------------------------------------------------

void resize(int newWidth, int newHeight)
{
  // Resize Viewport 
  viewPort.setSize(newWidth, newHeight);  
  // Resize Scene Visible Area 
  camera.setSize(viewPort.getW(), viewPort.getH());    // scale unchanged
}
//-------------------------------------------------------------------------

void key(unsigned char key, int x, int y)
{
	/**
	Variable para la foto
	dia permite que se giren los diabolos
	*/
  Texture tex;
  bool need_redisplay = true;
  //DiaboloTex* dia = scene.getDiaboloTex();
  switch (key) {
  case 'm':
	  scene.rotateBody();
	  scene.moveBB8();
	  break;
  case 27:  // Escape key 
    glutLeaveMainLoop();  // Freeglut's sentence for stopping glut's main loop 
    break;
  case '+': 
    camera.scale(+0.01);   // zoom in  
    break;
  case '-':
    camera.scale(-0.01);   // zoom out
    break;
  case 'l':
	  camera.set3D(); 
	  break;
  case 'o':
	  camera.setAZ();
	  break;
  case 'A':
//	  dia->rotateZ();
	  break;
  case 'a':
	  /**
	  Mueve a la izquierda camara
	  */
	  camera.moveLR(-10.0);
	  break;
  case 'd':
	  /**
	  Mueve a la derecha la camara
	  */
	  camera.moveLR(10.0);
	  break;
  case 'z':
	  /**
	  Mueve hacia arriba la camara
	  */
	  camera.moveUD(10.0);
	  break;
  case 'x':
	  /**
	  Mueve hacia abajo la camara
	  */
	  camera.moveUD(-10.0);
	  break;
  case 'w':
	  /**
	  Mueve hacia el frente la camara
	  */
	  camera.moveFB(10.0);
	  break;
  case 's':
	  /**
	  Mueve hacia atras la camara
	  */
	  camera.moveFB(-10.0);
	  break;
  case 'p':
	  /**
	  cambio de perspectiva de ortogonal a perspectiva
	  */
	  camera.setPrj();
	  break;
  case 'f':
	  /**
	  Captura de pantalla dado el tamaño de la pantalla y lugar asignado para guardar la captura
	  */
	  tex.loadColorBuffer(viewPort.getW(), viewPort.getH());
	  tex.save("..\\Bmps\\prueba.bmp");
	  break;
  default:
    need_redisplay = false;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}
//-------------------------------------------------------------------------

void specialKey(int key, int x, int y)
{
  bool need_redisplay = true;

  switch (key) {
  case GLUT_KEY_RIGHT:
	  camera.yaw(4);   
    break;
  case GLUT_KEY_LEFT:
    camera.yaw(-4);      
    break;
  case GLUT_KEY_UP:
    camera.pitch(4);   
    break;
  case GLUT_KEY_DOWN:
    camera.pitch(-4);
    break;
  default:
    need_redisplay = false;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}
//-------------------------------------------------------------------------

/**
mouse obtiene las coordenadas del raton. state suele estare n 0
*/
void mouse(int button, int state, int x, int y){
	mCoord.x = x;
	mCoord.y = viewPort.getH() - y;
}

/**
motion modifica los valores y mueve la camara segun se mueva el raton cuando esta pulsado
*/
void motion(int x, int y){
	glm::dvec2 mOffset = mCoord; // var. global
	mCoord = glm::dvec2(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
	mOffset = (mCoord - mOffset) * 0.05; // sensitivity = 0.05
	camera.rotatePY(mOffset.y, mOffset.x);
	glutPostRedisplay();
}