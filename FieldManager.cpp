#include "Headers.h"
#include "Externs.h"

FieldManager::FieldManager()
{

}
void FieldManager::init()
{
	x = 260;
	width = bricks.getWidth() * 20;
	y = 0;
	height = WindowManager::getHeight();
}
void FieldManager::set()
{
	x = 260;
	width = bricks.getWidth() * 20;
	y = 0;
	height = WindowManager::getHeight();
}
void FieldManager::draw()
{
	for (int x = getX(); x < getX()+getWidth(); x+= bricks.getWidth())
	{
		for (int y = getY() -10; y<getY()+getHeight(); y+= bricks.getHeight())
		{
			int width = bricks.getWidth(), height = bricks.getHeight();
			int R = 8, G = 8, B = 8;
			DrawManager::setColor(R + 7, G + 7, B + 7);

			GLfloat a[] = { x, x, x + width };
			GLfloat b[] = { y, y + height, y + height };

			GLfloat c[] = { x, x + width, x + width };
			GLfloat d[] = { y, y, y + height };

			DrawManager::filledPolygon(a, b, 3);
			DrawManager::setColor(R - 8, G - 8, B - 8);
			DrawManager::filledPolygon(c, d, 3);
			DrawManager::setColor(R, G, B);
			DrawManager::filledRectangle(x + 12, y + 8, width - 24, height - 16);
		}
	}
}
void FieldManager::save(ofstream& out)
{
	Rectangle::save(out);
}
void FieldManager::load(ifstream& in)
{
	Rectangle::load(in);
}