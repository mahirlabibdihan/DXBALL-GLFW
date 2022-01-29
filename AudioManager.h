#ifndef __AUDIO_MANAGER__
#define __AUDIO_MANAGER__
#include "Headers.h"
using namespace irrklang;
class AudioManager{	
	static ISoundEngine *soundEngine;
	static const char* music[14];
public:
	enum musicType {
		BACKGROUND,
		BALL_X_NORMAL,
		BALL_X_PADDLE,
		BALL_X_WALL,
		BALL_X_MULTIHIT,
		BALL_X_EXPLOSIVE,
		GAME_OVER,
		LEVEL_UP,
		MOUSE_HOVER,
		MOUSE_CLICK,
		RELOAD,
		SHOOT,
		CATCH_ITEMS,
		DROP_ITEMS
	};
	
public:
	AudioManager();
	~AudioManager();
	static void play(musicType, bool = false);
	static void play(const char*,bool=false);
	static void stopAll();
};
#endif
