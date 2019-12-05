#include "CGAME.h"

CGAME::CGAME(){
	std::string empty_lane;
	while (empty_lane.size() < max_lane_size) {
		empty_lane +='+';
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
	return;
}

void CGAME::SetLane(int laneID){
	CCAR car_obj(laneID, 0);
	int cur_pos = rand() % 20;
	while (cur_pos + car_obj.sY + vehicle_dis <= max_lane_size) {
		car_obj = CCAR(laneID, cur_pos);
		cur_pos += car_obj.sY + vehicle_dis;
		carList.push_back(car_obj);
	}
}

void CGAME::drawGame(){
	for (int i = vLane.size()-1; i >= 0; i--) {
		for (int j = 0; j < 10; j++) {
			GotoXY(10, 11 * (vLane.size() - i - 1) + j + 3);
			std::cout << boardGame[i*10 + j];
		}
		GotoXY(10, 11 * (vLane.size() - i - 1) + 10 + 3);
		std::cout << "LANE " << i+1 << " STATE: " << vLane[i].light.getState() << " TIME: " << vLane[i].light.getTime() << "\n";
		vLane[i].light.CountDown();
	} 
}
