#include "Headers.h"
#include "Externs.h"
PowerUp::PowerUp()
{

}
PowerUp::PowerUp(GLint x,GLint y, GLint type,GLfloat time)
{
	setXY(x, y);
	height = 50;
	width = 50;
	this->type = type;
	this->time = time;
}
int PowerUp::getType()
{
	return type;
}
void PowerUp::update()
{
	GLfloat t = (GameManager::getTime() - time)*.005;
	x += dirX * t *.4;
	y += dirY * t * 1.2  -  6 * t * t ;
	if (y > WindowManager::getHeight() - height)
	{
		//y = WindowManager::getHeight() - height;
	}
	else if (x < field.getX())
	{
		dirX *= -1;
		x = field.getX() ;
	}
	else if (x > field.getX() + field.getWidth() - width)
	{
		dirX *= -1;
		x = field.getX() + field.getWidth() - width;
	}

}
void PowerUp::save(ofstream& out)
{
	Rectangle::save(out);
	out << type <<" "<<time<< endl;
}
void PowerUp::load(ifstream& in)
{
	Rectangle::load(in);
	in >> type>>time;
}
GLfloat PowerUp::getTime()
{
	return time;
}
void PowerUp::setTime(GLfloat time)
{
	this->time = time;
}
void PowerUp::setDir(GLfloat dirX, GLfloat dirY)
{
	this->dirX = dirX;
	this->dirY = dirY;
}

GLfloat PowerUp::getDirX()
{
	return dirX;
}
GLfloat PowerUp::getDirY()
{
	return dirY;
}
void PowerUp::setDirY(GLfloat dirY)
{
	this->dirY = dirY;
}
void PowerUp::setDirX(GLfloat dirX)
{
	this->dirX = dirX;
}