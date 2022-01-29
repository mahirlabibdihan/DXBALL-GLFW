#include "Headers.h"
#include "Externs.h"
 
extern int timeLevelUp;


bool CollisionManager::isBallXPaddle = false;
/*----------------------------------------------------------------------- B L O C K 	C O L L I S I O N ----------------------------------------------------------------------*/

void iDirection(int i)
{
	if (balls.getCell(i).getX() >= paddle.getX() - paddle.getWidth() / 2 && balls.getCell(i).getX() <= paddle.getX() + paddle.getWidth() / 2)
	{
		particles.add(balls.getCell(i).getX(), paddle.getY() + paddle.getHeight());
		particles.add(balls.getCell(i).getX(), paddle.getY() + paddle.getHeight());
		if (paddle.isGrabPaddle())
			balls.getCell(i).setY(paddle.getY() + paddle.getHeight() + balls.getCell(i).getRadius() + Ball_Board);

		AudioManager::play(AudioManager::BALL_X_PADDLE);
		
		if (balls.getCell(i).getX() == paddle.getX() && !balls.getCell(i).isOnPaddle()) balls.getCell(i).setAngle(2*PI-balls.getCell(i).getAngle());
		else if(balls.getCell(i).getX() != paddle.getX())balls.getCell(i).setAngle(atan(balls.getCell(i).getY() / (balls.getCell(i).getX() - paddle.getX())));

		if (balls.getCell(i).getAngle() < 0)
		{
			balls.getCell(i).setAngle(PI + balls.getCell(i).getAngle());
		}

		while (balls.getCell(i).getAngle() == 0)
		{
			balls.getCell(i).setAngle(fmod(rand(),PI/2)+.785);
		}

		
		if (!balls.getCell(i).isOnPaddle() && paddle.isGrabPaddle())
		{
			balls.getCell(i).stickToPaddle();
			balls.getCell(i).setY(paddle.getY() + paddle.getHeight() + balls.getCell(i).getRadius() + Ball_Board);
		}
		else
		{
			if (balls.getCell(i).isOnPaddle()) balls.getCell(i).launch();
		}

		CollisionManager::isBallXPaddle = true;
	}
}

void CollisionManager::bulletXbrick()
{
	for (int i = 0;i < bullets.getTotal();i++)
	{
		GLfloat x = bullets.getCell(i).getX(), y = bullets.getCell(i).getY();
		if (y >= board.getY() && y < board.getY() + board.getHeight())
		{
			if (bricks.getCell((y - board.getY()) / bricks.getHeight(), (x - board.getX()) / bricks.getWidth()).getStrength())
			{
				bricks.getCell((y - board.getY()) / bricks.getHeight(), (x - board.getX()) / bricks.getWidth()).setStrength(abs(bricks.getCell((y - board.getY()) / bricks.getHeight(), (x - board.getX()) / bricks.getWidth()).getStrength()));
				particles.add(x, y);
				particles.add(x, y);
				bullets.remove(i);
				if (balls.isFireBall()) bricks.getCell((y - board.getY()) / bricks.getHeight(), (x - board.getX()) / bricks.getWidth()).setStrength(EXPLOSIVE);
				bricks.remove((y - board.getY()) / bricks.getHeight(), (x - board.getX()) / bricks.getWidth(),0);
			}
		}
	}
}
void CollisionManager::ballXpaddle(GLint i)
{
	//for (int i = 0;i < balls.getTotal();i++)
	{
		if (balls.getCell(i).getDirY() < 0 & balls.getCell(i).getY() >= paddle.getY() + paddle.getHeight() / 2 - balls.getCell(i).getRadius() & balls.getCell(i).getY() <= paddle.getY() + paddle.getHeight() + balls.getCell(i).getRadius() + Ball_Board)
		{
			iDirection(i);
		}
		else if (balls.getCell(i).isOnPaddle())
		{
			iDirection(i);
		}
	}
	
}

