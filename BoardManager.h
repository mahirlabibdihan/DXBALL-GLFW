#ifndef __BOARD_MANAGER__
#define __BOARD_MANAGER__
#include "Headers.h"
class BoardManager:public Rectangle {
public:
	BoardManager();
	void init();
	void set();
	void fall();
	void save(ofstream& out);
	void load(ifstream& in);
};
#endif