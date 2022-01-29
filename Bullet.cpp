#include "Headers.h"
Bullet::Bullet()
{

}
Bullet::Bullet(GLfloat x, GLfloat y)
{
	setXY(x, y);
	setColor(188, 3, 57);
}
void Bullet::draw()
{
	DrawManager::setColor(getColor());
	GLfloat X[] = { x - 4, x, x + 4, x + 4, x, x - 4 };
	GLfloat Y[] = { y + 4, y, y + 4, y + 10 + 4, y + 10 + 4 + 4, y + 10 + 4 };
	DrawManager::filledPolygon(X,Y,6);
}

void Bullet::draw(GLfloat x,GLfloat y)
{
	DrawManager::setColor(188, 3, 57);
	GLfloat X[] = { x - 4, x, x + 4, x + 4, x, x - 4 };
	GLfloat Y[] = { y + 4, y, y + 4, y + 10 + 4, y + 10 + 4 + 4, y + 10 + 4 };
	DrawManager::filledPolygon(X, Y, 6);
}
void Bullet::save(ofstream& out)
{
	Object::save(out);
}
void Bullet::load(ifstream& in)
{
	Object::load(in);
}