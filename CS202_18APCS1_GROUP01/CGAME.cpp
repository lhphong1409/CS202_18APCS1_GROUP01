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
	vLane.clear();
	player.updatePos(800, 790);
	//player.changeEffect(SHIELD, 0);
	//player.changeEffect(SLOW, 0);
	player.changeEffect(REDLIGHT, 0);
	vehicleList.clear();
	animalList.clear();
	effectList.clear();
	SetLane(0, 0);
	SetLane(1, 1);
	SetLane(2, 0);
}

void CGAME::SetLane(int laneID, bool objectType){ // 0 : vehicle, 1 : animal
	//lane format : pixel 100-200 400-500 700-800
	vLane.push_back(laneType());
	int cur_pos = rand() % vehicle_dis;
	while (cur_pos + vehicle_dis + vehicle_dis <= max_lane_size) {
		OBJECT cur_type = static_cast<OBJECT>(rand() % (3) + 3 * objectType);
		switch (cur_type) {
		case OBJECT::CAR:
			vehicleList.push_back(CCAR(cur_pos, lanePixel[laneID], laneID));
			break;
		case OBJECT::BUS:
			vehicleList.push_back(CBUS(cur_pos, lanePixel[laneID], laneID));
			break;
		case OBJECT::TRUCK:
			vehicleList.push_back(CTRUCK(cur_pos, lanePixel[laneID], laneID));
			break;
		case OBJECT::DINOSAUR:
			animalList.push_back(CDINOSAUR(cur_pos, -5 +lanePixel[laneID], laneID));
			break;
		case OBJECT::CROCODILE:
			animalList.push_back(CCROCODILE(cur_pos, (90-56) + lanePixel[laneID], laneID));
			break;
		case OBJECT::HORSE:
			animalList.push_back(CHORSE(cur_pos, -5 + lanePixel[laneID], laneID));
			break;
		default:
			break;
		}
		if(!objectType)
			cur_pos += vehicleList.back().sX + rand() % vehicle_dis + vehicle_dis;
		else {
			cur_pos += animalList.back().sX + rand() % animal_dis + animal_dis;
		}
		//std::cout << vehicleList.back().type << "\n";
	}

	bool spawnEffect = (rand() % 100) < 25;
	if (spawnEffect) {
		effectList.push_back(CEFFECT(rand() % 1500 + 10, lanePixel[laneID], laneID));
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

void CGAME::TextureLoad() {
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

	for (int i = 0; i < 9; i++) {
		numberTexture[i] = loadTexture(image_number[i]);
	}
	for (int i = 0; i < 4; i++) {
		dinosaurTexture[i] = loadTexture(image_animals_dinosaur[i]);
		crocodileTexture[i] = loadTexture(image_animals_crocodile[i]);
		horseTexture[i] = loadTexture(image_animals_horse[i]);
	}

	for (int i = 0; i < 3; i++) {
		effectTexture[i] = loadTexture(image_effect[i]);
	}
	return;
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
	if (frame == 0) {
		player.countdownEffect();
	}
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

void CGAME::Effect_Load() {
	SDL_Rect sourceRect, desRect;
	sourceRect.x = sourceRect.y = 0;
	desRect.w = sourceRect.w = 80;
	desRect.h = sourceRect.h = 80;
	for (int i = 0; i < effectList.size(); i++) {
		desRect.x = effectList[i].mX;
		desRect.y = effectList[i].mY;
		if (frame % (FPS / 6) == 0) { // EFFECT ANIMATION
			effectList[i].mY += 4;
			if (effectList[i].mY > lanePixel[effectList[i].lane] + 20) {
				effectList[i].mY = lanePixel[effectList[i].lane];
			}
		}
		SDL_RenderCopy(renderer, effectTexture[effectList[i].type], &sourceRect, &desRect);
	}
	desRect.x = player.getmX()+15;
	desRect.y = player.getmY()+15;

	if (player.getEffect(SHIELD)) {
		std::wcerr<<"SHIELD: "  << desRect.x << " " << desRect.y << "\n";
		SDL_RenderCopy(renderer, effectTexture[EFFECT::SHIELD], &sourceRect, &desRect);
	}
	if (player.getEffect(SLOW)) {
		std::wcerr <<"SLOW "<< desRect.x << " " << desRect.y << "\n";
		SDL_RenderCopy(renderer, effectTexture[EFFECT::SLOW], &sourceRect, &desRect);
	}
}

void CGAME::Vehicle_Load(){
	SDL_Rect sourceRect, desRect;
	SDL_Texture *curTexture;
	for (int iVe = 0; iVe < vehicleList.size(); iVe++) {
		switch (vehicleList[iVe].type){
		case OBJECT::BUS:
			curTexture = busTexture;
			break;
		case OBJECT::TRUCK:
			curTexture = truckTexture;
			break;
		case OBJECT::CAR:
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
		vehicleList[iVe].setV((level / 3 + vehicleList[iVe].default_v) * (vLane[vehicleList[iVe].lane].light.getState() != RED) / (1 + player.getEffect(SLOW)));
		vehicleList[iVe].move();
		vehicleList[iVe].mX %= max_lane_size;
	}
	return;
}

void CGAME::Animals_Load() {
	SDL_Rect sourceRect, desRect;
	SDL_Texture* curTexture;
	for (int iAni = 0; iAni < animalList.size(); iAni++) {
		switch (animalList[iAni].type) {
		case OBJECT::DINOSAUR:
			curTexture = dinosaurTexture[animalList[iAni].anima];
			break;
		case OBJECT::CROCODILE: 
			curTexture = crocodileTexture[animalList[iAni].anima];
			break;
		case OBJECT::HORSE:
			curTexture = horseTexture[animalList[iAni].anima];
			break;

		default:
			curTexture = dinosaurTexture[animalList[iAni].anima];
			break;
		}
		SDL_QueryTexture(curTexture, NULL, NULL, &sourceRect.w, &sourceRect.h);
		sourceRect.x = sourceRect.y = 0;
		desRect.w = sourceRect.w;
		desRect.h = sourceRect.h;
		desRect.x = animalList[iAni].mX;
		desRect.y = animalList[iAni].mY;
		SDL_RenderCopy(renderer, curTexture, &sourceRect, &desRect);
		animalList[iAni].setV((level / 3 + animalList[iAni].default_v) / (1 + player.getEffect(SLOW)));
		animalList[iAni].move();
		//std::cerr << "anima : " << animalList[iAni].anima << " frame:" << frame << "\n";
		if (frame % (FPS / 6) == 0) {
			++animalList[iAni].anima;
			animalList[iAni].anima %= 4;
		}
		animalList[iAni].mX %= max_lane_size;
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
		if (frame == 0) {
			vLane[i].light.CountDown();
		}
		desRect.w = desRect.h = 32;
		desRect.x = 0;
		desRect.y = lanePixel[i] - 32;
		SDL_RenderCopy(renderer, trafficlightTexture, &sourceRect, &desRect);
		if (vLane[i].light.getState() == OFF)
			continue;
		desRect.x = 32;
		sourceRect.x = sourceRect.y = 0;
		SDL_RenderCopy(renderer, numberTexture[vLane[i].light.getTime()], &sourceRect, &desRect);
	}
	return;
}

int CGAME::CheckState() {
	bool live = 1;
	int pxl, pyl, pxr, pyr;
	pxl = player.getmX() + 50;
	pxr = player.getmX() - 50 + 110;
	pyl = player.getmY() + 20;
	pyr = player.getmY() - 20 + 110;
	for (int iVe = 0; iVe < vehicleList.size(); iVe++) {
		if (pxl >= vehicleList[iVe].mX && pxl <= vehicleList[iVe].mX + vehicleList[iVe].sX
			&& pyl >= vehicleList[iVe].mY && pyl <= vehicleList[iVe].mY + vehicleList[iVe].sY) {
			live = 0;
			break;
		}
		if (pxr >= vehicleList[iVe].mX && pxr <= vehicleList[iVe].mX + vehicleList[iVe].sX
			&& pyr >= vehicleList[iVe].mY && pyr <= vehicleList[iVe].mY + vehicleList[iVe].sY) {
			player.mState = 0;
			live = 0;
			break;
		}
		if (pxl >= vehicleList[iVe].mX && pxl <= vehicleList[iVe].mX + vehicleList[iVe].sX
			&& pyr >= vehicleList[iVe].mY && pyr <= vehicleList[iVe].mY + vehicleList[iVe].sY) {
			player.mState = 0;
			live = 0;
			break;
		}
		if (pxr >= vehicleList[iVe].mX && pxr <= vehicleList[iVe].mX + vehicleList[iVe].sX
			&& pyl >= vehicleList[iVe].mY && pyl <= vehicleList[iVe].mY + vehicleList[iVe].sY) {
			player.mState = 0;
			live = 0;
			break;
		}
	}
	for (int iVe = 0; iVe < animalList.size(); iVe++) {
		if (pxl >= animalList[iVe].mX && pxl <= animalList[iVe].mX + animalList[iVe].sX
			&& pyl >= animalList[iVe].mY && pyl <= animalList[iVe].mY + animalList[iVe].sY) {
			live = 0;
			break;
		}
		if (pxr >= animalList[iVe].mX && pxr <= animalList[iVe].mX + animalList[iVe].sX
			&& pyr >= animalList[iVe].mY && pyr <= animalList[iVe].mY + animalList[iVe].sY) {
			player.mState = 0;
			live = 0;
			break;
		}
		if (pxl >= animalList[iVe].mX && pxl <= animalList[iVe].mX + animalList[iVe].sX
			&& pyr >= animalList[iVe].mY && pyr <= animalList[iVe].mY + animalList[iVe].sY) {
			player.mState = 0;
			live = 0;
			break;
		}
		if (pxr >= animalList[iVe].mX && pxr <= animalList[iVe].mX + animalList[iVe].sX
			&& pyl >= animalList[iVe].mY && pyl <= animalList[iVe].mY + animalList[iVe].sY) {
			player.mState = 0;
			live = 0;
			break;
		}
	}
	if(effectList.size() > 0)	
		for (int iEff = effectList.size() - 1; iEff >= 0; iEff--) {
			if (pxl >= effectList[iEff].mX && pxl <= effectList[iEff].mX + effectList[iEff].sX
				&& pyl >= effectList[iEff].mY && pyl <= effectList[iEff].mY + effectList[iEff].sY) {
				player.changeEffect(effectList[iEff].type, 10);
				effectList.erase(effectList.begin() + iEff);
				break;
			}
			if (pxr >= effectList[iEff].mX && pxr <= effectList[iEff].mX + effectList[iEff].sX
				&& pyr >= effectList[iEff].mY && pyr <= effectList[iEff].mY + effectList[iEff].sY) {
				player.changeEffect(effectList[iEff].type, 10);
				effectList.erase(effectList.begin() + iEff);
				break;
			}
			if (pxl >= effectList[iEff].mX && pxl <= effectList[iEff].mX + effectList[iEff].sX
				&& pyr >= effectList[iEff].mY && pyr <= effectList[iEff].mY + effectList[iEff].sY) {
				player.changeEffect(effectList[iEff].type, 10);
				effectList.erase(effectList.begin() + iEff);
				break;
			}
			if (pxr >= effectList[iEff].mX && pxr <= effectList[iEff].mX + effectList[iEff].sX
				&& pyl >= effectList[iEff].mY && pyl <= effectList[iEff].mY + effectList[iEff].sY) {
				player.changeEffect(effectList[iEff].type, 10);
				effectList.erase(effectList.begin() + iEff);
				break;
			}
		}
	if (player.getEffect(REDLIGHT)) {
		for (int i = 0; i < nLane; i++)
			vLane[i] = laneType(RED);
		player.changeEffect(REDLIGHT, 0);
	}
	if (pyl < 0) {
		player.changeEffect(REDLIGHT, 0);
		return 1;
	}
	if (!live) {
		if (player.getEffect(SHIELD)) {
			player.changeEffect(SHIELD, 2);
			return 0;
		}
		return -1;
	}
	return 0;
} // need to update

void CGAME::drawGame(){
	std::cerr << "NEW GAME LEVEL" << level << " " << effectList.size() << "\n";
	while (isRunning) {
		std::cerr << player.getEffect(EFFECT::SHIELD) << " ";
		std::cerr << "\n";
		++frame;
		frame %= FPS;
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		Background_Load();
		People_Load(player.flip + player.animation_flip);
		Effect_Load();
		Vehicle_Load();
		Animals_Load();
		TrafficLight_Load();


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
		SDL_Delay(1000 / FPS);
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

