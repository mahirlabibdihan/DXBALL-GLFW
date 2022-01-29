#ifndef __SCORE_MANAGER__
#define __SCORE_MANAGER__
#include "Headers.h"
class ScoreManager {
	static GLint score,totalR;
	static GLfloat scoreX, scoreY;
	static string name;	// Name of player
public:	
	ScoreManager();
	static string getName();
	static void setScore(GLint);
	static GLint getScore();
	static void increase();	// Increasing the score after every pickup
	static void draw();	// Draw score at top right corner of GameManager::screen
	static void drawBoard();	// Draw score board
	static void drawGameOver();	// Draw score at gameover screen
	static void reset();
	static void init();
	static void save();
	static void edit();
	static void erase();
	static void nameEntry(int);	// Add every key that is pressed at gameover screen to player's name
	static GLint getTotal();
	static void save(ofstream& out);
	static void load(ifstream& in);
};
#endif

/*
struct
{
	char Name[40];
	int Score, Time;
} ScoreSheet[10];
*/