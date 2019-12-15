#include "CANIMALS.h"

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

CDINOSAUR::CDINOSAUR(int x, int y) {
	mX = x;
	mY = y;
	sX = 224;
	sY = 95;
	state = 0;
	v = default_v = 4;
	lane = 0;
}
CCROCODILE::CCROCODILE(int x, int y) {
	mX = x;
	mY = y;
	sX = 224;
	sY = 95;
	state = 0;
	v = default_v = 4;
	lane = 0;
}
