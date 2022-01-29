#ifndef __LEVEL_MANAGER__
#define __LEVEL_MANAGER__
#include "Headers.h"
class LevelManager
{
	static GLint levelNum,totalLevels;
	static GLint cols,rows;
	static int*** levelField;
	// Level text files
	static const char* levels[11];
public:
	LevelManager();
	~LevelManager();
	static void init();
	static void set();	// Reading level from file
	static void reset();
	static void setTotalLevels(GLint);
	static GLint getCols();
	static GLint getRows();
	static bool levelUp();
	static bool levelDown();
	static char getCell(GLint,GLint);
	static void draw();	// Draw level number at top right corner of GameManager::screen
	static GLint getTotalLevels();
	static GLint getLevel();
	static void setLevel(GLint);
	static void save(ofstream& out);
	static void load(ifstream& in);
};
#endif

/*
struct
{
	int getX() = 460, getY() = ScreenHeight / 2 - 504, Mode = 8, MAX = 10;
	char *ImageBG = "Data\\Image\\LevelUp.bmp";
	char *Level[11] =
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
} LevelUp;*/