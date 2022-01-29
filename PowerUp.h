#ifndef __POWER_UP__
#define _POWER_UP_
#include "GameManager.h"
#include "Rectangle.h"
class PowerUp :public Rectangle {
	int type;
	GLfloat dirX, dirY;
	GLfloat time;
	GLfloat yMax;
public:
	PowerUp();
	PowerUp(GLint,GLint,GLint,GLfloat);
	int getType();
	void setType(GLint);
	void update();
	void save(ofstream& out);
	void load(ifstream& in);	
	GLfloat getTime();
	void setTime(GLfloat);
	GLfloat getDirX();
	GLfloat getDirY();
	void setDir(GLfloat, GLfloat);
	void setDirY(GLfloat);
	void setDirX(GLfloat);
};
#endif
