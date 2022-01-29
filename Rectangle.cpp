#include "Headers.h"
Rectangle::Rectangle()
{
	this->width = 0;
	this->height = 0;
}
Rectangle::Rectangle(GLfloat width, GLfloat height)
{
	this->width = width;
	this->height = height;
}
void Rectangle::setWidth(GLfloat width)
{
	this->width = width;
}
void Rectangle::setHeight(GLfloat height)
{
	this->height = height;
}
GLfloat Rectangle::getHeight()
{
	return this->height;
}
GLfloat Rectangle::getWidth()
{
	return this->width;
}
void Rectangle::draw()
{
	DrawManager::setColor(getColor());
	DrawManager::rectangle(x,y,width,height);
}
void Rectangle::setBounspeed(GLint x, GLint y, GLint width, GLint height)
{
	this->x = x;
	this->y = y;
	this->height = height;
	this->width = width;
}
void Rectangle::save(ofstream& out)
{
	Object::save(out);
	out << width << " " << height << endl;
}
void Rectangle::load(ifstream& in)
{
	Object::load(in);
	in >> width >> height ;
}