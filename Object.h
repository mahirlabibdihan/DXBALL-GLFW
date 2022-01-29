#ifndef __OBJECT__
#define __OBJECT__
#include "ColorManager.h"
#include "Point.h"
#include "GameManager.h"
class Object: public Point, public ColorManager {
public:
	void save(ofstream& out)
	{
		Point::save(out);
		ColorManager::save(out);
	}
	void load(ifstream& in)
	{
		Point::load(in);
		ColorManager::load(in);
	}
};
#endif