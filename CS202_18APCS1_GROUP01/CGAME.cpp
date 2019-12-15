#include "CGAME.h"

CGAME::CGAME(){
	srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("CrossRoad-Group-01.exe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// lane : 10 x 180:
	// set for CCAR
	TextureLoad();

	return;
}

void CGAME::Init() {
	isRunning = 1;
	player = CPEOPLE();
	vLane.clear();
	vehicleList.clear();
	for (int i = 0; i < nLane; i++) {
		laneType cur_laneType; // OFF-RED-YELLOW-GREEN
		vLane.push_back(cur_laneType);
	}
	SetLane(0);
	SetLane(1);
	SetLane(2);
}

void CGAME::SetLane(int laneID){
	//lane format : pixel 100-200 400-500 700-800
	int cur_pos = rand() % vehicle_dis;
	while (cur_pos + vehicle_dis + vehicle_dis <= max_lane_size) {
		CARTYPE cur_type = static_cast<CARTYPE>(rand() % (3));
		switch (cur_type) {
		case CARTYPE::CAR:
			vehicleList.push_back(CCAR(cur_pos, lanePixel[laneID], laneID));
			break;
		case CARTYPE::BUS:
			vehicleList.push_back(CBUS(cur_pos, lanePixel[laneID], laneID));
			break;
		case CARTYPE::TRUCK:
			vehicleList.push_back(CTRUCK(cur_pos, lanePixel[laneID], laneID));
			break;
		default:
			break;
		}
		cur_pos += vehicleList.back().sX + rand() % vehicle_dis + vehicle_dis;
		//std::cout << vehicleList.back().type << "\n";
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

void CGAME::TextureLoad(){
	carTexture = loadTexture(image_vehicle_car);
	busTexture = loadTexture(image_vehicle_bus);
	truckTexture = loadTexture(image_vehicle_truck);

	backgroundTexture[0] = loadTexture(image_background[0]);
	backgroundTexture[1] = loadTexture(image_background[1]);
	backgroundTexture[2] = loadTexture(image_background[2]);

	menuTexture[0] = loadTexture(image_menu[0]);
	menuTexture[1] = loadTexture(image_menu[1]);
	menuTexture[2] = loadTexture(image_menu[2]);
	menuTexture[3] = loadTexture(image_menu[3]);

	peopleTexture = loadTexture(image_people);
	trafficlightTexture = loadTexture(image_trafficlight);
}

void CGAME::Menu_Load(int curChoice) {
	SDL_Rect sourceRect, desRect;
	SDL_QueryTexture(menuTexture[curChoice], NULL, NULL, &sourceRect.w, &sourceRect.h);
	sourceRect.x = sourceRect.y = desRect.x = desRect.y = 0;
	desRect.w = sourceRect.w;
	desRect.h = sourceRect.h;
	SDL_RenderCopy(renderer, menuTexture[curChoice], &sourceRect, &desRect);
}

void CGAME::People_Load(const int animation){
	// 80x80
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
	int animateSize = sourceRect.w / 4;
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
	SDL_QueryTexture(backgroundTexture[level%3], NULL, NULL, &sourceRect.w, &sourceRect.h);
	sourceRect.x = sourceRect.y = desRect.x = desRect.y = 0;
	desRect.w = sourceRect.w;
	desRect.h = sourceRect.h;
	SDL_RenderCopy(renderer, backgroundTexture[level%3], &sourceRect, &desRect);
	return;
}

void CGAME::Vehicle_Load(){
	SDL_Rect sourceRect, desRect;
	SDL_Texture *curTexture;
	for (int iVe = 0; iVe < vehicleList.size(); iVe++) {
		switch (vehicleList[iVe].type){
		case CARTYPE::BUS:
			curTexture = busTexture;
			break;
		case CARTYPE::TRUCK:
			curTexture = truckTexture;
			break;
		case CARTYPE::CAR:
			curTexture = carTexture;
			break;

		default:
			curTexture = carTexture;
			break;
		}
		SDL_QueryTexture(curTexture, NULL, NULL, &sourceRect.w, &sourceRect.h);
		sourceRect.x = sourceRect.y = 0;
		desRect.w = sourceRect.w;
		desRect.h = sourceRect.h;
		desRect.x = vehicleList[iVe].mX;
		desRect.y = vehicleList[iVe].mY;
		SDL_RenderCopy(renderer, curTexture, &sourceRect, &desRect);
		vehicleList[iVe].setV((level / 3 + vehicleList[iVe].default_v) * (vLane[vehicleList[iVe].lane].light.getState() != RED));
		vehicleList[iVe].move();
		vehicleList[iVe].mX %= max_lane_size;
	}
	return;
}

void CGAME::TrafficLight_Load(){
	//lane format : pixel 100-200 400-500 700-800
	// traffic format 100-32, 400-32, 700-32
	SDL_Rect sourceRect, desRect;
	SDL_QueryTexture(trafficlightTexture, NULL, NULL, &sourceRect.w, &sourceRect.h);
	sourceRect.w /= 4;
	for (int i = 0; i < nLane; i++) {
		switch (vLane[i].light.getState()) {
		case RED: {
			sourceRect.x = 0;
			sourceRect.y = 0;
			break;
		}
		case YELLOW: {
			sourceRect.x = 32;
			sourceRect.y = 0;
			break;
		}
		case GREEN: {
			sourceRect.x = 64;
			sourceRect.y = 0;
			break;
		}
		case OFF: {
			sourceRect.x = 96;
			sourceRect.y = 0;
			break;
		}
		default:
			break;
		}
		vLane[i].light.incFrame();
		if (vLane[i].light.getFrame() == 0) {
			vLane[i].light.CountDown();
		}
		desRect.w = desRect.h = 32;
		desRect.x = 0;
		desRect.y = lanePixel[i] - 32;
		SDL_RenderCopy(renderer, trafficlightTexture, &sourceRect, &desRect);
	}
	return;
}

int CGAME::CheckState() {
	int pxl, pyl, pxr, pyr;
	pxl = player.getmX() + 50;
	pxr = player.getmX() - 50 + 110;
	pyl = player.getmY() + 20;
	pyr = player.getmY() - 20 + 110;
	for (int iVe = 0; iVe < vehicleList.size(); iVe++) {
		if (pxl >= vehicleList[iVe].mX && pxl <= vehicleList[iVe].mX + vehicleList[iVe].sX
			&& pyl >= vehicleList[iVe].mY && pyl <= vehicleList[iVe].mY + vehicleList[iVe].sY) {
			player.mState = 0;
			//player = CPEOPLE();
			return -1;
		}
		if (pxr >= vehicleList[iVe].mX && pxr <= vehicleList[iVe].mX + vehicleList[iVe].sX
			&& pyr >= vehicleList[iVe].mY && pyr <= vehicleList[iVe].mY + vehicleList[iVe].sY) {
			player.mState = 0;
			//player = CPEOPLE();
			return -1;
		}
		if (pxl >= vehicleList[iVe].mX && pxl <= vehicleList[iVe].mX + vehicleList[iVe].sX
			&& pyr >= vehicleList[iVe].mY && pyr <= vehicleList[iVe].mY + vehicleList[iVe].sY) {
			player.mState = 0;
			//player = CPEOPLE();
			return -1;
		}
		if (pxr >= vehicleList[iVe].mX && pxr <= vehicleList[iVe].mX + vehicleList[iVe].sX
			&& pyl >= vehicleList[iVe].mY && pyl <= vehicleList[iVe].mY + vehicleList[iVe].sY) {
			player.mState = 0;
			//player = CPEOPLE();
			return-1;
		}
	}
	if (pyl < 0) {
		return 1;
	}
	return 0;
}

void CGAME::drawGame(){
	std::cerr << "NEW GAME LEVEL" << level << "\n";
	while (isRunning) {
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		Background_Load();
		Vehicle_Load();
		TrafficLight_Load();
		People_Load(player.flip + player.animation_flip);
		int gameState = CheckState();
		if (gameState != 0) {
			isRunning = 0;
			if (gameState < 0) {
				level = -1;
			}
			else {
				++level;
			}
		}
		while (SDL_PollEvent(&mainEvent)) {
			switch (mainEvent.type) {
			case SDL_QUIT: {
				isRunning = 0;
				break;
			}
			case SDL_KEYDOWN: {
				++player.animation_flip;
				player.animation_flip %= 3;
				switch (mainEvent.key.keysym.sym) {
				case SDLK_ESCAPE: {
					level = -1;
					isRunning = 0;
					break;
				}
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

}

void CGAME::playGame(){
	SDL_Event gameEvent;
	bool running = 1;
	int userChoice = -1, curChoice = 0;
	while (running) {
		std::cerr << userChoice << " " << curChoice << "\n";
		SDL_RenderClear(renderer);
		Menu_Load(curChoice);
		while (SDL_PollEvent(&gameEvent)) {
			switch (gameEvent.type) {
			case SDL_KEYDOWN: {
				switch (gameEvent.key.keysym.sym) {
				case SDLK_ESCAPE: {
					running = 0;
					break;
				}
				case SDLK_UP: {
					--curChoice;
					curChoice = max(curChoice, 0);
					break;
				}
				case SDLK_DOWN: {
					++curChoice;
					curChoice = min(curChoice, 3);
					break;
				}
				case SDLK_RETURN: {
					userChoice = curChoice;
					break;
				}
				default:
					break;
				}
			}
			}
		}
		SDL_RenderPresent(renderer);
		switch (userChoice) {
		case (0):
			level = rand() % 3;
			while (level != -1) {
				Init();
				drawGame();
			}
			curChoice = 0;
			userChoice = -1;
			break;
		default:
			break;
		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
}

