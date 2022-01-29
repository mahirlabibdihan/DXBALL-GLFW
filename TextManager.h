#ifndef __TEXT_MANAGER__
#define __TEXT_MANAGER__
#include "Headers.h"
struct Character {
	unsigned int TextureID; // ID handle of the glyph texture
	glm::ivec2   Size;      // Size of glyph
	glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
	unsigned int Advance;   // Horizontal offset to advance to next glyph
};
class TextManager {
public:
	static map<GLchar, Character> Characters;
	static GLuint shaderProgram, VBO, VAO;
	static const GLchar* vertexShaderSource;
	static const GLchar* fragmentShaderSource;
public:
	static void init();
	static GLuint createProgram();
	static void render(float x, float y, string text, float scale = 1.0);
};
#endif