#ifndef _CSAVE_H
#define _CSAVE_H

#include "CVEHICLE.h"
#include "CANIMALS.H"
#include "CPEOPLE.h"
#include "CEFFECT.h"
#include "PATH.h"
#include "DATA.h"
#include "CONFIG.h"

class CSAVE {
public:
	int level;
	bool isRunning = 1;
	std::vector<CVEHICLE> vehicleList;
	std::vector<CANIMALS> animalList;
	std::vector<CEFFECT> effectList;
	std::vector<laneType> vLane;
	CPEOPLE player;
	std::string path;
	int CheckState();
	void SetLane(int laneID, bool objectType);
	void Init();

	//demo.txt
	
};
#endif