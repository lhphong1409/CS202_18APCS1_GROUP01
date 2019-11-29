#include "CTRAFFICLIGHT.h"

int CTRAFFICLIGHT::getTime(){
	return time_;
}

enum LIGHTst CTRAFFICLIGHT::getState() {
	return state_;
}

void CTRAFFICLIGHT::setState(enum LIGHTst cur_state_) {
	state_ = cur_state_;
	return;
}

void CTRAFFICLIGHT::setTime(int cur_time){
	time_ = cur_time;
	return;
}

void CTRAFFICLIGHT::CountDown(){
	if (getState() == OFF) {
		return;
	}
	--time_;
	if (time_ == 0) {
		state_ = static_cast<LIGHTst>((state_ + 1) % (3));
		if (getState() == LIGHTst::YELLOW) {
			setTime(rand() % 3 + 1);
		}
		else {
			setTime(rand() % 10 + 1);
		}
	}
}
