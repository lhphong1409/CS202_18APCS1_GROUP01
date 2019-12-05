#include "CVEHICLE.h"

void CVEHICLE::move(int & mX, int & my){
	++my;
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
	sY = 10;
}