void CollisionManager::paddleXpowerUp()
{
	{
		for (int i = 0;i < powerUps.getTotal();i++)
		{
			int x = powerUps.getCell(i).getX();
			int y = powerUps.getCell(i).getY();
			if (y > 0 && y <= paddle.getY() + paddle.getHeight() && x > paddle.getX() - paddle.getWidth()/2 - powerUps.getWidth() && x < paddle.getX() + paddle.getWidth()/2)
			{
				switch (powerUps.getCell(i).getType())
				{
				case PowerUpsManager::KillPaddle:
					for (int k = 0;k < balls.getTotal();k++)
					{
						particles.destroyBall(balls.getCell(k).getX(), balls.getCell(k).getY());
					}			
					powerUps.remove(i);
					GameManager::death();		
					break;
				case PowerUpsManager::ShootingPaddle:
					AudioManager::play(AudioManager::RELOAD);
					if (!paddle.isShootingPaddle())
					{
						paddle.toggleShootingPaddle();
					}
					paddle.addBullets(10);
					powerUps.remove(i);
					break;
				case PowerUpsManager::ExtraLife:
					AudioManager::play(AudioManager::CATCH_ITEMS);
					GameManager::incLife();
					powerUps.remove(i);
					break;
				case PowerUpsManager::ExpandPaddle:
					AudioManager::play(AudioManager::CATCH_ITEMS);
					paddle.extend();
					powerUps.remove(i);
					break;
				case PowerUpsManager::ShrinkPaddle:
					AudioManager::play(AudioManager::CATCH_ITEMS);
					paddle.shrink();
 					powerUps.remove(i);
					break;
				case PowerUpsManager::FastBall:
					AudioManager::play(AudioManager::CATCH_ITEMS);
					balls.speedUp();
					powerUps.remove(i);
					break;
				case PowerUpsManager::SlowBall:
					AudioManager::play(AudioManager::CATCH_ITEMS);
					balls.speedDown();
					powerUps.remove(i);
					break;
				case PowerUpsManager::LevelWrap:
					AudioManager::play(AudioManager::CATCH_ITEMS);
					if (!paddle.isGrabPaddle()) paddle.toggleGrabPaddle();
					bricks.levelWrap();
					powerUps.remove(i);
					break;
				case PowerUpsManager::FallingBricks:
					AudioManager::play(AudioManager::CATCH_ITEMS);
					board.fall();
					powerUps.remove(i);
					break;
				case PowerUpsManager::GrabPaddle:
					AudioManager::play(AudioManager::CATCH_ITEMS);
					if (!paddle.isGrabPaddle())
					{
						paddle.toggleGrabPaddle();
					}
					powerUps.remove(i);
					break;
				case PowerUpsManager::FireBall:
					AudioManager::play(AudioManager::CATCH_ITEMS);
					if (!balls.isFireBall())
					{
						balls.toggleFireBall();
					}
					powerUps.remove(i);
					break;
				case PowerUpsManager::ThruBall:
					AudioManager::play(AudioManager::CATCH_ITEMS);
					if (!balls.isThruBall())
					{
						balls.toggleThruBall();
					}
					powerUps.remove(i);
					break;
				case PowerUpsManager::MegaBall:
					AudioManager::play(AudioManager::CATCH_ITEMS);
					balls.extend();
					powerUps.remove(i);
					break;
				case PowerUpsManager::ShrinkBall:
					AudioManager::play(AudioManager::CATCH_ITEMS);
					balls.shrink();
					powerUps.remove(i);
					break;
				case PowerUpsManager::SplitBall:
					AudioManager::play(AudioManager::CATCH_ITEMS);
					int size;
					size =balls.getTotal();
					for (int j = 0;j <size ;j++)
					{
						balls.add(balls.getCell(j));
					}				
					powerUps.remove(i);
					break;
				case PowerUpsManager::EightBall:
					AudioManager::play(AudioManager::CATCH_ITEMS);
					size = balls.getTotal();
					for (int j = 0;j < size;j++)
					{
						for (int k = 0;k < 8;k++)
						{
							balls.add(balls.getCell(j));
						}		
					}
					powerUps.remove(i);
					break;
				case PowerUpsManager::SuperShrink:
					AudioManager::play(AudioManager::CATCH_ITEMS);
					paddle.superShrink();
					powerUps.remove(i);
					break;
				case PowerUpsManager::Explode:
					AudioManager::play(AudioManager::CATCH_ITEMS);
					bricks.explodeAll();
					powerUps.remove(i);
					break;
				case PowerUpsManager::ExpandExploding:
					AudioManager::play(AudioManager::CATCH_ITEMS);
					bricks.expandExploding();
					powerUps.remove(i);
					break;
				default:
					powerUps.remove(i);
					break;
				}
			}
		}
	}
}



int iLeftSideCollision(int i, int j, int k)
{
	if (balls.getCell(k).getX() > board.getX()+bricks.getCell(i, j).getX() - balls.getCell(k).getRadius() 
		&& balls.getCell(k).getX() <= board.getX()+bricks.getCell(i, j).getX() + max(balls.getCell(k).getRadius(), BALL_RADIUS) 
		&& balls.getCell(k).getDirX() > 0)
	{
		if (balls.isFireBall()) bricks.getCell(i, j).setStrength(EXPLOSIVE);
		bricks.remove(i, j,k);
		if (!balls.isThruBall())
		{
			if (balls.getCell(k).getDirX() > 0) balls.getCell(k).reverseX();
			balls.getCell(k).setX(board.getX() + bricks.getCell(i, j).getX() - balls.getCell(k).getRadius());
		}
		return 1;
	}
	return 0;
}

