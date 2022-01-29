#include "Headers.h"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "Opengl\\stb_image.h"
#endif
GLuint TextureManager::shaderProgram, TextureManager::VBO, TextureManager::VAO;
const GLchar* TextureManager::vertexShaderSource = "#version 430 core\n"
"layout(location = 0) in vec4 aPos;"
"out vec2 TexCoord;"
"uniform mat4 projection;"
"void main()"
"{"
"gl_Position = projection * vec4(aPos.x,aPos.y,1.0, 1.0);"
"TexCoord=vec2(aPos.z,aPos.w);"
"}";

const GLchar* TextureManager::fragmentShaderSource = "#version 430 core\n"
"out vec4 FragColor;"
"in vec2 TexCoord;"
"uniform sampler2D texture1;"
"void main()"
"{"
"FragColor = texture(texture1, TexCoord);"
"}";
TextureManager::TextureManager()
{

}
TextureManager::TextureManager(const char* filename)
{

}
TextureManager::~TextureManager()
{
	
}
GLuint TextureManager::createProgram()
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// link shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Delete shader
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}
void TextureManager::init()
{
	shaderProgram = createProgram();
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(WindowManager::getWidth()), 0.0f, static_cast<float>(WindowManager::getHeight()));
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));


	// configure VAO/VBO for texture quads
	// -----------------------------------
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 4, NULL, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void TextureManager::load(const char* filename)
{
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load image
	GLint n;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* image = stbi_load(filename, &width, &height, &n, 0);
	if (image == NULL) cout << "ERROR LOADING IMAGE" << endl;
	if (n == 4)	// PNG
	{
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			width,
			height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			image
		);
	}
	else if (n == 3)  // JPG
	{
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGB,
			width,
			height,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			image
		);
	}
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);
}
void TextureManager::render(GLfloat x,GLfloat y)
{
	// Showing image to screen
	GLfloat vertices[] = {
		x,     y,		0.0f, 0.0f ,
		x + width, y,       1.0f, 0.0f ,
		x + width ,y + height,   1.0f, 1.0f ,
		x,     y + height,     0.0f, 1.0f
	};
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUseProgram(shaderProgram);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
void TextureManager::render(GLfloat x, GLfloat y, GLuint totalC, GLuint totalR, GLuint startFlag, GLuint totalFlag, GLint& flag, bool loop)
{
	int row = flag / totalC, col = flag % totalC;

	if (flag >= 0)
	{
		flag++;
	}
	if (flag == startFlag + totalFlag)
	{
		if (loop) flag = startFlag;
		else flag = -1;
	}

	GLfloat vertices[] = {
	x,     y,		(1.0f / totalC) * (col),		1.0f - (1.0f / totalR) * (row + 1),
	x + width / totalC, y,       (1.0f / totalC) * (col + 1),	1.0f - (1.0f / totalR) * (row + 1),
	x + width / totalC, y + height / totalR,   (1.0f / totalC) * (col + 1),	1.0f - (1.0f / totalR) * (row),
	x,     y + height / totalR,   (1.0f / totalC) * (col),		1.0f - (1.0f / totalR) * (row)
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUseProgram(shaderProgram);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
void TextureManager::render(GLfloat x, GLfloat y,GLint width,GLint height ,unsigned char* image)
{
	glRasterPos3f(x, y, 0);	// Setting image position
	glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);	// Showing image
}
void TextureManager::render(GLfloat x, GLfloat y, const char* filename)
{
	GLuint texture;
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load image
	GLint width,height,n;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* image = stbi_load(filename, &width, &height, &n, 0);
	if (image == NULL) cout << "ERROR LOADING IMAGE" << endl;
	if (n == 4)	// PNG
	{
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			width,
			height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			image
		);
	}
	else if (n == 3)  // JPG
	{
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGB,
			width,
			height,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			image
		);
	}
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);
	GLfloat vertices[] = {
		x,     y,		0.0f, 0.0f ,
		x + width, y,       1.0f, 0.0f ,
		x + width ,y + height,   1.0f, 1.0f ,
		x,     y + height,     0.0f, 1.0f
	};
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUseProgram(shaderProgram);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
