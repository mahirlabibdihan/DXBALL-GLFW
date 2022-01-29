#include "Headers.h"
GLfloat ColorManager::clearR;
GLfloat ColorManager::clearG;
GLfloat ColorManager::clearB;
ColorManager::ColorManager()
{
	r = g = b = 255;
}
ColorManager::ColorManager(GLfloat r, GLfloat g, GLfloat b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}
void ColorManager::setColor(GLfloat r, GLfloat g, GLfloat b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}
void ColorManager::setColor(tuple<GLfloat, GLfloat, GLfloat>rgb)
{
	this->r = get<0>(rgb);
	this->g = get<1>(rgb);
	this->b = get<2>(rgb);
}
tuple<GLfloat, GLfloat, GLfloat> ColorManager::getColor()
{
	return make_tuple(r, g, b);
}

tuple<GLfloat, GLfloat, GLfloat> ColorManager::random()
{
	return make_tuple(rand()%256,rand()%256,rand()%256);
}
GLint ColorManager::getR()
{
	return r;
}
GLint ColorManager::getG()
{
	return g;
}
GLint ColorManager::getB()
{
	return b;
}
void ColorManager::save(ofstream& out)
{
	out << r << " " << g << " " << b << endl;
}
void ColorManager::load(ifstream& in)
{
	in >> r >> g >> b;
}