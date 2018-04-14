#ifndef _H_Texture_H_
#define _H_Texture_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include <GL/freeglut.h>
#include <string>

class Texture 
{
public:
	Texture() : w(0), h(0), id(0) {};
	~Texture() { if (id != 0) glDeleteTextures(1, &id); };
	bool load(const std::string & BMP_Name, GLubyte alpha = 255);
	bool load(const std::string & BMP_Name, glm::ivec3 color, GLubyte alpha = 255);
	void wrap(GLuint wp = GL_CLAMP);
	void loadColorBuffer(GLsizei width, GLsizei height);
	void save(const std::string & BMP_Name);
	void bind();
	void unbind() { glBindTexture(GL_TEXTURE_2D, 0); };
protected:
	GLuint w, h;
	GLuint id;

	void init();
};

#endif //_H_Texture_H_