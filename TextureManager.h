#ifndef __TEXTURE_MANAGER__
#define __TEXTURE_MANAGER__
#include "Headers.h"

class TextureManager{
	GLint width, height;
	static GLuint shaderProgram, VBO, VAO;
	static const GLchar* vertexShaderSource;
	static const GLchar* fragmentShaderSource;
	GLuint texture;
public:
	TextureManager();
	TextureManager(const char* filename);
	~TextureManager();
	static void init();
	static GLuint createProgram();
	void load(const char* filename);
	void render(GLfloat x, GLfloat y);
	static void render(GLfloat x, GLfloat y, const char* filename);
	static void render(GLfloat x, GLfloat y, GLint width, GLint height, unsigned char* image);
	void render(GLfloat x, GLfloat y, GLuint totalC, GLuint totalR, GLuint startFlag, GLuint totalFlag, GLint& flag, bool loop);
};
#endif