#include "DATA.h"

laneType::laneType(){
	light.setState(static_cast<LIGHTst>(rand() % OFF+1));
	if (light.getState() == LIGHTst::OFF) {
		light.setTime(-1);
		return;
	}
	if (light.getState() == LIGHTst::YELLOW) {
		light.setTime(rand() % 3 + 1);
	}
	else {
		light.setTime(rand() % 10 + 1);
	}
	return;
}

laneType::laneType(enum LIGHTst cur_state) {
	light.setState(cur_state);
	if (cur_state != OFF)
		if (light.getState() == LIGHTst::YELLOW) {
			light.setTime(rand() % 3 + 1);
		}
		else {
			light.setTime(rand() % 10 + 1);
		}
	return;
}
