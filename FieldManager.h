#ifndef __FIELD_MANAGER__
#include "GameManager.h"
#include "Rectangle.h"
class FieldManager:public Rectangle
{
public:
	FieldManager();
	void set();
	void init();
	void draw();
	void save(ofstream& out);
	void load(ifstream& in);
};
#endif


