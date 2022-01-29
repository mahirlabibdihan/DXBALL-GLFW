#ifndef __MENU_MANAGER__
#define __MENU_MANAGER__
#include "TextureManager.h"
class MenuManager:public Rectangle {
	bool quit;
	TextureManager wallImage;
	TextureManager customImage;
	TextureManager dxImage;
	TextureManager helpImage;
	TextureManager lifeImage;
	TextureManager levelUpImage;
	TextureManager bulletImage;
	TextureManager gameOverImage;
	TextureManager nameEntryActiveImage;
	TextureManager nameEntryDeactiveImage;
	TextureManager winImage;
	TextureManager buttonImage[7];
	const char* button[7] =
	{
		"",
		"Data\\Image\\NewButton.png",
		"Data\\Image\\CustomButton.png",
		"Data\\Image\\ResumeButton.png",
		"Data\\Image\\HighScoreButton.png",
		"Data\\Image\\HelpButton.png",
		"Data\\Image\\QuitButton.png"
	};

	int buttonBound[7][5][10] = {
		{
			{},
			{},
			{},
			{},
			{}
		},
		{
			{7},
			{290, 305, 320, 330, 450, 400, 350},
			{455, 420, 390, 370, 435, 400, 525},
			{580, 450, 400, 370, 490, 425, 525},
			{525, 455, 420, 390, 455, 420, 540}
		},
		{
			{10},
			{300, 305, 325, 335, 355, 365, 445, 490, 490, 555},
			{530, 585, 545, 625, 625, 660, 625, 535, 585, 530},
			{325, 325, 490, 355, 445, 415, 465, 585, 525, 600},
			{590, 610, 625, 645, 660, 675, 645, 585, 610, 585}
		},
		{
			{7},
			{360, 382, 405, 480, 435, 525, 490},
			{335, 320, 305, 335, 355, 375, 400},
			{385, 480, 460, 505, 525, 550, 565},
			{355, 382, 310, 355, 412, 400, 440}
		},
		{
			{8},
			{440, 470, 490, 510, 530, 565, 600, 410},
			{665, 640, 625, 615, 605, 585, 650, 675},
			{560, 525, 510, 605, 655, 620, 635, 440},
			{705, 665, 640, 685, 645, 605, 670, 700}
		},
		{
			{3},
			{610, 655, 660},
			{520, 585, 500},
			{695, 690, 715},
			{585, 605, 525}
		},
		{
			{9},
			{460, 490, 510, 535, 525, 575, 585, 600, 600},
			{290, 295, 300, 320, 335, 365, 385, 420, 490},
			{505, 550, 575, 615, 640, 665, 685, 700, 655},
			{315, 325, 345, 365, 385, 415, 445, 490, 505}
		},
	};
public:
	bool back,left,right,play,nameEntry;
	TextureManager hsImage;
	enum option { NONE , NEWGAME , CUSTOM , RESUME , HIGHSCORE, HELP , QUIT };
	enum menus {MAIN,GAME,CUSTOM_GAME,HIGH_SCORE,HELP_PAGE,QUIT_GAME,GAME_OVER,WINNER,LEVEL_UP,NAME_ENTRY,DEATH};
	MenuManager();
	~MenuManager();
	void init();
	GLint getMenu();
	GLint getOption();
	void setOption(option);
	void setMenu(menus);
	void draw();
	void drawWin();
	void drawGame();
	void drawMainMenu();
	void drawGameOver();
	void drawHighScore();
	void drawHelp();
	void drawCustom();
	void drawNameEntry();
	void drawBack();
	void drawLevelUp();
	void drawQuit();
	void menuSelection(GLint,GLint);

private:
	menus menuName;
	option menuOption;
};
#endif