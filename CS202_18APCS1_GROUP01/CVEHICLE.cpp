#include "CVEHICLE.h"

void CVEHICLE::move(){
	++mY;
	return;
}

void CVEHICLE::tell(){
	return;
}

CCAR::CCAR(int x, int y){
	mX = x;
	mY = y;
	state = 0;
	v = 100;
	sX = 3;
	sY = 11;
}
