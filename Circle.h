#ifndef __CIRCLE__
#define __CIRCLE__
#include "Object.h"
class Circle: public Object {
protected:
	int radius;
public:
	int getRadius();
	void setRadius(int radius);
	void save(ofstream& out);
	void load(ifstream& in);
	void draw();
};
#endif