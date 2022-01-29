#include "Headers.h"
#include "Externs.h"
PaddleManager::PaddleManager()
{
	y = 10;
	width = PADDLE_WIDTH;
	height = 20;
	extension = 40;
	compression = 40;
	minWidth = 30;
	shootingPaddle = false;
	grabPaddle = false;
	bulletCount = 0;
}
PaddleManager::~PaddleManager()
{

}
void PaddleManager::init()
{
	x = WindowManager::getWidth() / 2;
	y = 10;
	width = PADDLE_WIDTH;
	height = 20;
	extension = 30;
	compression = 30;
	minWidth = 30;
	shootingPaddle = false;
	grabPaddle = false;
	bulletCount = 0;
}
void PaddleManager::update()
{

}
void PaddleManager::set()
{
	x = lastX = WindowManager::getWidth() / 2;
	y = 10;
	width = PADDLE_WIDTH;
	shootingPaddle = false;
	grabPaddle = false;
	bulletCount = 0;
}
void PaddleManager::reset()
{
	// x = WindowManager::getWidth() / 2;
	// 
	y = 10;
	width = PADDLE_WIDTH;
	shootingPaddle = false;
	grabPaddle = false;
	bulletCount = 0;
}
void PaddleManager::shoot()
{
	if (shootingPaddle)
	{
		AudioManager::play(AudioManager::SHOOT);
		bullets.add(x - width / 2 + 4, y + height);
		bullets.add(x + width / 2 - 4, y + height);
		bulletCount--;
		if (bulletCount == 0) shootingPaddle = false;
	}
}
void PaddleManager::move(int mx)
{
	x = mx;
}

void PaddleManager::draw()
{
	glPushMatrix();
	glTranslatef(-width / 2.0, 0, 0);
	DrawManager::setColor(100, 100, 100);
	DrawManager::filledRectangle(x + 4 - width / 2.0, y, width - 8, height / 2);
	DrawManager::setColor(120, 120, 120);
	DrawManager::filledRectangle(x + 4 - width / 2.0, y + height / 2, width - 8, height / 2);
	GLfloat c[] = { x - width / 2.0, x + 4 - width / 2.0, x + 10 - width / 2.0, x + 10 - width / 2.0, x + 4 - width / 2.0, x - width / 2.0 };
	GLfloat d[] = { y + 3, y, y, y + height, y + height, y + height - 3 };
	GLfloat e[] = { x + width - 10 - width / 2.0, x + width - 4 - width / 2.0, x + width - width / 2.0, x + width - width / 2.0, x + width - 4 - width / 2.0, x + width - 10 - width / 2.0 };
	GLfloat f[] = { y, y, y + 3, y + height - 3, y + height, y + height };
	DrawManager::setColor(188, 3, 57);
	DrawManager::filledPolygon(c, d, 6);
	DrawManager::filledPolygon(e, f, 6);
	if (shootingPaddle)
	{
		Bullet::draw(x + 4 - width / 2.0, y + height);
		Bullet::draw(x + width - 4 - width / 2.0, y + height);
	}
	for (int i = 0; i < balls.getTotal(); i++)
	{
		if (balls.getCell(i).isOnPaddle() && menu.getMenu() == MenuManager::GAME)
		{
			glLineWidth(3.0);
			if ((int)(GameManager::getTime() / 5) % 4 == 0)
			{
				DrawManager::setColor(235, 211, 187);
				GLfloat x = this->x - width / 2.0;
				GLfloat X[] = {
					x,
					x + width / 5,
					x + (2 * width / 5),
					x + (4 * width / 5),
					x + width
				};
				GLfloat Y[] = {
					 y + 2 * height,
					 y + 1.9 * height,
					 y + 2.2 * height,
					 y + 1.3 * height,
					 y + 2.1 * height
				};
				DrawManager::polygon(X, Y, 5, false);
			}
			else if ((int)(GameManager::getTime() / 5) % 4 == 1)
			{
				DrawManager::setColor(235, 211, 187);
				GLfloat x = this->x - width / 2.0;
				GLfloat X[] = {
					x,
					x + width / 3,
					x + width / 2,
					x + (2 * width / 3),
					x + width
				};
				GLfloat Y[] = {
					y + 1.9 * height,
					 y + 1.8 * height,
					 y + 1.3 * height,
					 y + 1.8 * height,
					 y + 1.9 * height
				};
				DrawManager::polygon(X, Y, 5, false);
			}
			else if ((int)(GameManager::getTime() / 5) % 4 == 2)
			{
				DrawManager::setColor(235, 211, 187);
				GLfloat x = this->x - width / 2.0;
				GLfloat X[] = {
					x,
					x + width / 5,
					x + width / 3,
					x + width / 2,
					x + (2 * width / 3),
					x + (4 * width / 5),
					x + width
				};
				GLfloat Y[] = {
					y + 2 * height,
					y + 1.8 * height,
					y + 1.3 * height,
					y + 1.7 * height,
					y + 1.3 * height,
					y + 2 * height,
					y + 2 * height
				};
				DrawManager::polygon(X, Y, 7, false);
			}
			else
			{
				DrawManager::setColor(235, 211, 187);
				GLfloat x = this->x - width / 2.0;
				GLfloat X[] = {
					x,
					x + width / 5,
					x + width / 3,
					x + width / 2,
					x + (3 * width / 4),
					x + (4 * width / 5),
					x + (5 * width / 6),
					x + width
				};
				GLfloat Y[] = {
					y + 1.9 * height,
					y + 1.9 * height,
					y + 1.3 * height,
					y + 2 * height,
					y + 2 * height,
					y + 1.7 * height,
					y + 2 * height,
					y + 1.9 * height
				};
				DrawManager::polygon(X, Y, 8, false);
			}
			glLineWidth(2.0);

			if (!shootingPaddle)
			{
				DrawManager::setColor(80, 80, 80);
				{
					GLfloat x = this->x - width / 2.0;
					GLfloat y = this->y + height;
					GLfloat X[] = { x, x + 4, x + 4, x };
					GLfloat Y[] = { y, y + 4, y + 10 + 4, y + 10 + 4 + 4 };
					DrawManager::filledPolygon(X, Y, 4);
				}
				{
					GLfloat x = this->x - width / 2.0 + width;
					GLfloat y = this->y + height;
					GLfloat X[] = { x - 4, x, x, x - 4 };
					GLfloat Y[] = { y + 4, y,y + 10 + 4 + 4, y + 10 + 4 };
					DrawManager::filledPolygon(X, Y, 4);
				}
			}
			break;
		}
	}

	DrawManager::setColor(5, 5, 5);
	DrawManager::line(x - width / 2.0 + 10, y + 1 * height / 4, x - width / 2.0 + width - 10, y + 1 * height / 4);
	DrawManager::line(x - width / 2.0 + 10, y + 2 * height / 4, x - width / 2.0 + width - 10, y + 2 * height / 4);
	DrawManager::line(x - width / 2.0 + 10, y + 3 * height / 4, x - width / 2.0 + width - 10, y + 3 * height / 4);
	glPopMatrix();


}

