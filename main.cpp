/*
 ______   _________ _      _       _
|  ____ \|___   ___| |    | |     | |
| |    \ \   | |   | |____| |     | |
| |    | |   | |   |  ____  |     | |
| |____/ /___| |___| |    | |_____| |
|_______/|_________|_|    |_________|
M A H I R     L A B I B     D I H A N

*/

#include "Headers.h"
#include "Externs.h"
int main()
{
	WindowManager::set();	// Setting window

	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WindowManager::getWidth(), WindowManager::getHeight(), "Dxball", glfwGetPrimaryMonitor(), NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }

	glfwSetKeyCallback(window, KeyboardManager::keyHandler);	// Callback for keyboard interactions
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);	  // Hide the cursor
	glfwSetMouseButtonCallback(window, MouseManager::clickHandler);
	glfwSetCursorPosCallback(window, MouseManager::moveHandler);
	//glfwSetScrollCallback(window, scroll_callback);

	glEnable(GL_BLEND);     // Transparent ColorManager
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);   // Transparent ColorManager
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(2.0);       // getWidth() of drawing lines
	glEnable(GL_POINT_SMOOTH);

	DrawManager::start();
	GameManager::init();
	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		DrawManager::draw();
		TimeManager::update(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	DrawManager::end();
	glfwTerminate();
	glfwDestroyWindow(window);
	exit(EXIT_SUCCESS);
	return 0;
}