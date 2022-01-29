#include "Headers.h"
#include "Opengl\\stb_image.h"
#include "Externs.h"
PowerUpsManager::PowerUpsManager()
{
	height = 50;
	width = 50;
	totalType = 19;
	
}
PowerUpsManager::~PowerUpsManager()
{

}
void PowerUpsManager::init()
{
	for (int i = 0; i < totalType; i++)
	{
		puImage[i].load(image[i]);
	}
	powerUpsField.clear();
}
void PowerUpsManager::set()
{
	powerUpsField.clear();
}
void PowerUpsManager::update()
{
	for (int i = 0;i < powerUpsField.size();i++)
	{
		if (powerUpsField[i].getY() < 0)
		{
			powerUpsField.erase(powerUpsField.begin()+i);
			i--;
		}
		else
		{
			powerUpsField[i].update();
		}
	}
}
PowerUp PowerUpsManager::getCell(GLint i)
{
	return powerUpsField[i];
}
void PowerUpsManager::add(GLint x,GLint y,GLint type,GLint i)
{
	PowerUp pu(x, y,type, GameManager::getTime());
	pu.setDir(balls.getCell(i).getDirX(),fabs(balls.getCell(i).getDirY()/2));
	powerUpsField.push_back(pu);
}
void PowerUpsManager::draw()
{
	for (auto i : powerUpsField)
	{
		puImage[i.getType()].render(i.getX(), i.getY());
	}
}
void PowerUpsManager::remove(GLint i)
{
	powerUpsField.erase(powerUpsField.begin() + i);
}
int PowerUpsManager::getHeight()
{
	return height;
}

int PowerUpsManager::getWidth()
{
	return width;
}
int PowerUpsManager::getTotal()
{
	return powerUpsField.size();
}

void PowerUpsManager::reset()
{
	powerUpsField.clear();
}
void PowerUpsManager::save(ofstream& out)
{
	out << width << " " << height << endl;

	out << powerUpsField.size() << endl;
	for (int i = 0;i < powerUpsField.size();i++)
	{
		powerUpsField[i].save(out);
	}
}
void PowerUpsManager::load(ifstream& in)
{
	in >> width >> height ;

	int size;
	in >> size;
	powerUpsField.resize(size);
	for (int i = 0;i < powerUpsField.size();i++)
	{
		powerUpsField[i].load(in);
	}
}

int PowerUpsManager::generate()
{
	AudioManager:: play(AudioManager::DROP_ITEMS);
	int type = rand() % 101;

	if (type <= 10) return KillPaddle;
	if (type <= 18) return ShrinkBall;
	if (type <= 26) return FastBall;
	if (type <= 34) return SuperShrink;
	if (type <= 42) return FallingBricks;
	if (type <= 46) return SlowBall;
	if (type <= 50) return MegaBall;
	if (type <= 54) return SplitBall;
	if (type <= 58) return ShrinkPaddle;
	if (type <= 62) return ExpandPaddle;
	if (type <= 66) return GrabPaddle;
	if (type <= 70) return Explode;
	if (type <= 74) return ExpandExploding;
	if (type <= 77) return ThruBall;
	if (type <= 80) return FireBall;
	if (type <= 82) return EightBall;
	if (type <= 85) return ShootingPaddle;
	if (type <= 87) return ExtraLife;
	if (type <= 89) return LevelWrap;	

	return KillPaddle;
}