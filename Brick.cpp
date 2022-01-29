#include "Headers.h"
#include "Externs.h"
Brick::Brick()
{
	setXY(0, 0);
	width = BRICK_WIDTH;
	height = BRICK_HEIGHT;
}
Brick::Brick(GLint x,GLint y)
{
	setXY(x, y);
	width = BRICK_WIDTH;
	height = BRICK_HEIGHT;
}
Brick::~Brick()
{

}
void Brick::setStrength(int strength)
{
	this->strength = strength;
}
int Brick::getStrength()
{
	return strength;
}

void Brick::damage()
{
	if (strength > 0)
	{
		strength--;
	}
	else
	{
		strength = abs(strength);
	}
}
void Brick::drawNormal(GLfloat x, GLfloat y)
{
	
	GLfloat a[] = { x, x, x + width };
	GLfloat b[] = { y, y + height, y + height };
	GLfloat c[] = { x, x + width, x + width };
	GLfloat d[] = { y, y, y + height };
	DrawManager::setColor(getR() + 8, getG() + 8, getB() + 8);
	DrawManager::filledPolygon(a, b, 3);
	DrawManager::setColor(getR() - 10, getG() - 10, getB() - 10);
	DrawManager::filledPolygon(c, d, 3);
	DrawManager::setColor(getR(), getG(), getB());
	DrawManager::filledRectangle(x + 12, y + 8, width - 24, height - 16);
}
void Brick::drawNormal(GLfloat x, GLfloat y,GLfloat R, GLfloat G, GLfloat B)
{
	
	GLfloat a[] = { x, x, x + BRICK_WIDTH };
	GLfloat b[] = { y, y + BRICK_HEIGHT, y + BRICK_HEIGHT };
	GLfloat c[] = { x, x + BRICK_WIDTH, x + BRICK_WIDTH };
	GLfloat d[] = { y, y, y + BRICK_HEIGHT };
	DrawManager::setColor(R + 8, G + 8, B + 8);
	DrawManager::filledPolygon(a, b, 3);
	DrawManager::setColor(R - 10, G - 10, B - 10);
	DrawManager::filledPolygon(c, d, 3);
	DrawManager::setColor(R, G,B);
	DrawManager::filledRectangle(x + 12, y + 8, BRICK_WIDTH - 24, BRICK_HEIGHT - 16);
}
void Brick::drawExplosive(GLfloat x, GLfloat y)
{
	if ((int)(GameManager::getTime() / 10) % 2)
	{
		DrawManager::setColor(255, 127, 0);
		DrawManager::filledRectangle(x, y, BRICK_WIDTH, BRICK_HEIGHT);
		DrawManager::setColor(247, 147, 47);
		DrawManager::filledRectangle(x + 3, y + 3, BRICK_WIDTH - 6, BRICK_HEIGHT - 6);
		DrawManager::setColor(243, 171, 95);
		DrawManager::filledRectangle(x + 6, y + 6, BRICK_WIDTH - 12, BRICK_HEIGHT - 12);
		DrawManager::setColor(239, 191, 143);
		DrawManager::filledRectangle(x + 9, y + 9, BRICK_WIDTH - 18, BRICK_HEIGHT - 18);
		DrawManager::setColor(235, 211, 187);
		DrawManager::filledRectangle(x + 12, y + 12, BRICK_WIDTH - 24, BRICK_HEIGHT - 24);
		DrawManager::setColor(231, 231, 231);
		DrawManager::filledRectangle(x + 15, y + 15, BRICK_WIDTH - 30, BRICK_HEIGHT - 30);
	}
	else
	{
		DrawManager::setColor(231, 231, 231);
		DrawManager::filledRectangle(x, y, BRICK_WIDTH, BRICK_HEIGHT);
		DrawManager::setColor(235, 211, 187);
		DrawManager::filledRectangle(x + 3, y + 3, BRICK_WIDTH - 6, BRICK_HEIGHT - 6);
		DrawManager::setColor(239, 191, 143);
		DrawManager::filledRectangle(x + 6, y + 6, BRICK_WIDTH - 12, BRICK_HEIGHT - 12);
		DrawManager::setColor(239, 191, 143);
		DrawManager::setColor(243, 171, 95);
		DrawManager::filledRectangle(x + 9, y + 9, BRICK_WIDTH - 18, BRICK_HEIGHT - 18);
		DrawManager::setColor(247, 147, 47);
		DrawManager::filledRectangle(x + 12, y + 12, BRICK_WIDTH - 24, BRICK_HEIGHT - 24);
		DrawManager::setColor(255, 127, 0);
		DrawManager::filledRectangle(x + 15, y + 15, BRICK_WIDTH - 30, BRICK_HEIGHT - 30);
	}
}
void Brick::drawMultiHit(GLfloat x,GLfloat y)
{
	DrawManager::setColor(200, 165, 0);
	DrawManager::filledRectangle(x, y, BRICK_WIDTH, BRICK_HEIGHT);
	DrawManager::setColor(205, 175, 20);
	DrawManager::filledRectangle(x + 3, y + 3, BRICK_WIDTH - 6, BRICK_HEIGHT - 6);
	DrawManager::setColor(210, 185, 40);
	DrawManager::filledRectangle(x + 6, y + 6, BRICK_WIDTH - 12, BRICK_HEIGHT - 12);
	DrawManager::setColor(215, 195, 60);
	DrawManager::filledRectangle(x + 9, y + 9, BRICK_WIDTH - 18, BRICK_HEIGHT - 18);
	DrawManager::setColor(220, 205, 80);
	DrawManager::filledRectangle(x + 12, y + 12, BRICK_WIDTH - 24, BRICK_HEIGHT - 24);
	DrawManager::setColor(225, 215, 100);
	DrawManager::filledRectangle(x + 15, y + 15, BRICK_WIDTH - 30, BRICK_HEIGHT - 30);
}
void Brick::draw()
{
	
	switch (strength)
	{
	case -1:
		drawMultiHit(x+ board.getX(),y+ board.getY());
		break;
	case 0:
		return;
	case 1:
		drawNormal(x + board.getX(), y + board.getY());
		break;
	case 2:
		drawExplosive(x + board.getX(), y + board.getY());
		break;
	}
	//glPushMatrix();
	//glTranslatef(board.getX(), board.getY(), 0);
	DrawManager::setColor(5, 5, 5);
	DrawManager::rectangle(x+ board.getX(), y+ board.getY(), width, height);
	//glPopMatrix();
}

void Brick::save(ofstream& out)
{
	Rectangle::save(out);
	out << strength << endl;
}
void Brick::load(ifstream& in)
{
	Rectangle::load(in);
	in >> strength;
}