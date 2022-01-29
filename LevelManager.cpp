#include "Headers.h"
const char* LevelManager::levels[11] =
{
	"Data\\Levels\\level0.txt",
	"Data\\Levels\\level1.txt",
	"Data\\Levels\\level2.txt",
	"Data\\Levels\\level3.txt",
	"Data\\Levels\\level4.txt",
	"Data\\Levels\\level5.txt",
	"Data\\Levels\\level6.txt",
	"Data\\Levels\\level7.txt",
	"Data\\Levels\\level8.txt",
	"Data\\Levels\\level9.txt",
	"Data\\Levels\\level10.txt"
};
GLint LevelManager::levelNum, LevelManager::totalLevels;
GLint LevelManager::cols, LevelManager::rows;
int*** LevelManager::levelField;
LevelManager::LevelManager()
{
	levelNum = totalLevels = 0;
	cols = rows = 0;
	levelField = NULL;
}
LevelManager::~LevelManager()
{
	// Deallocating memory
	for (GLint i = 0; i < rows; i++)
	{
		delete[] levelField[i];
	}
	delete[] levelField;
}
void LevelManager::init()
{
	totalLevels = 10;
	levelNum = 0;
	cols = rows = 20;
	levelField = new int**[totalLevels+1];
	for (int i = 0;i <= totalLevels;i++)
	{
		levelField[i] = new int* [rows];
		for (int j = 0; j < rows; j++)
		{
			levelField[i][j] = new int[cols];
		}

		ifstream in(levels[i], ios::in);
		if (!in)
		{
			cout << "File Reading error" << endl;
			return;
		}
		for (int j = rows - 1; j > -1; j--)
		{
			for (int k = 0; k < cols; k++)
			{
				in >> levelField[i][j][k];
			}
		}
		in.close();
	}
}
void LevelManager::setTotalLevels(GLint n)
{
	totalLevels = n;
}

GLint LevelManager::getTotalLevels()
{
	return totalLevels;
}
void LevelManager::set()
{
	/*ifstream in(levels[levelNum], ios::in);
	if (!in)
	{
		cout << "File Reading error" << endl;
		return;
	}
	in >> rows >> cols;
	cout << rows << " " << cols << endl;

	// Allocating memory
	levelField = new int* [rows];
	for (GLint i = 0; i < rows; i++)
	{
		levelField[i] = new int[cols];
	}

	for (GLint i = rows - 1; i > -1; i--)
	{
		for (GLint j = 0; j < cols; j++)
		{
			in >> levelField[i][j];
		}
	}
	in.close();*/
}
GLint LevelManager::getCols()
{
	return cols;
}
GLint LevelManager::getRows()
{
	return rows;
}
bool LevelManager::levelUp()
{
	if (levelNum < totalLevels)
	{
		levelNum++;
		GameManager::reset();
		GameManager::set();
		return true;
		//MODE = LevelUp.Mode;
	}
	else if (levelNum == totalLevels)
	{
		//iLevelUp();
	}
	else
	{
		//Custom.Win = 1;
	}
	return false;
}
bool LevelManager::levelDown()
{
	if (levelNum > 0)
	{
		levelNum--;
		GameManager::set();
		return true;
		//MODE = LevelUp.Mode;
	}
	return false;
}
char LevelManager::getCell(GLint row, GLint col)
{
	return levelField[levelNum][row][col];
}

void LevelManager::reset()
{
	levelNum = 0;
}

void LevelManager::draw()
{
	char temp[40];
	snprintf(temp, 40, "LEVEL :  %d", levelNum);
	DrawManager::setColor(RED);
	TextManager::render(WindowManager::getWidth() - 200, WindowManager::getHeight() - 150, temp);
}
GLint LevelManager::getLevel()
{
	return levelNum;
}
void LevelManager::setLevel(GLint n)
{
	levelNum = n;
}
void LevelManager::save(ofstream& out)
{
	out << levelNum << endl;
}
void LevelManager::load(ifstream& in)
{
	in >> levelNum;
}
