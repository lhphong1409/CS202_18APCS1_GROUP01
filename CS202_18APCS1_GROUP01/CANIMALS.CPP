#include "CANIMALS.h"

CANIMALS::CANIMALS(int x, int y, int l) {
	mX = x;
	mY = y;
	lane = l;
	anima = 0;
	return;
}

void CANIMALS::setV(const int value) {
	v = value;
	return;
}

void CANIMALS::setLane(const int value) {
	lane = value;
}

void CANIMALS::move() {
	mX += v;
	return;
}

void CANIMALS::tell() {
	return;
}
