#include "Headers.h"
Point::Point()
{
	this->x=this->y=0;
}
Point::Point(GLfloat x, GLfloat y)
{
	this->x=x;
	this->y=y;
}
GLfloat Point::getX()
{
	return x;
}
GLfloat Point::getY()
{
	return y;
}
void Point::setXY(GLfloat x, GLfloat y)
{
	this->x = x;
	this->y = y;
}
void Point::setX(GLfloat x)
{
	this->x = x;
}
void Point::setY(GLfloat y)
{
	this->y = y;
}
void Point::save(ofstream& out)
{
	out << x << " " << y << endl;
}
void Point::load(ifstream& in)
{
	in >> x >> y;
}