#ifndef __POWER_UPS_MANAGER__
#define __POWER_UPS_MANAGER__
#include "TextureManager.h"
#include "Headers.h" 
#include "PowerUp.h"
class PowerUpsManager {
	vector<PowerUp> powerUpsField;
	int height, width;
	int totalType;
	TextureManager puImage[19];
	const char* image[19] =
	{
		"Data\\Image\\PowerUps\\KillPaddle.png",  		//1
		"Data\\Image\\PowerUps\\ShootingPaddle.png",			//2
		"Data\\Image\\PowerUps\\ExtraLife.png",		//3
		"Data\\Image\\PowerUps\\ExtendPaddle.png",		//4
		"Data\\Image\\PowerUps\\ShrinkPaddle.png",		//5
		"Data\\Image\\PowerUps\\FastBall.png",			//6
		"Data\\Image\\PowerUps\\SlowBall.png",			//7
		"Data\\Image\\PowerUps\\LevelUp.png",		//8
		"Data\\Image\\PowerUps\\BrickFall.png",			//9
		"Data\\Image\\PowerUps\\GrabPaddle.png",			//10
		"Data\\Image\\PowerUps\\FireBall.png",			//11
		"Data\\Image\\PowerUps\\ThruBall.png",
		"Data\\Image\\PowerUps\\MegaBall.png",			//12
		"Data\\Image\\PowerUps\\ShrinkBall.png",		//13
		"Data\\Image\\PowerUps\\SplitBall.png",
		"Data\\Image\\PowerUps\\EightBall.png",
		"Data\\Image\\PowerUps\\SuperShrink.png",	//14
		"Data\\Image\\PowerUps\\Explode.png",		//15
		"Data\\Image\\PowerUps\\ExpandExploding.png"
	};
public:
	enum powerUpType {
		KillPaddle,
		ShootingPaddle,
		ExtraLife,
		ExpandPaddle,
		ShrinkPaddle,
		FastBall,
		SlowBall,
		LevelWrap,
		FallingBricks,
		GrabPaddle,
		FireBall,
		ThruBall,
		MegaBall,	
		ShrinkBall,
		SplitBall,
		EightBall,
		SuperShrink,
		Explode,
		ExpandExploding
	};
	PowerUpsManager();
	~PowerUpsManager();
	void init();
	void set();
	void update();
	void remove(GLint);
	void add(GLint,GLint, GLint,GLint);
	PowerUp getCell(GLint);
	void draw();
	int getHeight();
	int getWidth();
	int getTotal();
	void reset();
	void save(ofstream& out);
	void load(ifstream& in);
	int generate();
};
#endif