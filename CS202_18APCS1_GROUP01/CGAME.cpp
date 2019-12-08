#include "CGAME.h"

CGAME::CGAME(){
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("CrossRoad-Group-01.exe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	for (int i = 0; i < nLane; i++) {
		laneType cur_laneType; // OFF-RED-YELLOW-GREEN
		vLane.push_back(cur_laneType);
	}
	// lane : 10 x 180:
	// set for CCAR
	carTexture = loadTexture(image_vehicle_car);
	backgroundTexture = loadTexture(image_background);
	SetLane(0);
	SetLane(1);
	SetLane(2);

	return;
}

void CGAME::SetLane(int laneID){
	//lane format : pixel 100-200 400-500 700-800
	const int lanePixel[3] = { 700, 400, 100 };
	CCAR car_obj(0, lanePixel[laneID]);
	int cur_pos = rand() % vehicle_dis;
	while (cur_pos + vehicle_dis + 100 <= max_lane_size) {
		car_obj = CCAR(cur_pos, lanePixel[laneID]);
		cur_pos += car_obj.sX + rand() % vehicle_dis + 100;
		carList.push_back(car_obj);
	}
	return;
}

SDL_Texture* CGAME::loadTexture(std::string path){
	//The final texture
	SDL_Texture* newTexture = NULL;
	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	//Create texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);
	return newTexture;
}
void CGAME::Background_Load() {
	SDL_Rect sourceRect, desRect;
	SDL_QueryTexture(backgroundTexture, NULL, NULL, &sourceRect.w, &sourceRect.h);
	sourceRect.x = sourceRect.y = desRect.x = desRect.y = 0;
	desRect.w = sourceRect.w;
	desRect.h = sourceRect.h;
	SDL_RenderCopy(renderer, backgroundTexture, &sourceRect, &desRect);
	return;
}
void CGAME::Vehicle_Load(){
	SDL_Rect sourceRect, desRect;
	SDL_QueryTexture(carTexture, NULL, NULL, &sourceRect.w, &sourceRect.h);
	sourceRect.x = sourceRect.y = 0;
	desRect.w = sourceRect.w;
	desRect.h = sourceRect.h;
	for (int iCar = 0; iCar < carList.size(); iCar++) {
		desRect.x = carList[iCar].mX;
		desRect.y = carList[iCar].mY;
		SDL_RenderCopy(renderer, carTexture, &sourceRect, &desRect);
		carList[iCar].move();
		carList[iCar].mX %= max_lane_size;
	}
	return;
}
void CGAME::drawGame(){
	/*for (int i = vLane.size()-1; i >= 0; i--) {
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
	*/


	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	int cnt = 0;
	while (isRunning) {
		SDL_RenderClear(renderer);
		while (SDL_PollEvent(&mainEvent)) {
			switch (mainEvent.type) {
			case SDL_QUIT: {
				isRunning = 0;
				break;
			}
			case SDL_MOUSEBUTTONDOWN: {
				isRunning = 0;
				break;
			}
			default: {
				break;
			}
			}
		}
		Background_Load();
		Vehicle_Load();
		SDL_RenderPresent(renderer);
		SDL_Delay(1000/FPS);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
}
