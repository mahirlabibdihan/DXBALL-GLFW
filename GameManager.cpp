#include "Headers.h"
#include "Externs.h"

GLfloat GameManager::timer;
int GameManager::life;
bool GameManager::pause;


extern int timeDeath;
GameManager::GameManager()
{
	timer = 0;
	life = 2;
}
void GameManager::init()
{
	srand(time(NULL));
	pause = false;
	timer = 0;
	life = 2; 
	TextManager::init();
	TextureManager::init();
	LevelManager::init();
	ScoreManager::init();
	particles.init();
	paddle.init();
	balls.init();
	board.init();
	bullets.init();
	powerUps.init();
	menu.init();
	
}
void GameManager::set()
{
	if (menu.getMenu() == MenuManager::CUSTOM_GAME)
	{
		bullets.set();
		powerUps.set();
		bricks.set();
		field.set();
		board.set();
	}
	else
	{
		pause = false;
		bullets.set();
		powerUps.set();
		bricks.set();
		field.set();
		board.set();
		paddle.set();
		balls.set();
	}

}

void GameManager::reset()
{
	MouseManager::setX(WindowManager::getWidth() / 2);
	pause = false; 
	paddle.reset();
	balls.reset();
	powerUps.reset();
	bullets.reset();
	bricks.reset();
	particles.reset();
	// level.reset();
}

void GameManager::update()
{

}

void GameManager::incTimer()
{
	timer+=1;
}
void GameManager::incLife()
{
	life++;
}
void GameManager::drawTime()
{
	char temp[40];
	snprintf(temp, 40, "TIME :  %.0f", timer);
	DrawManager::setColor(RED);
	TextManager::render(WindowManager::getWidth() - 200.0f, WindowManager::getHeight() - 200.0f, temp);
}

GLfloat GameManager::getTime()
{
	return timer;
}

GLint GameManager::getLife()
{
	return life;
}
void GameManager::death()
{
	MouseManager::setXY(WindowManager::getWidth() / 2, WindowManager::getHeight() / 2);
	
	if (GameManager::life == 0)
	{
		{
			AudioManager::stopAll();
			menu.setMenu(MenuManager::GAME_OVER);
			return;
		}
	}
	else
	{
		life--;
	}
	
	AudioManager::play(AudioManager::GAME_OVER);
	menu.setMenu(MenuManager::DEATH);
	timeDeath = glfwGetTime();
}
void GameManager::save()
{
	ofstream out("Data\\LastState.txt",ios::out);
	out << pause<<" "<<timer << " " << life << endl;
	balls.save(out);
	paddle.save(out);
	board.save(out);
	field.save(out);
	LevelManager::save(out);
	ScoreManager::save(out);
	powerUps.save(out);
	particles.save(out);
	bullets.save(out);
	bricks.save(out);
	out.close();
}
void GameManager::load()
{
	ifstream in("Data\\LastState.txt", ios::in);
	in >> pause>> timer >> life;
	balls.load(in);
	paddle.load(in);
	board.load(in);
	field.load(in);
	LevelManager::load(in);
	ScoreManager::load(in);
	powerUps.load(in);
	particles.load(in);
	bullets.load(in);
	bricks.load(in);
	MouseManager::setX(paddle.getX());
	in.close();
}
void GameManager::pauseGame()
{
	pause = true;
}
void GameManager::resumeGame()
{
	pause = false;
}
bool GameManager::isPaused()
{
	return pause;
}