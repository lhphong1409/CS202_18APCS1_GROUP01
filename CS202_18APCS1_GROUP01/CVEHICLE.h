#ifndef _CVEHICLE_H
#define _CVEHICLE_H

#include "PATH.h"

class CVEHICLE {
public:
	int mX, mY, sX, sY; // row - col;
	int v, default_v; // velocity 
	int lane;
	bool state;
	virtual void setV(const int value);
	virtual void setLane(const int value);
	virtual void move();
	virtual void tell();
};

class CCAR : public CVEHICLE {
public:
	CCAR(int x, int y);
};
#endif