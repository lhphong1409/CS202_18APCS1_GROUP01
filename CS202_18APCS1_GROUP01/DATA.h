#ifndef _DATA_H
#define _DATA_H

#include "CTRAFFICLIGHT.h"
#include "TEMPLATE.h"


class laneType{
private:
public:
	CTRAFFICLIGHT light;
	laneType();
	laneType(enum LIGHTst cur_state);
};
#endif