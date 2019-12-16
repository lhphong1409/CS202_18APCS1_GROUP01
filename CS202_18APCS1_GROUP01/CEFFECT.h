#ifndef _CEFFECT_H
#define _CEFFECT_H

#include "PATH.h"
class CEFFECT {
public:
	enum EFFECT type;
	int mX, mY, sX, sY;
	int lane;
	CEFFECT(int x, int y, int lID);
	CEFFECT(int x, int y, EFFECT typeEffect, int lID);
};
#endif