#include "Headers.h"
#include "Externs.h"
BoardManager::BoardManager()
{

}
void BoardManager::init()
{
	y = 350;
	x = field.getX() + field.getWidth();
	width = bricks.getWidth() * bricks.getCols();
	height = bricks.getHeight() * bricks.getRows();
}

void BoardManager::set()
{
	y = 350;
	x = field.getX() + field.getWidth();
	width = bricks.getWidth() * bricks.getCols();
	height = bricks.getHeight() * bricks.getRows();
}

void BoardManager::fall()
{
	if (y > 2 * bricks.getHeight())
	{
		y -= bricks.getHeight();
	}
}
void BoardManager::save(ofstream& out)
{
	Rectangle::save(out);
}
void BoardManager::load(ifstream& in)
{
	Rectangle::load(in);
}