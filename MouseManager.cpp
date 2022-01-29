/*--------------------------------------------------------------------------------- M O U S E ----------------------------------------------------------------------------------*/
#include "Headers.h"
#include "Externs.h"

int MouseManager::button;
GLfloat MouseManager::angle;
GLfloat MouseManager::x;
GLfloat MouseManager::y;

MouseManager::MouseManager()
{
	button = -1;
}

GLfloat MouseManager::getX()
{
	return x;
}
GLfloat MouseManager::getY()
{
	return y;
}
void MouseManager::setXY(GLfloat x, GLfloat y)
{
	glfwSetCursorPos(window,x,WindowManager::getHeight()-y);
}
void MouseManager::setX(GLfloat x)
{
	glfwSetCursorPos(window, x, WindowManager::getHeight()-y);
}
void MouseManager::setY(GLfloat y)
{
	glfwSetCursorPos(window, x, WindowManager::getHeight()-y);
}

int MouseManager::getButton()
{
	return button;
}

void MouseManager::setButton(int button)
{
	MouseManager::button = button;
}

GLfloat MouseManager::getDir()
{
	return angle;
}
void MouseManager::setDir(GLfloat mx, GLfloat my)
{
	/*GLfloat dx = mx - x, dy = my - y;
	GLfloat dir = atan(dy / dx);
	if (dx >= 0 && dy >= 0)
	{
		angle = dir;
	}
	else if (dx >= 0 && dy < 0)
	{
		angle = 2*PI + dir;
	}
	else if (dx < 0 && dy >= 0)
	{
		angle = PI + dir;
	}
	else if (dx < 0 && dy < 0)
	{
		angle = PI + dir;
	}*/
}
void MouseManager::scroll(int dir)
{

}
void MouseManager::drag(int mx, int my)
{
	if (menu.getMenu() == MenuManager::CUSTOM_GAME)
	{
		int i, j;
		for (i = 0; i < bricks.getRows(); i++)
		{
			for (j = 0; j < bricks.getCols(); j++)
			{
				if (mx >= board.getX() + bricks.getCell(i, j).getX() && mx <= board.getX() + bricks.getCell(i, j).getX() + bricks.getWidth())
				{
					if (my >= board.getY() + bricks.getCell(i, j).getY() - 170 && my <= board.getY() + bricks.getCell(i, j).getY() - 170 + bricks.getHeight())
					{
						if (!bricks.getCell(i, j).getStrength() && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
						{
							bricks.getCell(i, j).setStrength(1);
							bricks.setRemaining(bricks.getRemaining()+1);
						}
						else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && bricks.getCell(i, j).getStrength())
						{
							bricks.getCell(i, j).setStrength(0);
							bricks.setRemaining(bricks.getRemaining()-1);
						}
					}
				}
			}
		}
	}
}
void iMouseLeftButtonDownMenu(int mx, int my)
{
	if (menu.getOption() == MenuManager::NEWGAME)
	{
		menu.setMenu(MenuManager::GAME);
		//glutPostRedisplay();
		AudioManager::play(AudioManager::MOUSE_CLICK);
		LevelManager::setLevel(1);
		bricks.set();
		MouseManager::setX(paddle.getX());
		AudioManager::play(AudioManager::BACKGROUND, true);
		menu.setOption(MenuManager::NONE);
	}
	else if (menu.getOption() == MenuManager::CUSTOM)
	{
		AudioManager::play(AudioManager::MOUSE_CLICK);
		GameManager::init();
		board.setX(field.getX());
		menu.setMenu(MenuManager::CUSTOM_GAME);
		menu.setOption(MenuManager::NONE);
		AudioManager::play(AudioManager::BACKGROUND, true);
	}
	else if (menu.getOption() == MenuManager::RESUME)
	{
		AudioManager::play(AudioManager::MOUSE_CLICK);
		GameManager::init();
		GameManager::load();
		particles.reset();
		menu.setMenu(MenuManager::GAME);
		menu.setOption(MenuManager::NONE);
		AudioManager::play(AudioManager::BACKGROUND, true);
	}
	else if (menu.getOption() == MenuManager::HIGHSCORE)
	{
		AudioManager::play(AudioManager::MOUSE_CLICK);
		menu.setMenu(MenuManager::HIGH_SCORE);
		menu.setOption(MenuManager::NONE);
	}
	else if (menu.getOption() == MenuManager::HELP)
	{
		AudioManager::play(AudioManager::MOUSE_CLICK);
		menu.setMenu(MenuManager::HELP_PAGE);
		menu.setOption(MenuManager::NONE);
	}
	else if (menu.getOption() == MenuManager::QUIT)
	{
		AudioManager::play(AudioManager::MOUSE_CLICK);
		menu.setMenu(MenuManager::QUIT_GAME);
		menu.setOption(MenuManager::NONE);
	}
}
void iCustomPlay()
{

}
void iMouseLeftButtonDownCustom(int mx, int my)
{
	if (menu.play)
	{
		//iCustomPlay();
		if (bricks.getRemaining())
		{
			menu.setMenu(MenuManager::GAME);
			paddle.init();
			balls.init();
			paddle.set();
			balls.set();
			LevelManager::setLevel(0);
			AudioManager::play("Data\\Music\\Background.mp3", true);
		}
		menu.play = false;
	}
	else if (menu.left)
	{
		if (LevelManager::levelDown())
		{
			AudioManager::play(AudioManager::MOUSE_CLICK);
			GameManager::set();
			board.setX(field.getX());
		}
		menu.left = false;
	}
	else if (menu.right)
	{
		if (LevelManager::levelUp())
		{
			AudioManager::play(AudioManager::MOUSE_CLICK);
			GameManager::set();
			board.setX(field.getX());
		}
		menu.right = 0;
	}
	else
	{
		int i, j;
		for (i = 0; i < bricks.getRows(); i++)
		{
			for (j = 0; j < bricks.getCols(); j++)
			{
				if (mx >= board.getX() + bricks.getCell(i, j).getX() && mx <= board.getX() + bricks.getCell(i, j).getX() + bricks.getWidth())
				{
					if (my >= board.getY() + bricks.getCell(i, j).getY() - 170 && my <= board.getY() + bricks.getCell(i, j).getY() - 170 + bricks.getHeight())
					{
						if (bricks.getCell(i, j).getStrength() == 1)
						{
							bricks.getCell(i, j).setStrength(2);
							return;
						}
						else if (bricks.getCell(i, j).getStrength() == 0)
						{
							bricks.setRemaining(bricks.getRemaining()+1);
							bricks.getCell(i, j).setStrength(1);
							return;
						}
						else if (bricks.getCell(i, j).getStrength() == -1)
						{
							bricks.setRemaining(bricks.getRemaining()-1);
							bricks.getCell(i, j).setStrength(1);
							return;
						}
					}
				}
			}
		}
	}
}
void iMouseLeftButtonDown(int mx, int my)
{
	//MouseManager::setButton(GLUT_LEFT_BUTTON);
	if (menu.getMenu() == MenuManager::GAME_OVER || menu.getMenu() == MenuManager::WINNER)
	{
		if (menu.nameEntry)
		{
			menu.setMenu(MenuManager::NAME_ENTRY);
		}
	}
	else if (menu.getMenu() == MenuManager::CUSTOM_GAME)
	{
		iMouseLeftButtonDownCustom(mx, my);
	}
	else if (menu.getMenu() == MenuManager::GAME)
	{
		if (GameManager::isPaused())
		{
			GameManager::resumeGame();
			MouseManager::setX(paddle.getX());
		}
		else if (balls.isOnPaddle())
		{
			for (int i = 0;i < balls.getTotal();i++)
			{
				if (balls.getCell(i).isOnPaddle())
				{
					CollisionManager::ballXpaddle(i);
				}			
			}
		}
		else if (paddle.isShootingPaddle())
		{
			paddle.shoot();
		}
	}

	else if (menu.getMenu() == MenuManager::MAIN)
	{
		iMouseLeftButtonDownMenu(mx, my);
	}

	if (menu.back)
	{
		AudioManager::play(AudioManager::MOUSE_CLICK);
		menu.setMenu(MenuManager::MAIN);
		GameManager::init();
		menu.back = 0;
	}
}
void iMouseRightButtonDown(int mx, int my)
{
	int i, j;
	if (menu.getMenu() == MenuManager::CUSTOM_GAME)
	{
		//MouseManager::setButton(GLUT_RIGHT_BUTTON);
		for (i = 0; i < bricks.getRows(); i++)
		{
			for (j = 0; j < bricks.getCols(); j++)
			{
				if (mx >= board.getX() + bricks.getCell(i, j).getX() && mx <= board.getX() + bricks.getCell(i, j).getX() + bricks.getWidth())
				{
					if (my >= board.getY() + bricks.getCell(i, j).getY() - 170 && my <= board.getY() + bricks.getCell(i, j).getY() - 170 + bricks.getHeight())
					{
						if (abs(bricks.getCell(i, j).getStrength()) == 1) { bricks.getCell(i, j).setStrength(0); bricks.setRemaining(bricks.getRemaining()-1); }
						else if (bricks.getCell(i, j).getStrength() == 2) { bricks.getCell(i, j).setStrength(0); bricks.setRemaining(bricks.getRemaining()-1); }
						else { bricks.getCell(i, j).setStrength(-1); bricks.setRemaining(bricks.getRemaining()+1); }
					}
				}
			}
		}
	}

	else if (menu.getMenu() == MenuManager::GAME)
	{
		if (!GameManager::isPaused()) GameManager::pauseGame();
		else
		{
			GameManager::save();
			menu.setMenu(MenuManager::MAIN);
			AudioManager::stopAll();
			GameManager::init();
			GameManager::reset();
		}
	}
}
void MouseManager::click(int button, int action, int mx, int my)
{
	if (action == GLFW_PRESS && (LevelManager::getLevel() == 0 && (menu.getMenu() == MenuManager::GAME_OVER || menu.getMenu() == MenuManager::WINNER)))
	{
		menu.setMenu(MenuManager::MAIN);
		GameManager::reset();
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		iMouseLeftButtonDown(mx, my);
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		iMouseRightButtonDown(mx, my);
	}
}
void MouseManager::move(int mx, int my)
{
	if (menu.getMenu() == MenuManager::GAME || menu.getMenu() == MenuManager::LEVEL_UP)
	{
		if (mx < field.getX() + paddle.getWidth() / 2)
		{
			MouseManager::setXY(field.getX() + paddle.getWidth() / 2, WindowManager::getHeight() / 2);
			mx = field.getX() + paddle.getWidth() / 2;
		}
		else if (mx > field.getX() + field.getWidth() - paddle.getWidth() / 2)
		{
			MouseManager::setXY(field.getX() + field.getWidth() - paddle.getWidth() / 2, WindowManager::getHeight() / 2);
			mx = field.getX() + field.getWidth() - paddle.getWidth() / 2;
		}
	}
	if (menu.getMenu() == MenuManager::GAME)
	{
		if (GameManager::isPaused()) return;
		for (int i = 0;i < balls.getTotal();i++)
		{
			if (balls.getCell(i).isOnPaddle()) balls.getCell(i).move(mx);
		}
		
		paddle.move(mx);
	}

	else if (menu.getMenu() == MenuManager::GAME_OVER || menu.getMenu() == MenuManager::WINNER)
	{
		if (mx >= 460 + 280 && mx <= 460 + 710 && my >= 130 && my <= 130 + 90)
		{
			menu.nameEntry = true;
		}
		else
		{
			menu.nameEntry = false;
		}
	}

	else if (menu.getMenu() == MenuManager::CUSTOM_GAME)
	{
		if (mx >= 880 && mx <= 1050 && my >= 820 && my <= 1020)
		{
			if (!menu.play)AudioManager::play(AudioManager::MOUSE_HOVER);
			menu.play = true;
		}
		else
		{
			menu.play = false;
		}

		if (mx >= 590 && mx <= 780 && my >= 870 && my <= 970)
		{
			if (!menu.left)AudioManager::play(AudioManager::MOUSE_HOVER);
			menu.left = true;
		}
		else
		{
			menu.left = false;
		}
		if (mx >= 1140 && mx <= 1330 && my >= 870 && my <= 970)
		{
			if (!menu.right)AudioManager::play(AudioManager::MOUSE_HOVER);
			menu.right = true;
		}
		else
		{
			menu.right = false;
		}
	}

	else if (menu.getMenu() == MenuManager::MAIN)
	{
		menu.menuSelection(mx, my);
	}

	if (menu.getMenu() == MenuManager::HELP_PAGE
		|| menu.getMenu() == MenuManager::HIGH_SCORE
		|| menu.getMenu() == MenuManager::NAME_ENTRY
		|| menu.getMenu() == MenuManager::CUSTOM_GAME
		|| LevelManager::getLevel()
		&& (menu.getMenu() == MenuManager::WINNER
			|| menu.getMenu() == MenuManager::GAME_OVER)
		)
	{
		struct
		{
			int X = 30, Y = 20, Height = 100, Width = 148, Active = 0;

		} Back;
		if ((mx >= Back.X && mx <= Back.X + Back.Width / 2 && my >= Back.Y && my <= Back.Y + Back.Height) || (mx >= Back.X + Back.Width / 2 && mx <= Back.X + Back.Width && my >= Back.Y + Back.Height / 2 - 10 && my <= Back.Y + Back.Height / 2 + 10))
		{
			if (!menu.back)AudioManager::play(AudioManager::MOUSE_HOVER);
			menu.back = true;
		}
		else
		{
			menu.back = false;
		}
	}
}

void MouseManager::dragHandler(int mx, int my)
{
	x = mx;
	y = WindowManager::getHeight() - my;
	drag(x, y);
	glFlush();
}

void MouseManager::moveHandler(GLFWwindow* window, double mx, double my)
{
	setDir(mx, WindowManager::getHeight() - my);
	x = mx;
	y = WindowManager::getHeight() - my;
	dragHandler(mx, my);
	move(x, y);
	glFlush();
}

void MouseManager::clickHandler(GLFWwindow* window, int button, int action, int mods)
{
	//x = mx;
	//y = WindowManager::getHeight() - my;
	click(button, action , x, y);
	glFlush();
}
void MouseManager::scrollHandler(int button, int dir, int x, int y)
{
	scroll(dir);
}
/*------------------------------------ M E N U -----------------------------------*/

/*--------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/



