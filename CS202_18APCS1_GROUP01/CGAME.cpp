#include "CGAME.h"

CGAME::CGAME(){
	std::string empty_lane;
	while (empty_lane.size() < max_lane_size) {
		empty_lane +=' ';
	}
	for (int i = 0; i < nLane; i++) {
		laneType cur_laneType; // OFF-RED-YELLOW-GREEN
		vLane.push_back(cur_laneType);
		for (int j = 0; j < 10; j++)
			boardGame.push_back(empty_lane);
	}
	// lane : 10 x 180:
	// set for CCAR
	SetLane(0);
	SetLane(1);
	SetLane(2);

	return;
}

void CGAME::SetLane(int laneID){
	CCAR car_obj(laneID, 0);
	int cur_pos = rand() % vehicle_dis;
	while (cur_pos + vehicle_dis + 5 <= max_lane_size) {
		car_obj = CCAR(laneID, cur_pos);
		cur_pos += car_obj.sY + rand() % vehicle_dis + 5;
		carList.push_back(car_obj);
	}
}

void CGAME::drawGame(){
	for (int i = vLane.size()-1; i >= 0; i--) {
		for (int j = 0; j < 10; j++) {
			GotoXY(0, 11 * (vLane.size() - i - 1) + j + 0);
			std::cout << boardGame[i*10 + j];
		}
		GotoXY(0, 11 * (vLane.size() - i - 1) + 10);
		std::cout << "LANE " << i+1 << " STATE: " << vLane[i].light.getState() << " TIME: " << vLane[i].light.getTime() << "\n";
		vLane[i].light.CountDown();
	}
	for (int iCar = 0; iCar < carList.size(); iCar++) {
		for (int i = 0; i < carList[iCar].sX; i++) {
			for (int j = 0; j < carList[iCar].sY; j++) {
				GotoXY((carList[iCar].mY + j) % max_lane_size, (vLane.size() - carList[iCar].mX - 1) * 11 + 6 + i);
				std::cout << carList[iCar].dbox[i * carList[iCar].sY + j];
			}
		}
		carList[iCar].move();
	}
}
