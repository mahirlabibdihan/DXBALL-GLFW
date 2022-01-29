#include "Headers.h"
#include "Externs.h"
Ball::Ball()
{
	radius = BALL_RADIUS;
	fireBall = false, thruBall = false ,onPaddle = true;
	theta = 0;
	speed = BALL_SPEED;
}
Ball::~Ball()
{

}
void Ball::init()
{
	x = paddle.getX() + paddle.getWidth() / 2,
	y = paddle.getY() + paddle.getHeight() + radius + Ball_Board;
	radius = BALL_RADIUS;  fireBall = false;
	onPaddle = true;
	theta = 0;
	speed = BALL_SPEED;
}
void Ball::set()
{
	x = paddle.getX();
	radius = BALL_RADIUS; fireBall = false, thruBall = false;
	y = paddle.getY() + paddle.getHeight() + radius + Ball_Board;
	onPaddle = true;
	theta = 0;
	speed = BALL_SPEED;
}
void Ball::reset()
{
	radius = BALL_RADIUS; fireBall = false, thruBall = false;
	onPaddle = true;
	x = paddle.getX();
	y = paddle.getY() + paddle.getHeight() + radius + Ball_Board;
	theta = 0;
	speed = BALL_SPEED;
}

GLfloat Ball::getAngle()
{
	return theta;
}
void Ball::setAngle(GLfloat theta)
{
	this->theta = theta;
}

void Ball::reverseX()
{
	theta = PI - theta;
}
void Ball::reverseY()
{
	theta = 2 * PI - theta;
}
void Ball::update()
{
	if (!onPaddle)
	{
		x += speed * cos(theta);
		y += speed * sin(theta);
		if (fireBall)
		{
			particles.addspark(x, y);
		}
	}

	if (y > WindowManager::getHeight() - radius)
	{
		AudioManager::play(AudioManager::BALL_X_WALL);
		reverseY();
		y = WindowManager::getHeight() - radius;
		particles.add(x, WindowManager::getHeight());
		particles.add(x, WindowManager::getHeight());
	}
	else if (x < field.getX() + radius)
	{
		AudioManager::play(AudioManager::BALL_X_WALL);
		reverseX();
		x = field.getX() + radius;
		particles.add(field.getX(), y);
	}
	else if (x > field.getX() + field.getWidth() - radius)
	{
		AudioManager::play(AudioManager::BALL_X_WALL);
		reverseX();
		x = field.getX() + field.getWidth() - radius;   
		particles.add(field.getX() + field.getWidth(), y);

	}
}

void Ball::move(GLint mx)
{
	x = x + mx - paddle.getX();
}

void Ball::draw()
{
	if (fireBall) DrawManager::setColor(255, 120, 13);
	else if(thruBall)  DrawManager::setColor(153,0,0);
	else DrawManager::setColor(100, 100, 100);
	DrawManager::filledCircle(x, y, radius);
	if (fireBall) DrawManager::setColor(255, 150, 13);
	else if (thruBall)  DrawManager::setColor(204,0,0);
	else DrawManager::setColor(150, 150, 150);
	DrawManager::filledCircle(x - 0.1 * radius, y + 0.2 * radius, 0.8 * radius);
	if (fireBall) DrawManager::setColor(255, 170, 13);
	else if (thruBall)  DrawManager::setColor(255,0, 0);
	else DrawManager::setColor(200, 200, 200);
	DrawManager::filledCircle(x - 0.3 * radius, y + 0.5 * radius, 0.4 * radius);
}


void Ball::speedUp()
{
	speed *= 1.3;
}
void Ball::speedDown()
{
	speed *= .7;
}
GLfloat Ball::getSpeed()
{
	return speed;
}
void Ball::setSpeed(GLfloat speed)
{
	this->speed = speed;
}
void Ball::stickToPaddle()
{
	onPaddle = true;
}
void Ball::launch()
{
	onPaddle = false;
}

bool Ball::isOnPaddle()
{
	return onPaddle;
}
void Ball::shrink()
{
	
	if (radius >= BALL_RADIUS)
	{
		
		radius = BALL_RADIUS * 0.6;
		if (onPaddle)
		{
			y = paddle.getY() + paddle.getHeight() + Ball_Board + radius;
		}
		else
		{
		}
	}
}
void Ball::extend()
{
	if (radius <= BALL_RADIUS)
	{
		radius = BALL_RADIUS * 1.5;
		if (onPaddle)
		{
			y = paddle.getY() + paddle.getHeight() + Ball_Board + radius;
		}
		else
		{
		}
	}
}
void Ball::toggleFireBall()
{
	fireBall = !fireBall;
}
bool Ball::isFireBall()
{
	return fireBall;
}
void Ball::toggleThruBall()
{
	thruBall = !thruBall;
}
bool Ball::isThruBall()
{
	return thruBall;
}

GLfloat Ball::getDirX()
{
	return speed*cos(theta);
}
GLfloat Ball::getDirY()
{
	return speed*sin(theta);
}
void Ball::save(ofstream& out)
{
	Circle::save(out);
	out << theta << " "<<speed << endl;
	out << fireBall << " " << thruBall << " " << onPaddle << endl;
}
void Ball::load(ifstream& in)
{
	Circle::load(in);
	in >> theta >> speed;
	in >> fireBall >> thruBall >> onPaddle;
}

