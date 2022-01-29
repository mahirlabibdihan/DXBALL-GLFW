#ifndef __BALLS_MANAGER__
#define __BALLS_MANAGER__
#include "Ball.h"
class BallsManager{
	GLfloat initRadius;
	vector<Ball> ballsField;
	bool fireBall, thruBall;
public:
	BallsManager();
	~BallsManager();
	Ball& getCell(GLint);
	void add(GLfloat);
	void add(Ball);
	void remove(GLint);
	void speedUp();
	void speedDown();
	bool isOnPaddle();
	void shrink();
	void extend();
	void update();
	void draw();
	GLint getTotal();
	void toggleFireBall();
	bool isFireBall();
	void toggleThruBall();
	bool isThruBall();
	void set();
	void init();
	void reset();
	void save(ofstream& out);
	void load(ifstream& in);
};
#endif
