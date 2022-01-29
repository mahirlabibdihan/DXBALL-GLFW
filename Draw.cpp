
/*------------------------------------------------------------------------------ D R A W I N G S -------------------------------------------------------------------------------*/
#include "Headers.h"
#include "Externs.h"
vector<DrawManager::vertice> DrawManager::vertices;
GLfloat DrawManager::r, DrawManager::g, DrawManager::b, DrawManager::a;
GLuint DrawManager::shaderProgram, DrawManager::VBO, DrawManager::VAO;
const GLchar* DrawManager::vertexShaderSource = "#version 430 core\n"
"layout (location = 0) in vec2 aPos;\n"
"uniform mat4 projection;\n"
"uniform mat4 translation;\n"
"void main()\n"
"{\n"
"   gl_Position =  translation * projection * vec4(aPos,0.0, 1.0);\n"
"}";

const GLchar* DrawManager::fragmentShaderSource = "#version 430 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}";
void DrawManager::draw()
{
	clear();
	if (menu.getMenu() == MenuManager::MAIN)
	{
		menu.draw();
	}
	else if (menu.getMenu() == MenuManager::NAME_ENTRY)
	{
		menu.drawNameEntry();
		menu.drawBack();
	}
	else if (menu.getMenu() == MenuManager::CUSTOM_GAME)
	{
		menu.drawCustom();
		menu.drawBack();
	} 

	else if (menu.getMenu() == MenuManager::HIGH_SCORE)
	{
		menu.drawHighScore();
		menu.drawBack();
	}
	else if (menu.getMenu() == MenuManager::HELP_PAGE)
	{
		menu.drawHelp();
		menu.drawBack();
	}
	else if (menu.getMenu() == MenuManager::QUIT_GAME)
	{
		menu.drawQuit();
	}
	else if (menu.getMenu() == MenuManager::GAME_OVER)
	{
		menu.drawGameOver();
		if(LevelManager::getLevel()>0)menu.drawBack();
	}
	else if (menu.getMenu() == MenuManager::WINNER)
	{
		menu.drawWin();
		if (LevelManager::getLevel() > 0)menu.drawBack();
	}
	else if (menu.getMenu() == MenuManager::GAME || menu.getMenu() == MenuManager::DEATH)
	{
		menu.drawGame();
	}
	else if (menu.getMenu() == MenuManager::LEVEL_UP)
	{
		menu.drawLevelUp();
	}
	if (menu.getMenu() != MenuManager::GAME
		&& menu.getMenu() != MenuManager::DEATH 
		&& menu.getMenu() != MenuManager::LEVEL_UP 
		&& menu.getMenu() != MenuManager::QUIT_GAME 
		&& !(LevelManager::getLevel()==0&&(menu.getMenu()==MenuManager::GAME_OVER|| menu.getMenu() == MenuManager::WINNER)))
	{
		
		TextureManager::render(MouseManager::getX(), MouseManager::getY() - 35, "Data\\Image\\Mouse.png");
	}
		
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
