#ifndef __GAME_MANAGER__
#define __GAME_MANAGER__
#include "OpenGL.h"
class GameManager
{
	static GLfloat timer;
	static int life;
	static bool pause;
public:	
	GameManager();
	static void init();
	static void set();
	static void reset();
	static void incTimer();
	static void drawTime();
	static GLfloat getTime();
	static void saveState();
	static void loaspeedtate();
	static void incLife();
	static void update();
	static void death();
	static GLint getLife();
	static void save();
	static void load();
	static void pauseGame();
	static void resumeGame();
	static bool isPaused();
};
#endif
