#ifndef _CVEHICLE_H
#define _CVEHICLE_H

#include "TEMPLATE.h"
class CVEHICLE {
public:
	int mX, mY, sX, sY; // row - col;
	int v; // velocity - v = ms for 1 unit of movement;
	bool state;
	virtual void move();
	virtual void tell();
};

class CCAR : public CVEHICLE {
public:
	std::string dbox = "  _______  _/       \\_|_( )_( )_|";
	CCAR(int x, int y);
};
#endif