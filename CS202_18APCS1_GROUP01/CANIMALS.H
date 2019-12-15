#ifndef _ANIMALS_H
#define _ANIMALS_H

#include "PATH.h"

class CANIMALS {
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

class CDINOSAUR : public CANIMALS {
public:
	CDINOSAUR(int x, int y);
};
class CCROCODILE : public CANIMALS {
public:
	CCROCODILE(int x, int y);
};
#endif