#include "Headers.h"
#include "Externs.h"
BallsManager::BallsManager()
{

}
BallsManager::~BallsManager()
{

}
void BallsManager::update()
{
	for (int i = 0;i < ballsField.size();i++)
	{
		ballsField[i].update();
		
		if (ballsField[i].getDirY() < 0  && ballsField[i].getY() < paddle.getY() + paddle.getHeight() / 2 - ballsField[i].getRadius())
		{
			particles.destroyBall(ballsField[i].getX(), ballsField[i].getY());
			ballsField.erase(ballsField.begin() + i);
			if(ballsField.empty()) GameManager::death();
			i--;
		}
	}
}
void BallsManager::draw()
{
	for (auto i : ballsField)
	{
		i.draw();
	}
}

Ball& BallsManager::getCell(GLint i)
{
	return ballsField[i];
}
void BallsManager::add(GLfloat angle)
{
	Ball temp;
	temp.init();
	temp.set();	
	temp.setAngle(angle);
	temp.setSpeed(ballsField[0].getSpeed());
	if(ballsField.size()<8)ballsField.push_back(temp);
}
void BallsManager::add(Ball ball)
{
	ball.setAngle(rand() % 628 / 100.0);
	if (ballsField.size() < 8)ballsField.push_back(ball);
}
void BallsManager::remove(GLint i)
{
	ballsField.erase(ballsField.begin() + i);
}
GLint BallsManager::getTotal()
{
	return ballsField.size();
}
void BallsManager::set()
{
	ballsField.clear();
	Ball temp;
	temp.init();
	temp.set();
	ballsField.push_back(temp);
	fireBall = thruBall = false;
}
void BallsManager::init()
{
	ballsField.clear();
	fireBall = thruBall = false;
}

void BallsManager::reset()
{
	ballsField.clear();
	Ball temp;
	temp.init();
	temp.set();
	ballsField.push_back(temp);
	fireBall = thruBall = false;
}
void BallsManager::save(ofstream& out)
{
	out << fireBall << " " << thruBall << endl;
	out << ballsField.size() << endl;
	for (int i = 0;i < ballsField.size();i++)
	{
		ballsField[i].save(out);
	}
}
void BallsManager::load(ifstream& in)
{
	int size;
	in >> fireBall >> thruBall;
	in >> size;
	ballsField.resize(size);
	for (int i = 0;i < ballsField.size();i++)
	{
		ballsField[i].load(in);
	}
}
void BallsManager::toggleFireBall()
{
	for (auto& i : ballsField)
	{
		i.toggleFireBall();
	}
	fireBall = !fireBall;
}
bool BallsManager::isFireBall()
{
	return fireBall;
}
void BallsManager::toggleThruBall()
{
	for (auto& i : ballsField)
	{
		i.toggleThruBall();
	}
	thruBall = !thruBall;
}
bool BallsManager::isThruBall()
{
	return thruBall;
}
void BallsManager::speedUp()
{
	for (int i = 0;i < ballsField.size();i++)
	{
		ballsField[i].speedUp();
	}
	
}
void BallsManager::speedDown()
{
	for (int i = 0;i < ballsField.size();i++)
	{
		ballsField[i].speedDown();
	}
}
void BallsManager::shrink()
{
	for (auto& i : ballsField)
	{
		i.shrink();
	}
}
void BallsManager::extend()
{
	for (auto& i : ballsField)
	{
		i.extend();
	}
}
bool BallsManager::isOnPaddle()
{
	for (int i = 0;i < getTotal();i++)
	{
		if (ballsField[i].isOnPaddle())
		{
			return true;
		}
	}
	return false;
}