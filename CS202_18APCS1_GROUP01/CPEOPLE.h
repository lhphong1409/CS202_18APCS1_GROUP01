#ifndef _CPEOPLE_H
#define _CPEOPLE_H

#include "TEMPLATE.h"

enum EFFECT { SLOW, SHIELD, REDLIGHT};

class CPEOPLE {
private:
	int mX, mY;	
	int v;
	int effectState[3] = { 0, 0, 0 };
public:
	bool mState;
	int flip = 0;
	int animation_flip = 0;
	CPEOPLE();
	int getmX();
	int getmY();
	int getV();
	int getEffect(EFFECT idEffect);
	void updatePos(int x, int y);
	void changeEffect(EFFECT idEffect, int timeEffect);
	void countdownEffect();
	void up();
	void down();
	void left();
	void right();
};
#endif;