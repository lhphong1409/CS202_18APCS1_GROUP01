#ifndef _CPEOPLE_H
#define _CPEOPLE_H

#include "TEMPLATE.h"

enum EFFECT { SLOW, SHIELD, REDLIGHT};

class CPEOPLE {
private:
	int mX, mY;	
	int v;
	std::vector<EFFECT> curEffect;
public:
	bool mState;
	int flip = 0;
	int animation_flip = 0;
	CPEOPLE();
	CPEOPLE(int x, int y);
	int getmX();
	int getmY();
	int getV();
	void up();
	void down();
	void left();
	void right();
};
#endif;