#include "CEFFECT.h"

CEFFECT::CEFFECT(int x, int y, int lID){
	mX = x;
	mY = y;
	sX = sY = 80;
	type = static_cast<EFFECT>(rand() % (3));
	lane = lID;
	return;
}


CEFFECT::CEFFECT(int x, int y, EFFECT typeEffect, int lID){
	mX = x;
	mY = y;
	sX = sY = 80;
	type = typeEffect;
	lane = lID;
	return;
}
