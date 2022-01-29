/*------------------------------------------------------------------------------ K E getY() B O A R D -------------------------------------------------------------------------------*/
#include "Headers.h"
#include "Externs.h"

void KeyboardManager::keyHandler(GLFWwindow* window, int key, int scancode, int action, int mods)	  // Callback When normal key is pressed down
{
	keyboard(key);
	//glutPostRedisplay();
}
void KeyboardManager::specialKeyHandler(GLint key, GLint x, GLint y)	// Callback when special key is pressed down
{
	specialKeyboard(key);
	//glutPostRedisplay();
}
void KeyboardManager::keyboard(int key)
{
	//if (key == 'q') exit(1);
	//if (key == '\b') menu.setMenu(MenuManager::MAIN);
	if (menu.getMenu()==MenuManager::NAME_ENTRY)
	{
		ScoreManager::nameEntry(key);
	}

	/*else if (key == 'q')
	{
		if (MODE == Game.Mode)
		{
			if (!Custom.Win && !Custom.GameOver)
				iSaveState();
		}
		MODE = Quit.Mode;
	}

	else if (key == '\r')
	{
		if (MODE == GameOver.Mode)
		{
			MODE == Menu.Mode;
		}

		else if (MODE == Custom.Mode)
		{
			if (ADMIN)
			{
				int i, j;
				FILE *save = fopen(LevelUp.Level[Custom.Level], "w");
				for (i = TotalC - 1; i > -1; i--)
				{
					for (j = 0; j < TotalR; j++)
					{
						fprintf(save, "%d ", bricks.getCell(i,j).Strength );
					}
					fprintf(save, "\n") ;
				}
				fclose(save);
				level++;
			}

			else
			{
				MODE = Game.Mode;
				GameManager::Time = 0;
				Custom.Play = 0;
				paddle.getX() = paddle.LastX = Mouse.getX() - paddle.getWidth() / 2;
				balls.getX() = paddle.getX() + paddle.getWidth() / 2, balls.getY() = paddle.getY() + paddle.getHeight() + balls.Radius + Ball_Board;
				AudioManager::play(AudioManager::MOUSE_CLICK  );
			}
		}
	}

	else if (key == '\b' || key == 27)
	{
		if (MODE)
		{
			if (MODE == Game.Mode)
			{
				if (!Custom.Win && !Custom.GameOver)
					iSaveState();
			}
			iReset();
			MODE = Menu.Mode;
		}
	}

	else if (key == 'p')
	{
		GameManager::Pause = !GameManager::Pause;
		glutWarpPointer(paddle.getX(), ScreenHeight - Mouse.getY());
	}

	else if (key == ' ')
	{
		if (MODE == Game.Mode)
		{
			if (!GameManager::Launch)
			{
				iDirection();
			}
			else if (GameManager::Pause)
			{
				GameManager::Pause = 0;
				glutWarpPointer(paddle.getX(), ScreenHeight - Mouse.getY());
			}
			else if (paddle.Gun)
			{
				if (paddle.Bullets > 0)
				{
					AudioManager::play(AudioManager::music[AudioManager::SHOOT]  );
					Bullet.Table[paddle.getY() + paddle.getHeight()][paddle.getX() + 4] = 1;
					Bullet.Table[paddle.getY() + paddle.getHeight()][paddle.getX() + paddle.getWidth() - 4] = 1;
					paddle.Bullets--;
					if (paddle.Bullets == 0) paddle.Gun = 0;
				}
			}
		}
	}*/
}
void KeyboardManager::specialKeyboard(unsigned char key)
{
	/*if (Custom.GameOver || Custom.Win)
	{
		MODE = Menu.Mode;
		Custom.GameOver = 0;
		Custom.Win = 0;
	}
	if (MODE == Game.Mode)
	{
		if (key == GLUT_KEY_END) {
			MODE = Quit.Mode;

		}
		else if (key == GLUT_KEY_RIGHT)
		{
			if (paddle.getX() +  paddle.SpeedX <= WallManager.getX() + WallManager.getWidth() - paddle.getWidth())
			{
				paddle.getX() += paddle.SpeedX;
				if (!GameManager::Launch)
				{
					balls.getX() += paddle.SpeedX;
				}
			}

			else
			{
				if (!GameManager::Launch)
				{
					balls.getX() += (WallManager.getX() + WallManager.getWidth() - paddle.getWidth() - paddle.getX());
				}
				paddle.getX() = WallManager.getX() + WallManager.getWidth() - paddle.getWidth();
			}
		}
		else if (key == GLUT_KEY_LEFT)
		{
			if (paddle.getX() - paddle.SpeedX >= WallManager.getX())
			{
				paddle.getX() -= paddle.SpeedX;
				if (!GameManager::Launch)
				{
					balls.getX() -= paddle.SpeedX;
				}
			}
			else
			{
				if (!GameManager::Launch)
				{
					balls.getX() -= (paddle.getX() - WallManager.getX());
				}

				paddle.getX() = WallManager.getX();
			}
		}
	}

	else if (MODE == Custom.Mode)
	{
		if (key == GLUT_KEY_RIGHT)
		{
			if (Custom.Level < LevelUp.MAX)
			{
				AudioManager::play(AudioManager::MOUSE_CLICK  );
				Custom.Level++;
				iSetCustom();
			}
		}
		else if (key == GLUT_KEY_LEFT)
		{

			if (Custom.Level > 0)
			{
				AudioManager::play(AudioManager::MOUSE_CLICK  );
				Custom.Level--;
				iSetCustom();
			}
		}
	}*/
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
