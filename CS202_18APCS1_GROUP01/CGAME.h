#ifndef _CGAME_H
#define _CGAME_H

#include "CVEHICLE.h"
#include "CANIMALS.H"
#include "TEMPLATE.h"
#include "DATA.h"
#include "CONFIG.h"
#include "PATH.h"
#include "CPEOPLE.h"
class CGAME {
private:
	std::vector<laneType> vLane;
	std::vector<CVEHICLE> vehicleList;
	std::vector<CANIMALS> animalList;
	CPEOPLE player;
	int nLane = 3; // default;
	int max_lane_size = 1500;
	int vehicle_dis = 150;
	int animal_dis = 150;
	int FPS = 60, frame = 0;
	int score = 0, level = 1;
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Event mainEvent;
	SDL_Texture *carTexture = NULL;
	SDL_Texture* truckTexture = NULL;
	SDL_Texture* busTexture = NULL;
	SDL_Texture* dinosaurTexture[4];
	SDL_Texture* crocodileTexture[4];
	SDL_Texture* horseTexture[4];
	SDL_Texture *backgroundTexture[3];
	SDL_Texture *peopleTexture = NULL;
	SDL_Texture *trafficlightTexture = NULL;
	SDL_Texture *menuTexture[4];
	SDL_Texture *numberTexture[10];
	bool isRunning = 1;
public:
	CGAME();
	void Init();
	void SetLane(int laneID, bool objectType);
	SDL_Texture* loadTexture(std::string path);
	void TextureLoad();
	void Menu_Load(int curChoice);
	void People_Load(const int animation);
	void Background_Load();
	void Vehicle_Load();
	void Animals_Load();
	void TrafficLight_Load();
	int CheckState();
	void drawGame();
	void playGame();
};
#endif
