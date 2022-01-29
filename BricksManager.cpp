#include "Headers.h"
#include "Externs.h"
extern int timeLevelUp;

BricksManager::BricksManager()
{
	bricksField = NULL;
}
BricksManager::~BricksManager()
{

}
void BricksManager::remove(int i, int j,int k)
{
	if (bricksField[i][j].getStrength() == EXPLOSIVE)
	{
		bombs.push_back(bricksField[i][j]);
		AudioManager::play(AudioManager::BALL_X_EXPLOSIVE);
		int type = powerUps.generate();
		{
			powerUps.add(board.getX() + bricksField[i][j].getX(), board.getY() + bricksField[i][j].getY(), type,k); //bricksField[i][j].Type;
		}
		explode(i, j);
	}
	else if (balls.isThruBall())
	{
		if (abs(bricksField[i][j].getStrength()) == NORMAL)
		{
			//destroyed.push_back(bricksField[i][j]);
			particles.add(board.getX() + bricksField[i][j].getX() + bricksField[i][j].getWidth() / 2, board.getY() + bricksField[i][j].getY() + bricksField[i][j].getHeight() / 2);
			particles.add(board.getX() + bricksField[i][j].getX() + bricksField[i][j].getWidth() / 2, board.getY() + bricksField[i][j].getY() + bricksField[i][j].getHeight() / 2);
			bricksField[i][j].setStrength(0);
			AudioManager::play(AudioManager::BALL_X_NORMAL);
			remaining--;
			ScoreManager::increase();

			if (rand() % 4 == 0)
			{
				int type = powerUps.generate();
				{
					powerUps.add(board.getX() + bricksField[i][j].getX(), board.getY() + bricksField[i][j].getY(), type,k); //bricksField[i][j].Type;
				}
			}
		}
	}
	else if (bricksField[i][j].getStrength() == NORMAL)
	{
		destroyed.push_back(bricksField[i][j]);
		particles.add(board.getX() + destroyed.back().getX() + destroyed.back().getWidth() / 2, board.getY() + destroyed.back().getY() + destroyed.back().getHeight() / 2);
		particles.add(board.getX() + destroyed.back().getX() + destroyed.back().getWidth() / 2, board.getY() + destroyed.back().getY() + destroyed.back().getHeight() / 2);
		bricksField[i][j].setStrength(0);
		AudioManager::play(AudioManager::BALL_X_NORMAL);
		remaining--;
		ScoreManager::increase();
		{
			if (rand() % 3 == 0)
			{
				int type = powerUps.generate();
				{
					powerUps.add(board.getX() + bricksField[i][j].getX(), board.getY() + bricksField[i][j].getY(), type,k); //bricksField[i][j].Type;
				}
			}
		}
	}
	else if (bricksField[i][j].getStrength() == MULTIHIT)
	{
		particles.add(board.getX() + bricksField[i][j].getX() + bricksField[i][j].getWidth() / 2, board.getY() + bricksField[i][j].getY() + bricksField[i][j].getHeight() / 2);
		bricksField[i][j].setStrength(1);
		AudioManager::play(AudioManager::BALL_X_MULTIHIT);
	}
}

void BricksManager::explode(int i, int j)
{
	if (abs(bricksField[i][j].getStrength()) == NORMAL)
	{
		remaining--;
		ScoreManager::increase();
		bombs.push_back(bricksField[i][j]);
		bricksField[i][j].setStrength(0);
	}
	else if (bricksField[i][j].getStrength() == EXPLOSIVE)
	{
		remaining--;
		ScoreManager::increase();
		bombs.push_back(bricksField[i][j]);
		bricksField[i][j].setStrength(0);
		if (i > 0 & j > 0) explode(i - 1, j - 1);
		if (i > 0 & j < rows - 1) explode(i - 1, j + 1);
		if (i < cols - 1 & j > 0) explode(i + 1, j - 1);
		if (i < cols - 1 & j < rows - 1) explode(i + 1, j + 1);
		if (i > 0) explode(i - 1, j);
		if (j > 0) explode(i, j - 1);
		if (i < cols - 1) explode(i + 1, j);
		if (j < rows - 1) explode(i, j + 1);
	}
}
void BricksManager::explodeAll()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (bricksField[i][j].getStrength() == EXPLOSIVE)
			{
				explode(i, j);
			}
		}
	}
}
void BricksManager::expandExploding()
{
	vector<pair<int, int>> temp;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (bricksField[i][j].getStrength() == EXPLOSIVE)
			{
				if (i > 0) temp.push_back({ i - 1,j });
				if (j > 0) temp.push_back({ i,j - 1 });
				if (i < rows - 1) temp.push_back({ i + 1,j });
				if (j < cols - 1) temp.push_back({ i ,j + 1 });
			}
		}
	}

	for (auto i : temp)
	{
		if (bricksField[i.first][i.second].getStrength() == 0) remaining++;
		bricksField[i.first][i.second].setStrength(EXPLOSIVE);
	}
}
void BricksManager::levelWrap()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (bricksField[i][j].getStrength())
			{
				remaining--;
				ScoreManager::increase();
				bombs.push_back(bricksField[i][j]);
				bricksField[i][j].setStrength(0);
			}
		}
	}
}
int BricksManager::getRows()
{
	return rows;
}

int BricksManager::getCols()
{
	return cols;
}
void BricksManager::draw()
{
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			bricksField[i][j].draw();
		}
	}

	for (int i = 1;i < bombs.size();i++)
	{
		bombs[i].draw();
	}

	for (auto i : destroyed)
	{
		i.draw();
	}
	particles.draw();
}

