#define STB_IMAGE_IMPLEMENTATION
#include "Headers.h"
int Circle::getRadius()
{
	return radius;
}
void Circle::setRadius(int radius)
{
	this->radius = radius;
}
void Circle::save(ofstream& out)
{
	Object::save(out);
	out << this->radius << endl;
}
void Circle::load(ifstream& in)
{
	Object::load(in);
	in >> radius;
}
void Circle::draw()
{
	
}