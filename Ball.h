#ifndef __BALL__
#define __BALL__
#include "Headers.h"
#define Ball_Board 5
#define BALL_RADIUS 10
#define BALL_SPEED 10
class Ball :public Circle {
	bool fireBall, onPaddle, thruBall;
	GLfloat theta, speed;
public:
	Ball();
	~Ball();
	void init();
	void set();
	void reset();
	void update();
	void move(GLint);
	GLfloat getDirX();
	GLfloat getDirY();
	GLfloat getAngle();
	void setAngle(GLfloat);
	void speedUp();
	void speedDown();
	GLfloat getSpeed();
	void setSpeed(GLfloat);
	bool isOnPaddle();
	void stickToPaddle();
	void launch();
	void shrink();
	void extend();
	void toggleFireBall();
	bool isFireBall();
	void toggleThruBall();
	bool isThruBall();
	void draw();
	void reverseX();
	void reverseY();
	void save(ofstream& out);
	void load(ifstream& in);
};
#endif
