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
	peopleTexture = loadTexture(image_people);
	trafficlightTexture = loadTexture(image_trafficlight);
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
	while (cur_pos + vehicle_dis + vehicle_dis <= max_lane_size) {
		car_obj = CCAR(cur_pos, lanePixel[laneID]);
		cur_pos += car_obj.sX + rand() % vehicle_dis + vehicle_dis;
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
void CGAME::People_Load(const int animation){
	// 80x80
	int animateSize = 80;
	SDL_Rect sourceRect, desRect;
	SDL_QueryTexture(peopleTexture, NULL, NULL, &sourceRect.w, &sourceRect.h);
	switch (animation){
		case 0: { // UP
			sourceRect.x = 0;
			sourceRect.y = 1;
			break;
		}
		case 1: {
			sourceRect.x = 1;
			sourceRect.y = 1;
			break;
		}
		case 2: {
			sourceRect.x = 3;
			sourceRect.y = 1;
			break;
		}
		case 3: { // DOWN
			sourceRect.x = 0;
			sourceRect.y = 0;
			break;
		}
		case 4: {
			sourceRect.x = 1;
			sourceRect.y= 0;
			break;
		}
		case 5: {
			sourceRect.x = 3;
			sourceRect.y = 0;
			break;
		}
		case 6: { // LEFT
			sourceRect.x = 1;
			sourceRect.y = 2;
			break;
		}
		case 7: {
			sourceRect.x = 0;
			sourceRect.y = 2;
			break;
		}
		case 8: {
			sourceRect.x = 2;
			sourceRect.y = 2;
			break;
		}
		case 9: { // RIGHT
			sourceRect.x = 0;
			sourceRect.y = 3;
			break;
		}
		case 10: {
			sourceRect.x = 3;
			sourceRect.y = 2;
			break;
		}
		case 11: {
			sourceRect.x = 1;
			sourceRect.y = 3;
			break;
		}
		default: {
			break;
		}
	}
	sourceRect.x *= animateSize;
	sourceRect.y *= animateSize;
	desRect.x = player.getmX();
	desRect.y = player.getmY();
	desRect.w = sourceRect.w = animateSize;
	desRect.h = sourceRect.h = animateSize;
	SDL_RenderCopy(renderer, peopleTexture, &sourceRect, &desRect);
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

void CGAME::TrafficLight_Load(){
	SDL_Rect sourceRect, desRect;
	SDL_QueryTexture(trafficlightTexture, NULL, NULL, &sourceRect.w, &sourceRect.h);
	for (int i = 0; i < nLane; i++) {
		//vLane[i].light.
	}
	SDL_RenderCopy(renderer, trafficlightTexture, &sourceRect, &desRect);
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

	while (isRunning) {
		SDL_RenderClear(renderer);
		Background_Load();
		Vehicle_Load();
		TrafficLight_Load();
		People_Load(player.flip + player.animation_flip);
		CheckState();
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
			case SDL_KEYDOWN: {
				++player.animation_flip;
				player.animation_flip %= 3;
				switch (mainEvent.key.keysym.sym) {
				case SDLK_UP: {
					player.up();
					player.flip = 0;
					break;
				}
				case SDLK_DOWN: {
					player.down();
					player.flip = 3;
					break;
				}
				case SDLK_LEFT: {
					player.left();
					player.flip = 6;
					break;
				}
				case SDLK_RIGHT: {
					player.right();
					player.flip = 9;
					break;
				}
				default:
					player.animation_flip = 0;
					break;
				}
			}
			default: {
				break;
			}
			}
		}
		SDL_Delay(1000 / 60);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void CGAME::CheckState(){
	// 30 - 15
	int pxl, pyl, pxr, pyr;
	pxl = player.getmX() + 30;
	pxr = player.getmX() - 30 + 80;
	pyl = player.getmY() + 15;
	pyr = player.getmY() - 15 + 80;
	for (int iCar = 0; iCar < carList.size(); iCar++) {
		if (pxl >= carList[iCar].mX && pxl <= carList[iCar].mX + carList[iCar].sX
			&& pyl >= carList[iCar].mY && pyl <= carList[iCar].mY + carList[iCar].sY) {
			//isRunning = 0;
			player = CPEOPLE(0, 0);
			return;
		}
		if (pxr >= carList[iCar].mX && pxr <= carList[iCar].mX + carList[iCar].sX
			&& pyr >= carList[iCar].mY && pyr <= carList[iCar].mY + carList[iCar].sY) {
			//isRunning = 0;
			player = CPEOPLE(0, 0);
			return;
		}
		if (pxl >= carList[iCar].mX && pxl <= carList[iCar].mX + carList[iCar].sX
			&& pyr >= carList[iCar].mY && pyr <= carList[iCar].mY + carList[iCar].sY) {
			//isRunning = 0;
			player = CPEOPLE(0, 0);
			return;
		}
		if (pxr >= carList[iCar].mX && pxr <= carList[iCar].mX + carList[iCar].sX
			&& pyl >= carList[iCar].mY && pyl <= carList[iCar].mY + carList[iCar].sY) {
			//isRunning = 0;
			player = CPEOPLE(0, 0);
			return;
		}
	}
	std::cout << "ALIVE\n";
}
