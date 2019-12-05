#ifndef _CGAME_H
#define _CGAME_H

#include "CVEHICLE.h"
#include "TEMPLATE.h"
#include "DATA.h"
#include "CONFIG.h"
class CGAME {
private:
	std::vector<laneType> vLane;
	std::vector<std::string> boardGame;
	std::vector<CCAR> carList;
	int nLane = 3; // default;
	int max_lane_size = 180;
	int vehicle_dis = 30;
	int animal_dis = 1;
	//boardGame[i*10][j] = row i col j
public:
	CGAME();
	void SetLane(int laneID);
	void drawGame();
};
#endif
