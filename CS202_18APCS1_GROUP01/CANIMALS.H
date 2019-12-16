#ifndef _ANIMALS_H
#define _ANIMALS_H
#include "PATH.h"
enum ANIMALS{DINOSAUR, CROCODILE, HORSE };
class CANIMALS {
public:
	CANIMALS(int x, int y, int l);
	int mX, mY, sX, sY; // row - col;
	int v, default_v; // velocity 
	int lane;
	int anima;
	bool state;
	enum ANIMALS type;
	virtual void setV(const int value);
	virtual void setLane(const int value);
	virtual void move();
	virtual void tell();
};

class CDINOSAUR : public CANIMALS {
public:
	CDINOSAUR(int x, int y, int l) : CANIMALS(x, y, l) 
	{
		v = default_v = 3;
		state = 0;
		sX = 79;
		sY = 99;
		type = DINOSAUR;
	}
};

class CCROCODILE : public CANIMALS {
public:
	CCROCODILE(int x, int y, int l) : CANIMALS(x, y, l) 
	{
		v = default_v = 3;
		state = 0;
		sX = 214;
		sY = 56;
		type = CROCODILE ;
	}
};
class CHORSE : public CANIMALS {
public:
	CHORSE(int x, int y, int l) : CANIMALS(x, y, l) 
	{
		v = default_v = 3;
		state = 0;
		sX = 98;
		sY = 96;
		type = HORSE;
	}
};
#endif