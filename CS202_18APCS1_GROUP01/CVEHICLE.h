#ifndef _CVEHICLE_H
#define _CVEHICLE_H

#include "PATH.h"

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
	CCAR(int x, int y);
};
#endif