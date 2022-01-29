#ifndef __BULLET__
#define __BULLET__
#include "Object.h"
class Bullet :public Object {
public:
	Bullet();
	Bullet(GLfloat, GLfloat);
	void draw();
	static void draw(GLfloat, GLfloat);
	void save(ofstream& out);
	void load(ifstream& in);
};
#endif