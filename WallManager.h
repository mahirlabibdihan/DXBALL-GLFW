#ifndef __WALL__
#define __WALL__
#include "Headers.h"
class WallManager:public Rectangle {
	int leftX,rightX,topY,bottomY;
	const char* image;
public:
	WallManager();
	void draw();
};
#endif