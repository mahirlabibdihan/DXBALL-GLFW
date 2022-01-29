/*
 ______   _________ _      _       _
|  ____ \|___   ___| |    | |     | |
| |    \ \   | |   | |____| |     | |
| |    | |   | |   |  ____  |     | |
| |____/ /___| |___| |    | |_____| |
|_______/|_________|_|    |_________|
M A H I R     L A B I B     D I H A N

*/

/*------------------------------------------------------------------------------ D getX()    B A L L ----------------------------------------------------------------------------- */

#include "Dxball.h"
Block Blocks[TotalR][TotalC];
BALL Ball;
GAMESTATE GameState;

stack<pair<int, int>> bombs;
void iBombExplode()
{
	if (!bombs.empty())
	{
		if (Blocks[bombs.top().first][bombs.top().second].Strength)
		{
			GameManager::Remaining--;
			GameManager::Score += 10;
			Blocks[bombs.top().first][bombs.top().second].Strength = 0;
		}

		bombs.pop();
	}
}

/*--------------------------------------------------------------------------------- L O G I C ---------------------------------------------------------------------------------*/

int Collide = 0;
int MODE = Menu.Mode , ADMIN = 0 ;
int level = 10;



void iDeath()
{

	Ball.getX() = Board.getX() + Board.Width / 2, Ball.getY() = Board.getY() + Board.Height + Ball.Radius + Ball_Board, Ball.dirX = 0, Ball.dirY = 0;
	GameManager::Launch = 0;

	if (GameManager::Life == 1)
	{
		if (GameManager::Level == 0)
		{
			Custom.GameOver = 1;
		}
		else
		{
			MODE = GameOver.Mode;
		}
	}
	else
	{
		iSaveState();
	}
	GameManager::Life--;

	Board.Width = Board.WIDTH;
	Board.Grab = 0;
	Board.Gun = 0;
	Ball.SpeedX = Ball.SPEEDX;
	Ball.SpeedY = Ball.SPEEDY;
	Ball.dirX = 0;
	Ball.dirY = 0;
	Ball.Fire = 0;
	Ball.Radius = Ball.RADIUS;
	sound.play(sound.GameOver);
	iResetBullet();
	iResetDropItems();
	Sleep(1000);
}

