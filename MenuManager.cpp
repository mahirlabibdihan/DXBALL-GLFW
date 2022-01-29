#include "Headers.h"
#include <stb_image.h>
#include "Externs.h"
MenuManager::MenuManager()
{
	quit = false;
	x = 460;
	y = 50;
	menuName = MAIN;
	menuOption = NONE;
}
MenuManager::~MenuManager()
{
	
}
void MenuManager::init()
{
	setMenu(MAIN);
	int n;
	stbi_set_flip_vertically_on_load(true);
	wallImage.load("Data\\Image\\Wall.jpg");
	customImage.load("Data\\Image\\Custom.png");
	dxImage.load("Data\\Image\\DxBall.jpg");
	helpImage.load("Data\\Image\\help.png");
	hsImage.load("Data\\Image\\highscore.png");
	lifeImage.load("Data\\Image\\heart.png");
	bulletImage.load("Data\\Image\\bullet.png");
	levelUpImage.load("Data\\Image\\LevelUp.png");
	gameOverImage.load("Data\\Image\\GameOver.png");
	nameEntryActiveImage.load("Data\\Image\\NameEntryActive1.png");
	nameEntryDeactiveImage.load("Data\\Image\\NameEntryDeactive1.png");
	winImage.load("Data\\Image\\Win.png");
	for (int i = 1;i < 7;i++)
	{
		buttonImage[i].load(button[i]);
	}
}
GLint MenuManager::getMenu()
{
	return menuName;
}
GLint MenuManager::getOption()
{
	return menuOption;
}
void MenuManager::setMenu(menus n)
{
	menuName = n;
	if(n==MAIN) GameManager::set();
}
void MenuManager::setOption(option n)
{
	menuOption = n;
}
void MenuManager::draw()
{
	dxImage.render(x, y);
	buttonImage[menuOption].render(x, y);
}

void iDrawRemaining()
{
	//DrawManager::setColor(188, 3, 57);
	DrawManager::setColor(0, 255, 0);
	TextManager::render(20,20, "REMAINING - ",.7);
	char temp[5];
	TextManager::render(20+ 160,20, _itoa(bricks.getRemaining(), temp, 10),.7);
}
void iDrawLevel()
{
	//DrawManager::setColor(188, 3, 57);
	DrawManager::setColor(0, 255, 0);
	TextManager::render(20,120, "LEVEL - ",.7);
	char temp[3];
	TextManager::render(20 + 95  ,120, _itoa(LevelManager::getLevel(), temp, 10),.7);
}
void iDrawTime()
{
	char Temp[50];
	//DrawManager::setColor(188, 3, 57);
	DrawManager::setColor(0,255,0);
	sprintf(Temp, "%02d",int((GameManager::getTime() / 70) / 3600));
	TextManager::render(20,70, Temp ,.7);
	TextManager::render(20+35,70+2, ":",.7);
	sprintf(Temp, "%02d", int(fmod((GameManager::getTime() / 70) / 60, 60)));
	TextManager::render(20+45,70, Temp,.7);
	TextManager::render(20+80,70+2, ":",.7);
	sprintf(Temp, "%02d",int(fmod((GameManager::getTime() / 70) , 60)));
	TextManager::render(20+90,70, Temp,.7);
}

extern GLfloat deathOpacity;
void MenuManager::drawGame()
{
	field.draw();
	paddle.draw();
	
	if (getMenu() == MenuManager::GAME)balls.draw();
	bricks.draw();
	
	//wall.draw();
	wallImage.render(0, 0);
	wallImage.render(field.getX() + field.getWidth(), 0);
	bullets.draw();
	for (int i = 0; i < GameManager::getLife() ; i++)
	{
		lifeImage.render(WindowManager::getWidth() - 90 - (i % 3) * 80, WindowManager::getHeight() - 100 - 100 * ((i / 3)));
	}

	
	powerUps.draw();
	DrawManager::setColor(255, 255, 0);
	iDrawSmallScore(ScoreManager::getScore(), 3, 220,1000);

	iDrawLevel();
	iDrawRemaining();
	if (GameManager::isPaused())
	{
		DrawManager::setColor(255, 255, 0);
		TextManager::render(20, 64, "PAUSED" );
	}
	else
	{
		iDrawTime();
	}

	if (paddle.isShootingPaddle())
	{
		bulletImage.render(WindowManager::getWidth()-120,20);
		DrawManager::setColor(255, 255, 0);
		iDrawSmallScore(paddle.getBullets(), 3, WindowManager::getWidth() -170,35);
	}

	if (getMenu() == MenuManager::DEATH)
	{
		DrawManager::setColor(BLACK, deathOpacity);
		DrawManager::filledRectangle(0, 0, WindowManager::getWidth(), WindowManager::getHeight());
	}
}

void MenuManager::drawHelp()
{
	helpImage.render(WindowManager::getWidth() / 2 - 939, WindowManager::getHeight() / 2 - 360);
}
void MenuManager::drawMainMenu()
{

}

void MenuManager::drawLevelUp()
{
	levelUpImage.render(460, WindowManager::getHeight() / 2 - 504);
}
void MenuManager::drawHighScore()
{
	score.drawBoard();
}

