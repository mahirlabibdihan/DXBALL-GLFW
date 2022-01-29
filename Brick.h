#ifndef __BRICK__
#define __BRICK__
#define NORMAL 1
#define EXPLOSIVE (1+NORMAL)
#define MULTIHIT (-1*NORMAL)
#define BRICK_WIDTH 70
#define BRICK_HEIGHT 30
#include "Headers.h"

class Brick : public Rectangle {
	int strength;
public:
	Brick();
	Brick(GLint, GLint);
	~Brick();
	void setStrength(int);
	int getStrength();
	void damage();
	void drawNormal(GLfloat, GLfloat);
	static void drawNormal(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	static void drawExplosive(GLfloat, GLfloat);
	static void drawMultiHit(GLfloat, GLfloat);
	void draw();
	void save(ofstream& out);
	void load(ifstream& in);
};
#endif
