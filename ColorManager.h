#ifndef __COLOR_MANAGER__
#define __COLOR_MANAGER__
#include "openGL.h"
#include <tuple>
using namespace std;
#define WHITE 255,255,255
#define BLACK 0,0,0
#define BLUE 0,0,255
#define GREEN 0,255,0
#define RED 255,0,0
#define YELLOW 255,255,0
#define PURPLE 255,255,0
#define ORANGE 255,128,0
#define GREY 100,100,100

class ColorManager {
protected:
	GLint r, g, b;
	static GLfloat clearR, clearG, clearB;
public:
	ColorManager();
	ColorManager(GLfloat r, GLfloat g, GLfloat b);
	void setColor(GLfloat r, GLfloat g, GLfloat b);
	void setColor(tuple<GLfloat, GLfloat, GLfloat>rgb);
	tuple<GLfloat, GLfloat, GLfloat> getColor();
	static tuple<GLfloat, GLfloat, GLfloat> random();
	GLint getR();
	GLint getG();
	GLint getB();
	void save(ofstream& out);
	void load(ifstream& in);
	static void clear()	// Clears the screen
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glClearColor(clearR / 255, clearG / 255, clearB / 255, 1.0);
		glFlush();
	}
	// Sets ColorManager for drawing
	static void set(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0)
	{
		// r,g,b should be 0 to 1
		r /= 255.0;
		g /= 255.0;
		b /= 255.0;
	}
	// Overloaded
	static void set(tuple<GLfloat, GLfloat, GLfloat> rgb, GLfloat a = 1.0)
	{
		GLfloat r = get<0>(rgb), g = get<1>(rgb), b = get<2>(rgb);
		// r,g,b should be 0 to 1
		r /= 255.0;
		g /= 255.0;
		b /= 255.0;
	}

	// Sets Background ColorManager
	static void setBG(GLfloat r, GLfloat g, GLfloat b)
	{
		clearR = r;
		clearG = g;
		clearB = b;
	}
};
#endif