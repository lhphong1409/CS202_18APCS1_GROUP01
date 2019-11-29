#include "CGAME.h"

CGAME::CGAME(const int & nLane){
	// nLane : Number of Lane;
	std::string a = "_________________________";
	for (int i = 0; i < nLane; i++) {
		laneType cur_laneType;
		vLane.push_back(cur_laneType);
		for (int j = 0 ; j < 5; j ++)	
			boardGame.push_back(a);
	}
	return;
}

CGAME::CGAME(){
}

void CGAME::drawGame(){
	for (int i = vLane.size()-1; i >= 0; i--) {
		for (int j = 0; j < 5; j++) {
			std::cout << boardGame[i*5 + j] << "\n";
		}
		std::cout << "LANE " << i+1 << " STATE: " << vLane[i].light.getState() << " TIME: " << vLane[i].light.getTime() << "\n";
		vLane[i].light.CountDown();
	} 
}
