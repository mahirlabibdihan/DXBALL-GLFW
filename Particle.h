#ifndef __PARTICLE__
#define __PARTICLE__
#include "GameManager.h"
#include "Object.h"
class Particle:public Object
{
	GLfloat speedX, speedY;
	GLfloat speedXDown, speedYDown;
	GLfloat dirX, dirY;
	GLfloat angle, speed;
public:
	Particle();
	Particle(GLfloat, GLfloat);
	void draw();
	GLfloat getDirX();
	GLfloat getDirY();
	void setDir(GLfloat, GLfloat);
	void setDirY(GLfloat);
	void setDirX(GLfloat);
	GLfloat getSpeedX();
	GLfloat getSpeedY();
	void speedDown();
	void update();
	GLfloat getAngle();
	void setAngle(GLfloat);
	GLfloat getSpeed();
	void setSpeed(GLfloat);
	void save(ofstream& out);
	void load(ifstream& in);
};
#endif