#ifndef __KEYBOARD_MANAGER__
#define __KEYBOARD_MANAGER__
class KeyboardManager {
	public:
	static void keyHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void specialKeyHandler(GLint, GLint, GLint);
	static void keyboard(int);
	static void specialKeyboard(unsigned char);
};
#endif