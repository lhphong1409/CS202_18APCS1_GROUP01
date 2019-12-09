#include "CPEOPLE.h"

CPEOPLE::CPEOPLE(){
	mState = 1;
	v = 20;
	mX = 0;
	mY = 0;
}

CPEOPLE::CPEOPLE(int x, int y){
	mX = x;
	mY = y;
	v = 20;
	mState = 1;
}

int CPEOPLE::getV() {
	return v;
}

int CPEOPLE::getmX(){
	return mX;
}

int CPEOPLE::getmY(){
	return mY;
}

void CPEOPLE::up(){
	mY -= v;
	mY = max(mY, 0);
	return;
}

void CPEOPLE::down(){
	mY += v;
	mY = min(mY, 800);
}

void CPEOPLE::left(){
	mX -= v;
	mX = max(mX, 0);
}

void CPEOPLE::right(){
	mX += v;
	mX = min(mX, 1500);
}