void PaddleManager::addBullets(GLint bullets)
{
	bulletCount += bullets;
}
void PaddleManager::toggleGrabPaddle()
{
	grabPaddle = !grabPaddle;
}
void PaddleManager::toggleShootingPaddle()
{
	shootingPaddle = !shootingPaddle;
}
bool PaddleManager::isGrabPaddle()
{
	return grabPaddle;
}
bool PaddleManager::isShootingPaddle()
{
	return shootingPaddle;
}

void PaddleManager::shrink()
{
	if (width - compression >= minWidth)
	{
		width -= compression;
		for (int i = 0; i < balls.getTotal(); i++)
		{

			if (balls.getCell(i).isOnPaddle())
			{
				if (balls.getCell(i).getX() < x - width / 2) balls.getCell(i).setX(x - width / 2);
				else if (balls.getCell(i).getX() > x + width / 2) balls.getCell(i).setX(x + width / 2);
			}
		}

		MouseManager::setX(x);
	}
}
void PaddleManager::superShrink()
{
	width = minWidth;
	for (int i = 0; i < balls.getTotal(); i++)
	{
		if (balls.getCell(i).isOnPaddle())
		{
			if (balls.getCell(i).getX() < x - width / 2) balls.getCell(i).setX(x - width / 2);
			else if (balls.getCell(i).getX() > x + width / 2) balls.getCell(i).setX(x + width / 2);
		}
	}

	MouseManager::setX(x);
}
void PaddleManager::extend()
{
	if (width + extension <= field.getWidth())
	{
		width += extension;
		if (x - width / 2 - extension / 2 >= field.getX())
		{
			if (x + width / 2 >= field.getX() + field.getWidth())
			{
				x = field.getX() + field.getWidth() - width / 2;
			}
		}
		else
		{
			x = field.getX();
		}
		MouseManager::setX(x);
	}
}

GLint PaddleManager::getBullets()
{
	return bulletCount;
}
void PaddleManager::save(ofstream& out)
{
	Rectangle::save(out);
	out << bulletCount << endl;
	out << shootingPaddle << " " << grabPaddle << endl;;
}
void PaddleManager::load(ifstream& in)
{
	Rectangle::load(in);
	in >> bulletCount;
	in >> shootingPaddle >> grabPaddle;
}
