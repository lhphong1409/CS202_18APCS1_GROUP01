#include "CPEOPLE.h"

CPEOPLE::CPEOPLE(){
	mState = 1;
	v = 40;
	mX = 800;
	mY = 790;
}

int CPEOPLE::getV() {
	return v;
}

int CPEOPLE::getEffect(EFFECT idEffect){
	return (effectState[idEffect] > 0);
}

void CPEOPLE::updatePos(int x, int y){
	mX = x;
	mY = y;
}

void CPEOPLE::changeEffect(EFFECT idEffect,  int time){
	effectState[idEffect] = time;
	return;
}

void CPEOPLE::countdownEffect(){
	--effectState[0];
	effectState[0] = max(0, effectState[0]);
	--effectState[1];
	effectState[1] = max(0, effectState[1]);
	--effectState[2];
	effectState[2] = max(0, effectState[2]);

	return;
}

int CPEOPLE::getmX(){
	return mX;
}

int CPEOPLE::getmY(){
	return mY;
}

void CPEOPLE::up(){
	mY -= v;
	mY = max(mY, -100);
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
