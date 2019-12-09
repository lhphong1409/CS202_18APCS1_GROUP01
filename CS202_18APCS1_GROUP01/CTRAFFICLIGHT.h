#ifndef _CTRAFFICLIGHT_H
#define _CTRAFFICLIGHT_H
#include "TEMPLATE.h"

enum LIGHTst { RED, GREEN, YELLOW, OFF };

class CTRAFFICLIGHT {
private:
	int time_;
	int frame;
	enum LIGHTst state_;
	//state_ =  0, 1, 2, 3 : RED YELLOW GREEN OFF 
public:
	int getFrame();
	int getTime();
	enum LIGHTst getState();
	void incFrame();
	void setState(enum LIGHTst cur_state_);
	void setTime(int cur_time);
	void CountDown();
};

#endif // _CTRAFFICLIGHT_H
