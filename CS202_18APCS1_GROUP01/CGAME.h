#ifndef _CGAME_H
#define _CGAME_H

#include "CVEHICLE.h"
#include "TEMPLATE.h"
#include "DATA.h"
#include "CONFIG.h"
#include "PATH.h"
#include "CPEOPLE.h"
class CGAME {
private:
	std::vector<laneType> vLane;
	std::vector<std::string> boardGame;
	std::vector<CCAR> carList;
	CPEOPLE player;
	int nLane = 3; // default;
	int max_lane_size = 1500;
	int vehicle_dis = 150;
	int animal_dis = 1;
	int FPS = 60;
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Event mainEvent;
	SDL_Texture *carTexture = NULL;
	SDL_Texture *backgroundTexture = NULL; 
	SDL_Texture *peopleTexture = NULL;
	SDL_Texture *trafficlightTexture = NULL;
	bool isRunning = 1;
public:
	CGAME();
	void SetLane(int laneID);
	SDL_Texture* loadTexture(std::string path);
	void People_Load(const int animation);
	void Background_Load();
	void Vehicle_Load();
	void TrafficLight_Load();
	void drawGame();
	void CheckState();
};
#endif
