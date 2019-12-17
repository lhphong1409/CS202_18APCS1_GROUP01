#include "CVEHICLE.h"

CVEHICLE::CVEHICLE()
{
}

CVEHICLE::CVEHICLE(int x, int y, int l){
	mX = x;
	mY = y;
	lane = l;
	return;
}

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

