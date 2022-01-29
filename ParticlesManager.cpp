#include "Headers.h"
#include "Externs.h"
void ParticlesManager::add(GLfloat x, GLfloat y)
{
	Particle p(x, y);
	p.setDir(rand() % 15, rand() % 15);particlesField.push_back(p);
	p.setDir(rand() % 15, -rand() % 15);particlesField.push_back(p);
	p.setDir(-rand() % 15, rand() % 15);particlesField.push_back(p);
	p.setDir(-rand() % 15, -rand() % 15);particlesField.push_back(p);
}

void ParticlesManager::init()
{
	particlesField.clear();
}
void ParticlesManager::addspark(GLfloat x, GLfloat y)
{
	Particle p;

	GLfloat t, dt = 2 * PI / 10;
	for (int i = 0;i < balls.getTotal();i++)
	{
		for (t = 0; t <= 2 * PI + dt; t += dt)
		{
			p.setXY(x + (balls.getCell(i).getRadius() - 3) * cos(t), y + (balls.getCell(i). getRadius() - 3) * sin(t));
			p.setColor(235, 211, 187);
			p.setDir(fmod(rand(), 5) - 2.5, fmod(rand(), 5) - 2.5);
			particlesField.push_back(p);
		}
	}
}
void ParticlesManager::add(GLfloat x, GLfloat y, GLfloat dirX, GLfloat dirY)
{
	Particle p(x, y);
	p.setDir(dirX, dirY);
	particlesField.push_back(p);
}
void ParticlesManager::update()
{
	for (int i = 0;i < particlesField.size();i++)
	{
		if (abs(particlesField[i].getDirY()) < 2)
		{
			particlesField.erase(particlesField.begin() + i);
			i--;
		}
		else
		{
			particlesField[i].update();
			particlesField[i].speedDown();
		}
	}
}
void ParticlesManager::draw()
{
	for (auto i : particlesField)
	{
		i.draw();
	}
}
void ParticlesManager::reset()
{
	particlesField.clear();
}

void ParticlesManager::destroyBall(GLfloat x,GLfloat y)
{
	Particle p(x, y);

	for (int i = 0; i<200;i++)
	{	
		p.setColor(RED);
		p.setColor(rand()%256, rand() % 256, rand() % 256);
		p.setDir((rand()%2001-1000)/10.0, (rand() % 1001)/10.0);
		particlesField.push_back(p);
	}
}
void ParticlesManager::save(ofstream& out)
{
	out << particlesField.size() << endl;
	for (int i = 0;i < particlesField.size();i++)
	{
		particlesField[i].save(out);
	}
}
void ParticlesManager::load(ifstream& in)
{
	int size;
	in >> size;
	particlesField.resize(size);
	for (int i = 0;i < particlesField.size();i++)
	{
		particlesField[i].load(in);
	}
}