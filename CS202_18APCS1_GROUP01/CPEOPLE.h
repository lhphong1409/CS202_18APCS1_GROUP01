#ifndef _CPEOPLE_H
#define _CPEOPLE_H

#include "TEMPLATE.h"

class CPEOPLE {
private:
	int v;
	int effectState[3] = { 0, 0, 0 };
public:
	int mX, mY;
	bool mState;
	int flip = 0;
	int animation_flip = 0;
	CPEOPLE();
	int getmX();
	int getmY();
	int getV();
	int getEffect(EFFECT idEffect);
	int getTimeEffect(int idEffect);
	void updatePos(int x, int y);
	void changeEffect(EFFECT idEffect, int timeEffect);
	void countdownEffect();
	void up();
	void down();
	void left();
	void right();
};
#endif;