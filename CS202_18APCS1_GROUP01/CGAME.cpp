#include "CGAME.h"
CGAME::CGAME(){
	srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	window = SDL_CreateWindow("CrossRoad-Group-01.exe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// lane : 10 x 180:
	// set for CCAR
	TextureLoad();

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

void CGAME::screenShot(std::string savePath){
	std::cout << "Screen Ok\n" << savePath << "\n";
	SDL_Surface *sshot = SDL_CreateRGBSurface(0, 1600, 900, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
	SDL_SaveBMP(sshot, savePath.c_str());
	SDL_FreeSurface(sshot);

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
		saveList[idGame].player.countdownEffect();
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
	desRect.x = saveList[idGame].player.getmX();
	desRect.y = saveList[idGame].player.getmY();
	desRect.w = sourceRect.w = animateSize;
	desRect.h = sourceRect.h = animateSize;
	SDL_RenderCopy(renderer, peopleTexture, &sourceRect, &desRect);
}

void CGAME::Text_Load(const std::string Text, const int dX, const int dY) {
	TTF_Font* font = TTF_OpenFont("font/PressStart2P.ttf", 30);
	SDL_Color fg = { 200, 29, 109 };
	SDL_Surface* surface = TTF_RenderText_Solid(font, Text.c_str(), fg);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	SDL_Rect srcRest;
	SDL_Rect desRect;
	TTF_SizeText(font, Text.c_str(), &srcRest.w, &srcRest.h);
	srcRest.x = 0;
	srcRest.y = 0;

	desRect.x = dX;
	desRect.y = dY;

	desRect.w = srcRest.w;
	desRect.h = srcRest.h;
	SDL_RenderCopy(renderer, texture, &srcRest, &desRect);
	return;
}

void CGAME::Background_Load() {
	SDL_Rect sourceRect, desRect;
	SDL_QueryTexture(backgroundTexture[saveList[idGame].level%3], NULL, NULL, &sourceRect.w, &sourceRect.h);
	sourceRect.x = sourceRect.y = desRect.x = desRect.y = 0;
	desRect.w = sourceRect.w;
	desRect.h = sourceRect.h;
	SDL_RenderCopy(renderer, backgroundTexture[saveList[idGame].level%3], &sourceRect, &desRect);
	std::string leadingZero = "";
	if (saveList[idGame].level < 10) {
		leadingZero = "0";
	}
	Text_Load("level " + leadingZero + std::to_string(saveList[idGame].level), 1350, 15);
	return;
}

void CGAME::Effect_Load() {
	SDL_Rect sourceRect, desRect;
	sourceRect.x = sourceRect.y = 0;
	desRect.w = sourceRect.w = 80;
	desRect.h = sourceRect.h = 80;
	for (int i = 0; i < saveList[idGame].effectList.size(); i++) {
		desRect.x = saveList[idGame].effectList[i].mX;
		desRect.y = saveList[idGame].effectList[i].mY;
		if (frame % (FPS / 6) == 0) { // EFFECT ANIMATION
			saveList[idGame].effectList[i].mY += 4;
			if (saveList[idGame].effectList[i].mY > lanePixel[saveList[idGame].effectList[i].lane] + 20) {
				saveList[idGame].effectList[i].mY = lanePixel[saveList[idGame].effectList[i].lane];
			}
		}
		SDL_RenderCopy(renderer, effectTexture[saveList[idGame].effectList[i].type], &sourceRect, &desRect);
	}
	desRect.x = saveList[idGame].player.getmX()+15;
	desRect.y = saveList[idGame].player.getmY()+15;

	if (saveList[idGame].player.getEffect(SHIELD)) {
		std::wcerr<<"SHIELD: "  << desRect.x << " " << desRect.y << "\n";
		SDL_RenderCopy(renderer, effectTexture[EFFECT::SHIELD], &sourceRect, &desRect);
	}
	if (saveList[idGame].player.getEffect(SLOW)) {
		std::wcerr <<"SLOW "<< desRect.x << " " << desRect.y << "\n";
		SDL_RenderCopy(renderer, effectTexture[EFFECT::SLOW], &sourceRect, &desRect);
	}
}

void CGAME::Vehicle_Load(){
	SDL_Rect sourceRect, desRect;
	SDL_Texture *curTexture;
	for (int iVe = 0; iVe < saveList[idGame].vehicleList.size(); iVe++) {
		switch (saveList[idGame].vehicleList[iVe].type){
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
		desRect.x = saveList[idGame].vehicleList[iVe].mX;
		desRect.y = saveList[idGame].vehicleList[iVe].mY;
		SDL_RenderCopy(renderer, curTexture, &sourceRect, &desRect);
		saveList[idGame].vehicleList[iVe].setV((saveList[idGame].level / 3 + saveList[idGame].vehicleList[iVe].default_v) * (saveList[idGame].vLane[saveList[idGame].vehicleList[iVe].lane].light.getState() != RED) / (1 + saveList[idGame].player.getEffect(SLOW)));
		saveList[idGame].vehicleList[iVe].move();
		saveList[idGame].vehicleList[iVe].mX %= max_lane_size;
	}
	return;
}

void CGAME::Animals_Load() {
	SDL_Rect sourceRect, desRect;
	SDL_Texture* curTexture;
	for (int iAni = 0; iAni < saveList[idGame].animalList.size(); iAni++) {
		switch (saveList[idGame].animalList[iAni].type) {
		case OBJECT::DINOSAUR:
			curTexture = dinosaurTexture[saveList[idGame].animalList[iAni].anima];
			break;
		case OBJECT::CROCODILE: 
			curTexture = crocodileTexture[saveList[idGame].animalList[iAni].anima];
			break;
		case OBJECT::HORSE:
			curTexture = horseTexture[saveList[idGame].animalList[iAni].anima];
			break;

		default:
			curTexture = dinosaurTexture[saveList[idGame].animalList[iAni].anima];
			break;
		}
		SDL_QueryTexture(curTexture, NULL, NULL, &sourceRect.w, &sourceRect.h);
		sourceRect.x = sourceRect.y = 0;
		desRect.w = sourceRect.w;
		desRect.h = sourceRect.h;
		desRect.x = saveList[idGame].animalList[iAni].mX;
		desRect.y = saveList[idGame].animalList[iAni].mY;
		SDL_RenderCopy(renderer, curTexture, &sourceRect, &desRect);
		saveList[idGame].animalList[iAni].setV((saveList[idGame].level / 3 + saveList[idGame].animalList[iAni].default_v) / (1 + saveList[idGame].player.getEffect(SLOW)));
		saveList[idGame].animalList[iAni].move();
		//std::cerr << "anima : " << saveList[idGame].animalList[iAni].anima << " frame:" << frame << "\n";
		if (frame % (FPS / 6) == 0) {
			++saveList[idGame].animalList[iAni].anima;
			saveList[idGame].animalList[iAni].anima %= 4;
		}
		saveList[idGame].animalList[iAni].mX %= max_lane_size;
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
		switch (saveList[idGame].vLane[i].light.getState()) {
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
			saveList[idGame].vLane[i].light.CountDown();
		}
		desRect.w = desRect.h = 32;
		desRect.x = 0;
		desRect.y = lanePixel[i] - 32;
		SDL_RenderCopy(renderer, trafficlightTexture, &sourceRect, &desRect);
		if (saveList[idGame].vLane[i].light.getState() == OFF)
			continue;
		desRect.x = 32;
		sourceRect.x = sourceRect.y = 0;
		SDL_RenderCopy(renderer, numberTexture[saveList[idGame].vLane[i].light.getTime()], &sourceRect, &desRect);
	}
	return;
}

void CGAME::saveGame(){
	std::fstream(out);
	out.open(text_save);
	for (int i = 0; i < saveList.size(); i++) {
		out << saveList.size() << "\n";
		out << saveList[i].level << "\n";
		out << saveList[i].vehicleList.size() << "\n";
		for (int iVe = 0; iVe < saveList[i].vehicleList.size(); iVe++) {
			out << saveList[i].vehicleList[iVe].type << " " << saveList[i].vehicleList[iVe].mX << " " << saveList[i].vehicleList[iVe].mY << " " << saveList[i].vehicleList[iVe].lane << "\n";
		}
		for (int iAni = 0; iAni < saveList[i].animalList.size(); iAni++) {
			out << saveList[i].animalList[iAni].type << " " << saveList[i].animalList[iAni].mX << " " << saveList[i].animalList[iAni].mY << " " << saveList[i].animalList[iAni].lane << "\n";
		}
		for (int iEff = 0; iEff < saveList[i].effectList.size(); iEff++) {
			out << saveList[i].effectList[iEff].type << " " << saveList[i].effectList[iEff].mX << " " << saveList[i].effectList[iEff].mY << " " << saveList[i].effectList[iEff].lane << "\n";
		}
		for (int iLan = 0; iLan < saveList[i].vLane.size(); iLan++) {
			out << saveList[i].vLane[iLan].light.getTime() << " " << saveList[i].vLane[iLan].light.getState() << "\n";
		}
		out << saveList[i].player.getmX() << " " << saveList[i].player.getmY() << " ";
		for (int iState = 0; iState < 3; iState++) {
			out << saveList[i].player.getTimeEffect(iState) << " ";
		}
		out << saveList[i].path;
		out << "\n";
	}
	out.close();
}

void CGAME::drawGame(){
	screenShot("save/image/1.bmp");
	while (saveList[idGame].isRunning) {
		++frame;
		frame %= FPS;
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		Background_Load();
		People_Load(saveList[idGame].player.flip + saveList[idGame].player.animation_flip);
		Effect_Load();
		Vehicle_Load();
		Animals_Load();
		TrafficLight_Load();

		int gameState = saveList[idGame].CheckState();
		if (gameState != 0) {
			saveList[idGame].isRunning = 0;
			if (gameState < 0) {
				saveList[idGame].level = -1;
			}
			else {
				++saveList[idGame].level;
			}
		}
		while (SDL_PollEvent(&mainEvent)) {
			switch (mainEvent.type) {
			case SDL_QUIT: {
				saveList[idGame].isRunning = 0;
				break;
			}
			case SDL_KEYDOWN: {
				++saveList[idGame].player.animation_flip;
				saveList[idGame].player.animation_flip %= 3;
				switch (mainEvent.key.keysym.sym) {
				case SDLK_ESCAPE: {
					saveList[idGame].level = -1;
					saveList[idGame].isRunning = 0;
					break;
				}
				case SDLK_UP: {
					saveList[idGame].player.up();
					saveList[idGame].player.flip = 0;
					break;
				}
				case SDLK_DOWN: {
					saveList[idGame].player.down();
					saveList[idGame].player.flip = 3;
					break;
				}
				case SDLK_LEFT: {
					saveList[idGame].player.left();
					saveList[idGame].player.flip = 6;
					break;
				}
				case SDLK_RIGHT: {
					saveList[idGame].player.right();
					saveList[idGame].player.flip = 9;
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
					PlaySound("music/select/select.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
					--curChoice;
					curChoice = max(curChoice, 0);
					break;
				}
				case SDLK_DOWN: {
					PlaySound("music/select/select.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
					++curChoice;
					curChoice = min(curChoice, 3);
					break;
				}
				case SDLK_RETURN: {
					PlaySound("music/enter/enter.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
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
			PlaySound("music/musicgame/musicgame.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC | SND_LOOP);
			saveList.push_back(CSAVE());
			idGame = saveList.size() - 1;
			while (saveList.back().level != -1) {
				saveList.back().Init();
				drawGame();
			}
			if (saveList.size() > 0 && saveList.back().level == -1) {
				saveList.pop_back();
				PlaySound("music/collision/collision1.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
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

