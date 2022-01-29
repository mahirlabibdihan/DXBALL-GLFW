#ifndef __COLLISION_MANAGER__
#define __COLLISION_MANAGER__
class CollisionManager {
public:
	static bool isBallXPaddle;
	static void ballXbrick();
	static void ballXpaddle(GLint);
	static void ballXwall();
	static void bulletXbrick();
	static void paddleXpowerUp();
};
#endif