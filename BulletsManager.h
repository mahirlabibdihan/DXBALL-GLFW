#ifndef __BULLETS_MANAGER__
#define __BULLETS_MANAGER__
#include "Bullet.h"
class BulletsManager {
	vector<Bullet> bulletsField;
	GLfloat speedY;
public:
	BulletsManager();
	Bullet getCell(GLint);
	void add(GLint,GLint);
	void remove(GLint);
	void update();
	void draw();
	GLint getTotal();
	void set();
	void init();
	void reset();
	void save(ofstream& out);
	void load(ifstream& in);
};
#endif