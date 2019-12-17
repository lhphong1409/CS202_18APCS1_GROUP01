#ifndef _CVEHICLE_H
#define _CVEHICLE_H

#include "PATH.h"

class CVEHICLE {
public:
	CVEHICLE();
	CVEHICLE(int x, int y, int l);
	int mX, mY, sX, sY; // row - col;
	int v, default_v; // velocity 
	int lane;
	bool state;
	enum OBJECT type;
	virtual void setV(const int value);
	virtual void setLane(const int value);
	virtual void move();
	virtual void tell();
};

class CCAR : public CVEHICLE {
public:
	CCAR(int x, int y, int l) : CVEHICLE(x, y, l) {
		v = default_v = 3;
		state = 0;
		sX = 210;
		sY = 100;
		type = CAR;
	}
};

class CTRUCK: public CVEHICLE {
public:
	CTRUCK(int x, int y, int l) : CVEHICLE(x, y, l) {
		v = default_v = 3;
		state = 0;
		sX = 356;
		sY = 100;
		type = TRUCK;
	}
};
class CBUS : public CVEHICLE {
public:
	CBUS(int x, int y, int l) : CVEHICLE(x, y, l) {
		v = default_v = 3;
		state = 0;
		sX = 205;
		sY = 100;
		type = BUS;
	}
};
#endif