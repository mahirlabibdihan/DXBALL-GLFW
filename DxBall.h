#ifndef _DX_BALL_
#define _DX_BALL_
# include "iGraphics.h"
# include "AudioManager.h"
# include <stack>
using namespace std;

/*----------------------------------------------------------------------------- C O N S T A N T -------------------------------------------------------------------------------*/

#define ScreenHeight 1080
#define ScreenWidth 1920
#define TotalC 20
#define TotalR 20
#define BlockHeight 30
#define BlockWidth 70
#define Ball_Board 5
#define WallY 350

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

#define ScoreUp 10

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/




/*----------------------------------------------------------------------------- F U N C T I O N S -----------------------------------------------------------------------------*/

void Initialize(int, int, char*);
void iReset();
void iSet();
void iSetCustom();
void iResetDropItems();
void iResetBullet();
void iLoadState();
void iSaveState();
void iSaveScore();
void iDeath();
void iLevelUp();
void iCatch();
void iBallMove();
void iDirection();


void iDrawBall(int, int);
void iDrawBack();
void iDrawHighScore();
void iDrawHelp();
void iDrawMenu();
void iDrawBlock(int, int, double , double, double);
void iDrawBomb(int, int);
void iDrawBrick(int, int);
void iDrawBullet(int, int);
void iDrawBoard(int, int);
void iDrawTable();
void iDrawCustom();
void VerticalSegment(int , int, int, int, int);
void HorizontalSegment(int, int, int , int, int);
void iDrawDigit(int, int, int, int);
void iDrawScore(int, int, int, int);
void iDrawSmallScore(int, int, int, int);
void iDrawLevel();
void iDrawRemaining();
void iDrawTime();
void iDrawWin();
void iDrawLevelUp();
void iDrawQuit();
void iDrawGameOver();
void iDrawNameEntry();
void iDraw();


void iMouseMove(int, int);
void iMouseLeftButtonDownMenu(int mx, int my);
void iCustomPlay();
void iMouseLeftButtonDownCustom(int mx, int my);
void iMouseLeftButtonDown(int mx, int my);
void iMouseRightButtonDown(int mx, int my);
void iMouse(int, int, int, int);
void iMouseOver(int, int);
int iNewMenuSelection(int, int);
int iCustomMenuSelection(int, int);
int iResumeMenuSelection(int, int);
int iHighScoreMenuSelection(int, int);
int iHelpMenuSelection(int, int);
int iQuitMenuSelection(int, int);
void iMenuSelection(int, int);


void iNameEntry(unsigned char );
void iKeyboard(unsigned char);
void iSpecialKeyboard(unsigned char );


void iRemoveBlock(int, int);
void iBomb(int, int);
void iCollision();
int iRightSideCollision(int, int);
int iLeftSideCollision(int, int);
int iTopSideCollision(int, int);
int iBottomSideCollision(int, int);
int iTopRightCornerCollision(int, int);
int iBottomRightCornerCollision(int, int);
int iTopLeftCornerCollision(int, int);
int iBottomLeftCornerCollision(int, int);
/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------- S T R U C T U R E -----------------------------------------------------------------------------*/





/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#endif