int iBottomSideCollision(int i, int j, int k)
{
	if (balls.getCell(k).getY() > board.getY()+bricks.getCell(i, j).getY() - balls.getCell(k).getRadius() 
		&& balls.getCell(k).getY() <= board.getY()+bricks.getCell(i, j).getY() + max(balls.getCell(k).getRadius(), BALL_RADIUS) 
		&& balls.getCell(k).getDirY() > 0)
	{
		if (balls.isFireBall()) bricks.getCell(i, j).setStrength(EXPLOSIVE);
		bricks.remove(i, j,k);
		if (!balls.isThruBall())
		{
			if (balls.getCell(k).getDirY() > 0) balls.getCell(k).reverseY();
			balls.getCell(k).setY(board.getY() + bricks.getCell(i, j).getY() - balls.getCell(k).getRadius());
		}
		return 1;
	}
	return 0;
}
int iTopSideCollision(int i, int j, int k)
{
	if (balls.getCell(k).getY() >= board.getY() + bricks.getCell(i, j).getY() + bricks.getHeight() - max(balls.getCell(k).getRadius(),BALL_RADIUS)
		&& balls.getCell(k).getY() < board.getY() + bricks.getCell(i, j).getY() + bricks.getHeight() + balls.getCell(k).getRadius()
		&& balls.getCell(k).getDirY() < 0)
	{
		if (balls.isFireBall()) bricks.getCell(i, j).setStrength(EXPLOSIVE);
		bricks.remove(i, j,k);
		if (!balls.isThruBall())
		{
			if (balls.getCell(k).getDirY() < 0) balls.getCell(k).reverseY();
			balls.getCell(k).setY(board.getY() + bricks.getCell(i, j).getY() + bricks.getHeight() + balls.getCell(k).getRadius());
		}
		return 1;
	}
	return 0;
}
int iRightSideCollision(int i, int j, int k)
{
	if (balls.getCell(k).getX() >= board.getX() + bricks.getCell(i, j).getX() + bricks.getWidth() - max(balls.getCell(k).getRadius(), BALL_RADIUS)
		&& balls.getCell(k).getX() < board.getX() + bricks.getCell(i, j).getX() + bricks.getWidth() + balls.getCell(k).getRadius()
		&& balls.getCell(k).getDirX() < 0)
	{
		if (balls.isFireBall()) bricks.getCell(i, j).setStrength(EXPLOSIVE);
		bricks.remove(i, j,k);
		if (!balls.isThruBall())
		{
			if (balls.getCell(k).getDirX() < 0) balls.getCell(k).reverseX();
			balls.getCell(k).setX(board.getX() + bricks.getCell(i, j).getX() + bricks.getWidth() + balls.getCell(k).getRadius());
		}
		return 1;
	}
	return 0;
}
int iTopRightCornerCollision(int i, int j, int k)
{
	if (balls.getCell(k).getY() >= board.getY()+bricks.getCell(i, j).getY() + bricks.getHeight() - max(balls.getCell(k).getRadius(), BALL_RADIUS) / 2 
		&& balls.getCell(k).getY() < board.getY()+bricks.getCell(i, j).getY() + bricks.getHeight() + balls.getCell(k).getRadius())
	{
		if (balls.isFireBall()) bricks.getCell(i, j).setStrength(EXPLOSIVE);
		bricks.remove(i, j,k);
		if (!balls.isThruBall())
		{
			if (balls.getCell(k).getDirY() < 0) balls.getCell(k).reverseY();
			if (balls.getCell(k).getDirX() < 0) balls.getCell(k).reverseX();
		}
		return 1;
	}
	return 0;
}
int iBottomRightCornerCollision(int i, int j, int k)
{
	if (balls.getCell(k).getY() >= board.getY()+bricks.getCell(i, j).getY() - balls.getCell(k).getRadius() 
		&& balls.getCell(k).getY() <= board.getY()+bricks.getCell(i, j).getY() + max(balls.getCell(k).getRadius(), BALL_RADIUS) / 2)
	{
		if (balls.isFireBall()) bricks.getCell(i, j).setStrength(EXPLOSIVE);
		bricks.remove(i, j,k);
		if (!balls.isThruBall())
		{
			if (balls.getCell(k).getDirY() > 0) balls.getCell(k).reverseY();
			if (balls.getCell(k).getDirX() < 0) balls.getCell(k).reverseX();
		}
		return 1;
	}
	return 0;
}
int iTopLeftCornerCollision(int i, int j, int k)
{
	if (balls.getCell(k).getY() >= board.getY()+bricks.getCell(i, j).getY() + bricks.getHeight() - max(balls.getCell(k).getRadius(), BALL_RADIUS) / 2 
		&& balls.getCell(k).getY() < board.getY()+bricks.getCell(i, j).getY() + bricks.getHeight() + balls.getCell(k).getRadius())
	{
		if (balls.isFireBall()) bricks.getCell(i, j).setStrength(EXPLOSIVE);
		bricks.remove(i, j,k);
		if (!balls.isThruBall())
		{
			if (balls.getCell(k).getDirY() < 0) balls.getCell(k).reverseY();
			if (balls.getCell(k).getDirX() > 0) balls.getCell(k).reverseX();
		}
		return 1;
	}
	return 0;
}
int iBottomLeftCornerCollision(int i, int j,int k)
{
	if (balls.getCell(k).getY() >= board.getY()+bricks.getCell(i, j).getY() - balls.getCell(k).getRadius() 
		&& balls.getCell(k).getY() <= board.getY()+bricks.getCell(i, j).getY() + max(balls.getCell(k).getRadius(), BALL_RADIUS) / 2)
	{
		if (balls.isFireBall()) bricks.getCell(i, j).setStrength(EXPLOSIVE);
		bricks.remove(i, j,k);
		if (!balls.isThruBall())
		{
			if (balls.getCell(k).getDirY() > 0) balls.getCell(k).reverseY();
			if (balls.getCell(k).getDirX() > 0) balls.getCell(k).reverseX();
		}
		return 1;
	}
	return 0;
}
void CollisionManager::ballXbrick()
{
	int i, j,k;
	for (k = 0;k < balls.getTotal();k++)
	{
		for (i = 0; i < bricks.getRows(); i++)
		{
			for (j = 0; j < bricks.getCols(); j++)
			{
				if (bricks.getCell(i, j).getStrength())
				{
					{
						if (balls.getCell(k).getX() > board.getX() + bricks.getCell(i, j).getX() - balls.getCell(k).getRadius()
							&& balls.getCell(k).getX() < board.getX() + bricks.getCell(i, j).getX() + bricks.getWidth() + balls.getCell(k).getRadius()
							&& balls.getCell(k).getY() > board.getY() + bricks.getCell(i, j).getY() - balls.getCell(k).getRadius()
							&& balls.getCell(k).getY() < board.getY() + bricks.getCell(i, j).getY() + bricks.getHeight() + balls.getCell(k).getRadius())
						{
							if (balls.getCell(k).getX() >= board.getX() + bricks.getCell(i, j).getX() && balls.getCell(k).getX() <= board.getX() + bricks.getCell(i, j).getX() + bricks.getWidth())
							{
								if (iTopSideCollision(i, j,k))return;
								if (iBottomSideCollision(i, j, k))return;
							}
							if (balls.getCell(k).getY() >= board.getY() + bricks.getCell(i, j).getY() && balls.getCell(k).getY() <= board.getY() + bricks.getCell(i, j).getY() + bricks.getHeight())
							{
								if (iLeftSideCollision(i, j, k))return;
								if (iRightSideCollision(i, j, k))return;
							}
							if (balls.getCell(k).getX() >= board.getX() + bricks.getCell(i, j).getX() - balls.getCell(k).getRadius() && balls.getCell(k).getX() <= board.getX() + bricks.getCell(i, j).getX() + balls.getCell(k).getRadius())
							{
								if (iBottomLeftCornerCollision(i, j, k))return;
								if (iTopLeftCornerCollision(i, j, k))return;
							}

							if (balls.getCell(k).getX() >= board.getX() + bricks.getCell(i, j).getX() + bricks.getWidth() - balls.getCell(k).getRadius() && balls.getCell(k).getX() <= board.getX() + bricks.getCell(i, j).getX() + bricks.getWidth() + balls.getCell(k).getRadius())
							{
								if (iBottomRightCornerCollision(i, j, k))return;
								if (iTopRightCornerCollision(i, j, k))return;
							}
							bricks.remove(i, j,k);
							if (!balls.isThruBall())
							{
								balls.getCell(k).setAngle(fmod(PI+balls.getCell(k).getAngle(),2*PI));
							}
							return;
						}
					}
				}
			}
		}
	}
}


/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
