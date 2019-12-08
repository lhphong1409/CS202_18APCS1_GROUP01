#include "CVEHICLE.h"

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
	path = image_vehicle_car;;
	state = 0;
	v = 10;
}
