#ifndef __PADDLE_MANAGER__ 
#define __PADDLE_MANAGER__
#include "GameManager.h"
#include "Rectangle.h"
#define PADDLE_WIDTH 120 
class PaddleManager : public Rectangle {	
	int speedX, bulletCount;
	GLfloat lastX;
	bool shootingPaddle, grabPaddle;
	int extension , compression, minWidth;
public:
	PaddleManager();
	~PaddleManager();
	void init();
	void update();
	void set();
	void reset();
	void shoot();
	void move(GLint);
	void addBullets(GLint);
	void toggleGrabPaddle();
	void toggleShootingPaddle();
	bool isGrabPaddle();
	bool isShootingPaddle();
	void shrink();
	void superShrink();
	void extend();
	void draw();
	GLfloat getLastX();
	GLint getBullets();
	void save(ofstream& out);
	void load(ifstream& in);
};
#endif