void iCatch()
{
	int i, j;
	for (i = 0; i <= Board.getY() + Board.Height; i++)
	{
		for (j = Board.getX() - 49; j < Board.getX() + Board.Width; j++)
		{
			if (j < 0) continue;
			if (DropItems.Table[i][j])
			{
				if (i == 0)
				{
					DropItems.Table[i][j] = 0;
					return ;
				}

				switch (DropItems.Table[i][j])
				{
				case Death_Mode:
					iDeath();
					DropItems.Table[i][j] = 0;
					break;
				case Gun_Mode:
					sound.play(sound.Reload);
					Board.Gun = 1;
					Board.Bullets += ReloadBullet;
					DropItems.Table[i][j] = 0;
					break;
				case Life_Mode:
					sound.play(sound.CatchItem);
					GameManager::Life++;
					DropItems.Table[i][j] = 0;
					break;
				case Extend_Mode:
					sound.play(sound.CatchItem);
					if (Board.WIDTH + Board.Extension <= ScreenWidth - 2 * WallManager.getX())
					{

						Board.Width += Board.Extension;
						if (Board.getX() - Board.Extension / 2 >= WallManager.getX())
						{
							glutWarpPointer(Mouse.getX() - Board.Extension / 2, ScreenHeight / 2);
							Board.getX() -= Board.Extension / 2;
							if (Board.getX() > WallManager.getX() + WallManager.Width - Board.Width)
							{
								glutWarpPointer(Mouse.getX() - Board.Extension / 2, ScreenHeight / 2);
								Board.getX() -= Board.Extension / 2;
							}
						}
					}
					DropItems.Table[i][j] = 0;
					break;
				case Shrink_Mode:
					sound.play(sound.CatchItem);
					if (Board.Width - Board.Compression >= Board.MinWidth)
					{
						glutWarpPointer(Mouse.getX() + Board.Compression / 2, ScreenHeight / 2);
						Board.getX() += Board.Compression / 2;
						Board.Width -= Board.Compression;
						if (!GameManager::Launch)
						{
							if (Ball.getX() < Board.getX()) Ball.getX() = Board.getX();
							else if (Ball.getX() > Board.getX() + Board.Width) Ball.getX() = Board.getX() + Board.Width;
						}
					}
					DropItems.Table[i][j] = 0;
					break;
				case Fast_Mode:
					sound.play(sound.CatchItem);
					if (abs(Ball.dirY) < 20)
					{
						Ball.dirY *= Ball.SpeedYUp;
						Ball.SpeedY *= Ball.SpeedYUp;
						Ball.dirX *=  Ball.SpeedXUp;
						Ball.SpeedX *= Ball.SpeedXUp;
					}
					DropItems.Table[i][j] = 0;
					break;
				case Slow_Mode:
					sound.play(sound.CatchItem);
					if (abs(Ball.dirY) > 0)
					{
						Ball.dirY *= Ball.SpeedYDown;
						Ball.SpeedY *= Ball.SpeedYDown;
						Ball.dirX *= Ball.SpeedXDown;
						Ball.SpeedX *= Ball.SpeedXDown;
					}
					DropItems.Table[i][j] = 0;
					break;
				case LevelUp_Mode:
					sound.play(sound.LevelUp);
					if (GameManager::Level < LevelUp.MAX && GameManager::Level > 0)
					{
						MODE = LevelUp.Mode;
					}
					else if (GameManager::Level == LevelUp.MAX) iLevelUp();
					else Custom.Win = 1;
					DropItems.Table[i][j] = 0;
					break;
				case Fall_Mode:
					sound.play(sound.CatchItem );
					if (WallManager.getY() > 2 * BlockHeight)
					{
						WallManager.getY() -= BlockHeight;
					}
					DropItems.Table[i][j] = 0;
					break;
				case Grab_Mode:
					sound.play(sound.CatchItem );
					Board.Grab = 1;
					DropItems.Table[i][j] = 0;
					break;
				case Fire_Mode:
					sound.play(sound.CatchItem );
					Ball.Fire = 1;
					DropItems.Table[i][j] = 0;
					break;
				case Big_Mode:
					sound.play(sound.CatchItem );
					if (Ball.Radius == Ball.RADIUS)
					{
						Ball.Radius = Ball.RADIUS * 1.5;
						Ball.dirY *= 1.2;
						Ball.SpeedY *= 1.2;
						Ball.dirX *= 1.2;
						Ball.SpeedX *= 1.2;
						if (!GameManager::Launch)
						{
							Ball.getY() = Board.getY() + Board.Height + Ball_Board + Ball.Radius;

						}
					}

					DropItems.Table[i][j] = 0;
					break;
				case Small_Mode:
					sound.play(sound.CatchItem );
					if (Ball.Radius == Ball.RADIUS)
					{
						Ball.Radius = Ball.RADIUS * 0.6;
						Ball.dirY *= .8;
						Ball.SpeedY *= .8;
						Ball.dirX *= .8;
						Ball.SpeedX *= .8;
						if (!GameManager::Launch)
						{
							Ball.getY() = Board.getY() + Board.Height + Ball_Board + Ball.Radius;
						}
					}

					DropItems.Table[i][j] = 0;
					break;
				case SuperShrink_Mode:
					sound.play(sound.CatchItem );
					glutWarpPointer(Mouse.getX() + (Board.Width - Board.MinWidth) / 2, ScreenHeight / 2);
					Board.getX() += (Board.Width - Board.MinWidth) / 2;
					Board.Width = Board.MinWidth;
					if (!GameManager::Launch)
					{
						if (Ball.getX() < Board.getX()) Ball.getX() = Board.getX();
						else if (Ball.getX() > Board.getX() + Board.Width) Ball.getX() = Board.getX() + Board.Width;
					}
					DropItems.Table[i][j] = 0;
					break;
				case Explode_Mode:

				{
					int i, j;
					for (i = 0; i < TotalC; i++)
					{
						for (j = 0; j < TotalR; j++)
						{
							if (Blocks[i][j].Strength == 2) iRemoveBlock( i , j );
						}
					}
				}

				DropItems.Table[i][j] = 0;
				break;
				}
			}
		}
	}
}

void iDirection()
{
	if (Ball.getX() >= Board.getX() && Ball.getX() <= Board.getX() + Board.Width)
	{
		if (Board.Grab)Ball.getY() = Board.getY() + Board.Height + Ball.Radius + Ball_Board;
		sound.play(sound.BallXBoard  );
		if (Ball.getX() != Board.getX() + Board.Width / 2)
		{
			Ball.dirX = ceil((Ball.getX() - Board.getX() - Board.Width / 2) * Ball.SpeedX * max(min(12, Ball.Radius), 8) / Board.Width);
		}
		while (!Ball.dirX)
		{
			Ball.dirX = (rand() % 15) - 7;
		}
		Ball.dirY = abs(Ball.dirY);
		if (!Ball.dirY) Ball.dirY = 2 * Ball.SpeedY;
		if (GameManager::Launch && Board.Grab)
		{
			GameManager::Launch = 0;
			Ball.getY() = Board.getY() + Board.Height + Ball.Radius + Ball_Board;
		}
		else
		{
			GameManager::Launch = 1;
		}
	}
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/




















