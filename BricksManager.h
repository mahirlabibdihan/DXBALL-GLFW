#ifndef __BRICK_MANAGER__
#define __BRICK_MANAGER__
#include "Brick.h"
class BricksManager {
	Brick** bricksField;
	int rows, cols;	
	int height, width;
	int remaining;
	vector<Brick> bombs;
	vector<Brick> destroyed;
public:
	BricksManager();
	~BricksManager();
	void init();
	void set();
	void reset();
	void draw();
	void update();
	int getHeight();
	int getWidth();
	int getRows();
	int getCols();
	void remove(int,int,int);
	void explode(int,int);
	void explodeAll();
	void levelWrap();
	Brick& getCell(GLint, GLint);
	GLint getRemaining();
	void setRemaining(GLint);
	void save(ofstream& out);
	void load(ifstream& in);
	void expandExploding();
};
#endif
