#include "CVEHICLE.h"

void CVEHICLE::setV(const int value){
	v = value;
	return;
}

void CVEHICLE::setLane(const int value){
	lane = value;
}

void CVEHICLE::move(){
	mX += v;
	return;
}

void CVEHICLE::tell(){
	return;
}

CCAR::CCAR(int x, int y){
	mX = x;
	mY = y;
	sX = 224;
	sY = 95;
	state = 0;
	v = default_v = 4;
	lane = 0;
}
CTRUCK::CTRUCK(int x, int y) {
	mX = x;
	mY = y;
	sX = 224;
	sY = 95;
	state = 0;
	v = default_v = 6;
	lane = 0;
}
CBUS::CBUS(int x, int y) {
	mX = x;
	mY = y;
	sX = 224;
	sY = 95;
	state = 0;
	v = default_v = 6;
	lane = 0;
}


