#ifndef __PARTICLES_MANAGER__
#define __PARTICLES_MANAGER__
#include "Particle.h"
class ParticlesManager
{
	vector<Particle> particlesField;
	
public:
	void add(GLfloat, GLfloat);
	void addspark(GLfloat, GLfloat);
	void add(GLfloat, GLfloat,GLfloat,GLfloat);
	void update();
	void draw();
	void reset();
	void destroyBall(GLfloat, GLfloat);
	void init();
	void save(ofstream& out);
	void load(ifstream& in);
};
#endif
