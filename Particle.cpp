#include "Headers.h"
#include "Externs.h"
Particle::Particle()
{
	setXY(0,0);
	speedX = 3 / 2.0, speedY = 8 / 2.0;
	speedXDown = 0.95, speedYDown = 0.95;
	setColor(235, 211, 187);
}
Particle::Particle(GLfloat x, GLfloat y)
{
	setXY(x, y);
	speedX = 3 / 2.0, speedY = 8 / 2.0;
	speedXDown = 0.95, speedYDown = 0.95;
	setColor(235, 211, 187);
}
void Particle::setDir(GLfloat dirX, GLfloat dirY)
{
	this->dirX = dirX;
	this->dirY = dirY;
}

GLfloat Particle::getDirX()
{
	return dirX;
}
GLfloat Particle::getDirY()
{
	return dirY;
}
void Particle::setDirY(GLfloat dirY)
{
	this->dirY = dirY;
}
void Particle::setDirX(GLfloat dirX)
{
	this->dirX = dirX;
}
GLfloat Particle::getSpeedX()
{
	return speedX;
}
GLfloat Particle::getSpeedY()
{
	return speedY;
}
void Particle::speedDown()
{
	dirY *= speedYDown;
	dirX *= speedXDown;
} 
void Particle::draw()
{
	DrawManager::setColor(getColor());
	if (menu.getMenu() == MenuManager::DEATH)
	{
		DrawManager::point(x, y, 5.0);
	}
	else
	{
		DrawManager::point(x, y, 2);
	}	
}
void Particle::update()
{
	x += dirX;
	y += dirY;
}
void Particle::save(ofstream& out)
{
	Object::save(out);
	out << speedX << " " << speedY << endl;
	out << speedXDown << " " << speedYDown << endl;
	out << dirX<<" "<< dirY<<endl;
}
void Particle::load(ifstream& in)
{
	Object::load(in);
	in >> speedX >> speedY ;
	in >> speedXDown >> speedYDown ;
	in >> dirX >> dirY ;
}