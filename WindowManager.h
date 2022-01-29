#ifndef __WINDOW_MANAGER__
#define __WINDOW_MANAGER__
#include "openGL.h"
class WindowManager {
public:
	static GLint height, width, x, y;
	static GLint getHeight()
	{
		return height;
	}
	static GLint getWidth()
	{
		return width;
	}
	static void setHeight(GLint height)
	{
		WindowManager::height = height;
	}
	static void setWidth(GLint width)
	{
		WindowManager::width = width;
	}
	static void setX(GLfloat x)
	{
		WindowManager::x = x;
	}
	static void setY(GLfloat y)
	{
		WindowManager::y = y;
	}
	static GLfloat getX()
	{
		return x;
	}
	static GLfloat getY()
	{
		return y;
	}
	// Opengl window setup 
	static void set();
};
#endif