#include "Headers.h"
BulletsManager::BulletsManager()
{
	speedY = 10;
}
void BulletsManager::add(GLint x,GLint y)
{
	Bullet b(x, y);
	bulletsField.push_back(b);
}
void BulletsManager::update()
{
	for (int i=0;i<bulletsField.size();i++)
	{
		bulletsField[i].setY(bulletsField[i].getY()+speedY);
		if (bulletsField[i].getY() > WindowManager::getHeight())
		{
			bulletsField.erase(bulletsField.begin() + i);
			i--;
		}
	}
}
void BulletsManager::draw()
{
	for (auto i : bulletsField)
	{
		i.draw();
	}
}

Bullet BulletsManager::getCell(GLint i)
{
	return bulletsField[i];
}
void BulletsManager::remove(GLint i)
{
	bulletsField.erase(bulletsField.begin() + i);
}
GLint BulletsManager::getTotal()
{
	return bulletsField.size();
}
void BulletsManager::set()
{
	bulletsField.clear();
}
void BulletsManager::init()
{
	bulletsField.clear();
}
void BulletsManager::reset()
{
	bulletsField.clear();
}
void BulletsManager::save(ofstream& out)
{
	out << bulletsField.size() << endl;
	for (int i = 0;i < bulletsField.size();i++)
	{
		bulletsField[i].save(out);
	}
}
void BulletsManager::load(ifstream& in)
{
	int size;
	in >> size;
	bulletsField.resize(size);
	for (int i = 0;i < bulletsField.size();i++)
	{
		bulletsField[i].load(in);
	}
}