void BricksManager::update()
{
	if (bombs.size() > 1)
	{
		if (bombs.size() % 5 == 0)AudioManager::play(AudioManager::BALL_X_EXPLOSIVE);
		//remaining--;
		//ScoreManager::increase();
		//destroyed.push_back(bombs.back());

		int MIN = 1;
		for (int i = 1;i < bombs.size();i++)
		{

			if (abs(bombs[i].getX() - bombs[0].getX()) + abs(bombs[i].getY() - bombs[0].getY())
				<
				abs(bombs[MIN].getX() - bombs[0].getX()) + abs(bombs[MIN].getY() - bombs[0].getY()))
			{
				MIN = i;
			}
		}
		particles.add(board.getX() + bombs[MIN].getX() + bombs[MIN].getWidth() / 2, board.getY() + bombs[MIN].getY() + bombs[MIN].getHeight() / 2);
		//bombs.pop_back();
		bombs.erase(bombs.begin() + MIN);
	}
	else
	{
		bombs.clear();
	}

	for (int i = 0;i < destroyed.size();i++)
	{
		destroyed[i].setX(destroyed[i].getX() + 4.9);
		destroyed[i].setY(destroyed[i].getY() + 2.1);
		destroyed[i].setWidth(destroyed[i].getWidth() - 9.8);
		destroyed[i].setHeight(destroyed[i].getHeight() - 4.2);

		if (destroyed[i].getHeight() <= 6 || destroyed[i].getWidth() <= 14)
		{
			destroyed.erase(destroyed.begin() + i);
			i--;
		}
	}
	particles.update();
	if (remaining <= 0 && bombs.empty() && destroyed.empty())
	{
		AudioManager::play(AudioManager::LEVEL_UP);
		particles.reset();
		timeLevelUp = glfwGetTime();
		if (LevelManager::getLevel() == LevelManager::getTotalLevels())
		{
			AudioManager::stopAll();
			menu.setMenu(MenuManager::WINNER);
		}
		else if (LevelManager::getLevel() == 0)
		{
			AudioManager::stopAll();
			menu.setMenu(MenuManager::WINNER);
		}
		else
		{
			timeLevelUp = glfwGetTime();
			menu.setMenu(MenuManager::LEVEL_UP);
		}
	}
}
Brick& BricksManager::getCell(GLint i, GLint j)
{
	return bricksField[i][j];
}

int BricksManager::getHeight()
{
	return height;
}
int BricksManager::getWidth()
{
	return width;
}

void BricksManager::set()
{
	rows = LevelManager::getRows();
	cols = LevelManager::getCols();
	width = 70;
	height = 30;

	remaining = 0;
	// Allocating memory 
	bricksField = new Brick * [rows];
	for (GLint i = 0; i < rows; i++)
	{
		bricksField[i] = new Brick[cols];
	}

	// Transfering the information from levelfield to tilesfield
	for (GLint i = 0; i < rows; i++)
	{
		for (GLint j = 0; j < cols; j++)
		{
			Brick b(j * width, i * height);
			b.setStrength(LevelManager::getCell(i, j));
			int R = (LevelManager::getLevel() % 3 == 1 ? i * i : LevelManager::getLevel() % 3 == 2 ? i * i : i * j); //i*i
			int G = (LevelManager::getLevel() % 3 == 1 ? i * j : LevelManager::getLevel() % 3 == 2 ? i * i : j * j); //i*j
			int B = (LevelManager::getLevel() % 3 == 1 ? j * j : LevelManager::getLevel() % 3 == 2 ? i * i : j * i); //j*j
			b.setColor(R, G, B);
			if (b.getStrength()) remaining++;
			bricksField[i][j] = b;
		}
	}
}
void BricksManager::reset()
{
	bombs.clear();
	destroyed.clear();
}

GLint BricksManager::getRemaining()
{
	return remaining;
}
void BricksManager::setRemaining(GLint rem)
{
	remaining = rem;
}
void BricksManager::init()
{
	remaining = 0;
}
void BricksManager::save(ofstream& out)
{
	out << rows << " " << cols << endl;
	out << width << " " << height << endl;
	out << remaining << endl;
	for (GLint i = 0; i < rows; i++)
	{
		for (GLint j = 0; j < cols; j++)
		{
			bricksField[i][j].save(out);
		}
	}

	out << bombs.size() << endl;
	for (int i = 0;i < bombs.size();i++)
	{
		bombs[i].save(out);
	}

	out << destroyed.size() << endl;
	for (int i = 0;i < destroyed.size();i++)
	{
		destroyed[i].save(out);
	}
}
void BricksManager::load(ifstream& in)
{
	in >> rows >> cols;
	in >> width >> height;
	in >> remaining;

	bricksField = new Brick * [rows];
	for (GLint i = 0; i < rows; i++)
	{
		bricksField[i] = new Brick[cols];
	}
	for (GLint i = 0; i < rows; i++)
	{
		for (GLint j = 0; j < cols; j++)
		{
			bricksField[i][j].load(in);
		}
	}

	int size;
	in >> size;
	bombs.resize(size);
	for (int i = 0;i < bombs.size();i++)
	{
		bombs[i].load(in);
	}

	in >> size;
	destroyed.resize(size);
	for (int i = 0;i < destroyed.size();i++)
	{
		destroyed[i].load(in);
	}

}
