#ifndef __MOUSE_MANAGER__
#define __MOUSE_MANAGER__
#include "Headers.h"
class MouseManager {
	static GLfloat x, y, angle;
	static int button;
public:
	MouseManager();
	static int getButton();
	static void setButton(int);
	static GLfloat getDir();
	static void setDir(GLfloat, GLfloat);
	static void drag(int, int);
	static void move(int, int);
	static void click(int, int, int, int);
	static void scroll(int);
	static void dragHandler(int, int);
	static void moveHandler(GLFWwindow* ,double, double);
	static void clickHandler(GLFWwindow* window, int button, int action, int mods);
	static void scrollHandler(int ,int , int, int);
	static GLfloat getX();
	static GLfloat getY();
	static void setXY(GLfloat x, GLfloat y);
	static void setX(GLfloat x);
	static void setY(GLfloat y);
};
#endif