void MenuManager::menuSelection(GLint mx, GLint my)
{
	for (int i = 1;i < 7;i++)
	{
		for (int j = 0;j < buttonBound[i][0][0];j++)
		{
			if (mx >= (x + buttonBound[i][1][j]) && mx <= (x + buttonBound[i][3][j]) && my >= (y + buttonBound[i][2][j]) && my <= (y + buttonBound[i][4][j]))
			{
				if (menuOption != (MenuManager::option)i) AudioManager::play(AudioManager::MOUSE_HOVER);
				menuOption = (MenuManager::option)i;
				return;
			}
		}
	}
	menuOption = MenuManager::NONE;
}

void MenuManager::drawQuit()
{
	if (quit)
	{
		Sleep(1000);
		exit(0);
	}
	TextureManager::render(460, 43, "Data\\Image\\GoodBye.png");
	quit = true;
}

void MenuManager::drawCustom()
{
	int i, j;
	customImage.render(134,0);
	if (play == 1) TextureManager::render(134, 0, "Data\\Image\\PlayButton.png");
	if (left == 1) TextureManager::render(134, 0, "Data\\Image\\Left.png");
	if (right == 1) TextureManager::render(134, 0, "Data\\Image\\Right.png");
	for (i = 0; i < bricks.getRows(); i++)
	{
		for (j = 0; j < bricks.getCols(); j++)
		{
			int R = (LevelManager::getLevel() % 3 == 1 ? i * i : LevelManager::getLevel() % 3 == 2 ? i * i : i * j); //i*i
			int G = (LevelManager::getLevel() % 3 == 1 ? i * j : LevelManager::getLevel() % 3 == 2 ? i * i : j * j); //i*j
			int B = (LevelManager::getLevel() % 3 == 1 ? j * j : LevelManager::getLevel() % 3 == 2 ? i * i : j * i); //j*j*/

			if (bricks.getCell(i, j).getStrength() == NORMAL)
			{
				bricks.getCell(i, j).setColor(18 + R / 1.5, 18 + G / 1.5, 18 + B / 1.5);
				Brick::drawNormal(bricks.getCell(i, j).getX()+board.getX(), bricks.getCell(i, j).getY() + board.getY()-170, 18 + R / 1.5, 18 + G / 1.5, 18 + B / 1.5);
			}
			else if (bricks.getCell(i, j).getStrength() == EXPLOSIVE)
			{
				Brick::drawExplosive(bricks.getCell(i, j).getX() + board.getX(), bricks.getCell(i, j).getY() + board.getY() - 170);
			}
				
			else if (bricks.getCell(i, j).getStrength() == MULTIHIT)
				Brick::drawMultiHit(bricks.getCell(i, j).getX() + board.getX(), bricks.getCell(i, j).getY() + board.getY() - 170);

			DrawManager::setColor(GREY);
			DrawManager::rectangle(board.getX() + bricks.getCell(i, j).getX(),
				board.getY() + bricks.getCell(i, j).getY() - 170,
				bricks.getWidth(),
			bricks.getHeight());
		}
		//cout << endl;
	}


	//iDrawBack();

	DrawManager::setColor(166, 41, 166);
	TextManager::render(260, 40, "Left click and Drag - " ,.5);
	TextManager::render(260, 10, "Left click on a normal block - " ,.5);
	TextManager::render(1460, 40, "- Right click and Drag" ,.5);
	TextManager::render(1375, 10, "- Right click on an empty block" ,.5);

	DrawManager::setColor(146, 62, 241);
	TextManager::render(450, 40, "Draw a normal block" ,.5);
	TextManager::render(535, 10, "Draw an explosive" ,.5);
	TextManager::render(1350, 40, "Erase block" ,.5);
	TextManager::render(1255, 10, "Draw a brick" ,.5);

	iDrawSmallScore(bricks.getRemaining(), 3, 100,1000);
}

void MenuManager::drawBack()
{
	if (back) TextureManager::render(30,20, "Data\\Image\\BackButton.bmp");
	else TextureManager::render(30,20, "Data\\Image\\BackButtonDark.bmp");
}

void MenuManager::drawNameEntry()
{
	if (LevelManager::getLevel() < LevelManager::getTotalLevels())
	{
		gameOverImage.render(460, 100);
		DrawManager::setColor(188, 57, 133);
	}
	else
	{
		winImage.render(600,100);
		DrawManager::setColor(188, 3, 57);
	}
	iDrawScore(ScoreManager::getScore(), 10, 920, 920);
	if (nameEntry)nameEntryActiveImage.render(460, 0);

	DrawManager::setColor(200, 200, 200);
	TextManager::render(460+310,160,ScoreManager::getName(),.6);
}
void MenuManager::drawGameOver()
{
	gameOverImage.render(460, 100);
	if (LevelManager::getLevel() > 0)
	{
		if (nameEntry)nameEntryActiveImage.render(460, 0);
		else nameEntryDeactiveImage.render(460, 0);
		DrawManager::setColor(100, 100, 100);
		TextManager::render(460 + 400, 160, "ENTER YOUR NAME",.6);
	}	
	DrawManager::setColor(188, 57, 133);
	iDrawScore(ScoreManager::getScore(), 10, 920, 920);
}

void MenuManager::drawWin()
{
	winImage.render(600, 100);
	if (LevelManager::getLevel() > 0)
	{
		if (nameEntry)nameEntryActiveImage.render(460, 0);
		else nameEntryDeactiveImage.render(460, 0);
		DrawManager::setColor(100, 100, 100);
		TextManager::render(460 + 400, 160, "ENTER YOUR NAME" );
	}
	DrawManager::setColor(188, 3, 57);
	iDrawScore(ScoreManager::getScore(), 10, 920, 920);
}