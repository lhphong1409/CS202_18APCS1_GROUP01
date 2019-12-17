#include "CGAME.h"
CGAME::CGAME(){
	srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	window = SDL_CreateWindow("CrossRoad-Group-01.exe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	loadGame();
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

	peopleTexture = loadTexture(image_people[characterID]);
	trafficlightTexture = loadTexture(image_trafficlight);

	saveTexture[0] = loadTexture(image_save[0]);
	saveTexture[1] = loadTexture(image_save[1]);

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

	for (int i = 0; i < 12; i++) {
		loadiTexture[i] = loadTexture(image_load[i]);
	}

	for (int i = 0; i < 14; i++) {
		optionTexture[i] = loadTexture(image_option[i]);
	}
	aboutTexture = loadTexture(image_about);
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
		curSave.player.countdownEffect();
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
	desRect.x = curSave.player.getmX();
	desRect.y = curSave.player.getmY();
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
	SDL_QueryTexture(backgroundTexture[curSave.level%3], NULL, NULL, &sourceRect.w, &sourceRect.h);
	sourceRect.x = sourceRect.y = desRect.x = desRect.y = 0;
	desRect.w = sourceRect.w;
	desRect.h = sourceRect.h;
	SDL_RenderCopy(renderer, backgroundTexture[curSave.level%3], &sourceRect, &desRect);
	std::string leadingZero = "";
	if (curSave.level < 10) {
		leadingZero = "0";
	}
	Text_Load("level " + leadingZero + std::to_string(curSave.level), 1350, 15);
	return;
}

void CGAME::Effect_Load() {
	SDL_Rect sourceRect, desRect;
	sourceRect.x = sourceRect.y = 0;
	desRect.w = sourceRect.w = 80;
	desRect.h = sourceRect.h = 80;
	for (int i = 0; i < curSave.effectList.size(); i++) {
		desRect.x = curSave.effectList[i].mX;
		desRect.y = curSave.effectList[i].mY;
		if (frame % (FPS / 6) == 0) { // EFFECT ANIMATION
			curSave.effectList[i].mY += 4;
			if (curSave.effectList[i].mY > lanePixel[curSave.effectList[i].lane] + 20) {
				curSave.effectList[i].mY = lanePixel[curSave.effectList[i].lane];
			}
		}
		SDL_RenderCopy(renderer, effectTexture[curSave.effectList[i].type], &sourceRect, &desRect);
	}
	desRect.x = curSave.player.getmX()+15;
	desRect.y = curSave.player.getmY()+15;

	if (curSave.player.getEffect(SHIELD)) {
		std::wcerr<<"SHIELD: "  << desRect.x << " " << desRect.y << "\n";
		SDL_RenderCopy(renderer, effectTexture[EFFECT::SHIELD], &sourceRect, &desRect);
	}
	if (curSave.player.getEffect(SLOW)) {
		std::wcerr <<"SLOW "<< desRect.x << " " << desRect.y << "\n";
		SDL_RenderCopy(renderer, effectTexture[EFFECT::SLOW], &sourceRect, &desRect);
	}
}

void CGAME::Vehicle_Load(){
	SDL_Rect sourceRect, desRect;
	SDL_Texture *curTexture;
	for (int iVe = 0; iVe < curSave.vehicleList.size(); iVe++) {
		switch (curSave.vehicleList[iVe].type){
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
		desRect.x = curSave.vehicleList[iVe].mX;
		desRect.y = curSave.vehicleList[iVe].mY;
		SDL_RenderCopy(renderer, curTexture, &sourceRect, &desRect);
		curSave.vehicleList[iVe].setV((curSave.level / 3 + curSave.vehicleList[iVe].default_v) * (curSave.vLane[curSave.vehicleList[iVe].lane].light.getState() != RED) / (1 + curSave.player.getEffect(SLOW)));
		curSave.vehicleList[iVe].move();
		curSave.vehicleList[iVe].mX %= max_lane_size;
	}
	return;
}

void CGAME::Animals_Load() {
	SDL_Rect sourceRect, desRect;
	SDL_Texture* curTexture;
	for (int iAni = 0; iAni < curSave.animalList.size(); iAni++) {
		switch (curSave.animalList[iAni].type) {
		case OBJECT::DINOSAUR:
			curTexture = dinosaurTexture[curSave.animalList[iAni].anima];
			break;
		case OBJECT::CROCODILE: 
			curTexture = crocodileTexture[curSave.animalList[iAni].anima];
			break;
		case OBJECT::HORSE:
			curTexture = horseTexture[curSave.animalList[iAni].anima];
			break;

		default:
			curTexture = dinosaurTexture[curSave.animalList[iAni].anima];
			break;
		}
		SDL_QueryTexture(curTexture, NULL, NULL, &sourceRect.w, &sourceRect.h);
		sourceRect.x = sourceRect.y = 0;
		desRect.w = sourceRect.w;
		desRect.h = sourceRect.h;
		desRect.x = curSave.animalList[iAni].mX;
		desRect.y = curSave.animalList[iAni].mY;
		SDL_RenderCopy(renderer, curTexture, &sourceRect, &desRect);
		curSave.animalList[iAni].setV((curSave.level / 3 + curSave.animalList[iAni].default_v) / (1 + curSave.player.getEffect(SLOW)));
		curSave.animalList[iAni].move();
		//std::cerr << "anima : " << curSave.animalList[iAni].anima << " frame:" << frame << "\n";
		if (frame % (FPS / 6) == 0) {
			++curSave.animalList[iAni].anima;
			curSave.animalList[iAni].anima %= 4;
		}
		curSave.animalList[iAni].mX %= max_lane_size;
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
		switch (curSave.vLane[i].light.getState()) {
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
			curSave.vLane[i].light.CountDown();
		}
		desRect.w = desRect.h = 32;
		desRect.x = 0;
		desRect.y = lanePixel[i] - 32;
		SDL_RenderCopy(renderer, trafficlightTexture, &sourceRect, &desRect);
		if (curSave.vLane[i].light.getState() == OFF)
			continue;
		desRect.x = 32;
		sourceRect.x = sourceRect.y = 0;
		SDL_RenderCopy(renderer, numberTexture[curSave.vLane[i].light.getTime()], &sourceRect, &desRect);
	}
	return;
}

void CGAME::Save_Load(int curChoice){
	SDL_Rect sourceRect, desRect;
	SDL_QueryTexture(saveTexture[curChoice], NULL, NULL, &sourceRect.w, &sourceRect.h);
	sourceRect.x = sourceRect.y = desRect.x = desRect.y = 0;
	desRect.w = sourceRect.w;
	desRect.h = sourceRect.h;
	desRect.x = 400;
	desRect.y = 225;
	SDL_RenderCopy(renderer, saveTexture[curChoice], &sourceRect, &desRect);
	return ;
}

void CGAME::Load_Load(int curChoice){
	SDL_Rect sourceRect, desRect;
	int showList = (curChoice / 4) * 4;
	if (curChoice >= ((saveImage.size() / 4 * 4)))
		curChoice = curChoice % 4 + 8;
	else {
		if(curChoice >= 4)
			curChoice = curChoice % 4 + 4;
	}
	SDL_QueryTexture(loadiTexture[curChoice], NULL, NULL, &sourceRect.w, &sourceRect.h);
	desRect.h = sourceRect.h;
	desRect.w = sourceRect.w;
	desRect.x = desRect.y = sourceRect.x = sourceRect.y = 0;
	SDL_RenderCopy(renderer, loadiTexture[curChoice], &sourceRect, &desRect);
	for (int i = showList; i < min(showList + 4, saveImage.size()); i++) {
		SDL_QueryTexture(saveImage[i], NULL, NULL, &sourceRect.w, &sourceRect.h);
		sourceRect.x = sourceRect.y = 0;
		desRect.w = sourceRect.w / 5 - 10;
		desRect.h = sourceRect.h / 5 - 10;

		switch (i % 4) {
		case(0):
			desRect.x = 112;
			desRect.y = 366;
			break;
		case(1):
			desRect.x = 466;
			desRect.y = 366;
			break;
		case(2):
			desRect.x = 823;
			desRect.y = 366;
			break;
		case(3):
			desRect.x = 1178;
			desRect.y = 366;
			break;
		default:
			break;
		}
		SDL_RenderCopy(renderer, saveImage[i], &sourceRect, &desRect);
	}
	return;
}

void CGAME::Option_Load(int curChoice){
	SDL_Rect sourceRect, desRect;
	SDL_QueryTexture(optionTexture[curChoice], NULL, NULL, &sourceRect.w, &sourceRect.h);
	sourceRect.x = sourceRect.y = desRect.x = desRect.y = 0;
	desRect.w = sourceRect.w;
	desRect.h = sourceRect.h;
	SDL_RenderCopy(renderer, optionTexture[curChoice], &sourceRect, &desRect);
	return;
}

void CGAME::About_Load(){
	SDL_Rect sourceRect, desRect;
	SDL_QueryTexture(aboutTexture, NULL, NULL, &sourceRect.w, &sourceRect.h);
	sourceRect.x = sourceRect.y = desRect.x = desRect.y = 0;
	desRect.w = sourceRect.w;
	desRect.h = sourceRect.h;
	bool running = 1;
	SDL_Event gameEvent;
	while (running) {
		SDL_RenderCopy(renderer, aboutTexture, &sourceRect, &desRect);
		while (SDL_PollEvent(&gameEvent)) {
			switch (gameEvent.type) {
			case SDL_KEYDOWN: {
				switch (gameEvent.key.keysym.sym) {
				case SDLK_ESCAPE: {
					running = 0;
					return;
				}
				default:
					break;
				}
			}
			}
		}
		SDL_RenderPresent(renderer);
	}
}

bool CGAME::userSaveChoice(){
	SDL_Event gameEvent;
	bool running = 1;
	int userChoice = -1, curChoice = 0;
	while (running) {
		Save_Load(curChoice);
		while (SDL_PollEvent(&gameEvent)) {
			switch (gameEvent.type) {
			case SDL_KEYDOWN: {
				switch (gameEvent.key.keysym.sym) {
				case SDLK_ESCAPE: {
					running = 0;
					return 1;
					break;
				}
				case SDLK_RIGHT: {
					--curChoice;
					curChoice = max(curChoice, 0);
					break;
				}
				case SDLK_LEFT: {
					++curChoice;
					curChoice = min(curChoice, 1);
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
			return 0;
			break;
		case (1): {
			return 1;
			break;
		}
		default:
			break;
		}
	}
	return false;
}

int CGAME::getIdgame(){
	SDL_Event gameEvent;
	bool running = 1;
	int userChoice = -1, curChoice = 0;
	while (running) {
		Load_Load(curChoice);
		while (SDL_PollEvent(&gameEvent)) {
			switch (gameEvent.type) {
			case SDL_KEYDOWN: {

				switch (gameEvent.key.keysym.sym) {
				case SDLK_ESCAPE: {
					running = 0;
					return -1;
					break;
				}
				case SDLK_LEFT: {
					if (saveList.empty())
						break;
					--curChoice;
					curChoice = max(curChoice, 0);
					break;
				}
				case SDLK_RIGHT: {
					if (saveList.empty())
						break;
					++curChoice;
					curChoice = min(curChoice, saveImage.size()-1);
					break;
				}
				case SDLK_RETURN: {
					if (saveList.empty())
						break;
					return curChoice;
					break;
				}
				case SDLK_DELETE: {
					if (saveList.empty())
						break;
					saveList.erase(saveList.begin() + curChoice);
					saveImage.erase(saveImage.begin() + curChoice);
					curChoice = min(curChoice, saveList.size() - 1);
					curChoice = max(curChoice, 0);
					saveGame();
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
			return 0;
			break;
		case (1): {
			return 1;
			break;
		}
		default:
			break;
		}
	}
	return false;
}

void CGAME::getCharMusic(){
	SDL_Event gameEvent;
	bool running = 1;
	int userChoice = -1, curChoice;
	curChoice = 9 * (1 - Sound) + characterID + 1;
	while (running) {
		std::cerr << characterID << " " << Sound << "\n";
		Option_Load(curChoice);
		while (SDL_PollEvent(&gameEvent)) {
			switch (gameEvent.type) {
			case SDL_KEYDOWN: {
				switch (gameEvent.key.keysym.sym) {
				case SDLK_ESCAPE: {
					running = 0;
					break;
				}
				case SDLK_LEFT: {
					switch (curChoice) {
					case(1):
						--curChoice;
						break;
					case(2):
						--curChoice;
						break;
					case(3):
						--curChoice;
						break;
					case(4):
						--curChoice;
						break;
					case(6): {
						curChoice = 5;
						break;
					}
					case(7): {
						curChoice = 8;
						break;
					}
					case(10):
						--curChoice;
						break;
					
					case(11):
						--curChoice;
						break;
					case(12):
						--curChoice;
						break;
					case(13):
						--curChoice;
						break;
					default:
						break;
					}
					break;
				}
				case SDLK_RIGHT: {
					switch (curChoice) {
					case(0):
						++curChoice;
						break;
					case(1):
						++curChoice;
						break;
					case(2):
						++curChoice;
						break;
					case(3):
						++curChoice;
						break;
					case(5):
						++curChoice;
						break;
					case(8):
						curChoice = 7;
						break;
					case(9):
						++curChoice;
						break;
					case(10):
						++curChoice;
						break;
					case(11):
						++curChoice;
						break;
					case(12):
						++curChoice;
						break;
					default:
						break;
					}
					break;
				}
				case SDLK_UP: {
					switch (curChoice) {
					case(5):
						curChoice = 0;
						break;
					case(8):
						curChoice = 9;
						break;
					default:
						break;
					}
					break;
				}
				case SDLK_DOWN: {
					switch (curChoice) {
					case(0):
						curChoice = 5;
						break;
					case(9):
						curChoice = 8;
						break;
					default:
						break;
					}
					break;
				}
				case SDLK_RETURN: {
					if (curChoice == 6)
						curChoice = 7;
					else if (curChoice == 7)
						curChoice = 6;
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
		case(0):
			break;
		case(1):
			characterID = 0;
			Sound = 1;
			break;
		case(2):
			characterID = 1;
			Sound = 1;
			break;
		case(3):
			characterID = 2;
			Sound = 1;
			break;
		case(4):
			characterID = 3;
			Sound = 1;
			break;
		case(5):
			break;
		case(6):
			Sound = 1;
			break;
		case(7):
			Sound = 0;
			break;
		case(8):
			break;
		case(9):
			break;
		case(10):
			characterID = 0;
			Sound = 0;
			break;
		case(11):
			characterID = 1;
			Sound = 0;
			break;
		case(12):
			characterID = 2;
			Sound = 0;
			break;
		case(13):
			characterID = 3;
			Sound = 0;
			break;
		default:
			break;
		}
	}
	peopleTexture = loadTexture(image_people[characterID]);

}

void CGAME::saveGame(){
	std::ofstream(out);
	out.open(text_save);
	out << saveList.size() << "\n";
	for (int i = 0; i < saveList.size(); i++) {
		out << saveList[i].level << "\n";
		out << saveList[i].vehicleList.size() << "\n";
		for (int iVe = 0; iVe < saveList[i].vehicleList.size(); iVe++) {
			out << saveList[i].vehicleList[iVe].type << " " << saveList[i].vehicleList[iVe].mX << " " << saveList[i].vehicleList[iVe].mY << " " << saveList[i].vehicleList[iVe].lane << "\n";
		}
		out << saveList[i].animalList.size() << "\n";
		for (int iAni = 0; iAni < saveList[i].animalList.size(); iAni++) {
			out << saveList[i].animalList[iAni].type << " " << saveList[i].animalList[iAni].mX << " " << saveList[i].animalList[iAni].mY << " " << saveList[i].animalList[iAni].lane << "\n";
		}
		out << saveList[i].effectList.size() << "\n";
		for (int iEff = 0; iEff < saveList[i].effectList.size(); iEff++) {
			out << saveList[i].effectList[iEff].type << " " << saveList[i].effectList[iEff].mX << " " << saveList[i].effectList[iEff].mY << " " << saveList[i].effectList[iEff].lane << "\n";
		}
		out << saveList[i].vLane.size() << "\n";
		for (int iLan = 0; iLan < saveList[i].vLane.size(); iLan++) {
			out << saveList[i].vLane[iLan].light.getTime() << " " << saveList[i].vLane[iLan].light.getState() << "\n";
		}
		out << saveList[i].player.getmX() << " " << saveList[i].player.getmY() << " ";
		for (int iState = 0; iState < 3; iState++) {
			out << saveList[i].player.getTimeEffect(iState) << " ";
		}
		out << "\n";
		out << saveList[i].path;
		out << "\n";
	}
	out.close();
}

void CGAME::loadGame() {
	std::ifstream(inp);
	inp.open(text_save);
	int saveSize = 0, objSize = 0, objType;
	inp >> saveSize ;
	for (int i = 0; i < saveSize; i++) {
		saveList.push_back(CSAVE());
		inp >> saveList[i].level;
		inp >> objSize;
		for (int iVe = 0; iVe < objSize; iVe++) {
			inp >> objType;
			switch (objType) {
			case (OBJECT::BUS):
				saveList[i].vehicleList.push_back(CBUS(0, 0, 0));
				break;
			case (OBJECT::CAR):
				saveList[i].vehicleList.push_back(CCAR(0, 0, 0));
				break;
			case (OBJECT::TRUCK):
				saveList[i].vehicleList.push_back(CTRUCK(0, 0, 0));
				break;
			default:
				break;
			}
			inp >> saveList[i].vehicleList[iVe].mX >> saveList[i].vehicleList[iVe].mY >> saveList[i].vehicleList[iVe].lane;
			saveList[i].vehicleList[iVe].type = OBJECT(objType);
		}
		inp >> objSize;
		for (int iAni = 0; iAni < objSize; iAni++) {
			inp >> objType;
			switch (objType) {
			case (OBJECT::CROCODILE):
				saveList[i].animalList.push_back(CCROCODILE(0, 0, 0));
				break;
			case (OBJECT::DINOSAUR):
				saveList[i].animalList.push_back(CDINOSAUR(0, 0, 0));
				break;
			case (OBJECT::HORSE):
				saveList[i].animalList.push_back(CHORSE(0, 0, 0));
				break;
			default:
				break;
			}
			inp >> saveList[i].animalList[iAni].mX >> saveList[i].animalList[iAni].mY >> saveList[i].animalList[iAni].lane;
			saveList[i].animalList[iAni].type = OBJECT(objType);
		}
		inp >> objSize;
		for (int iEff = 0; iEff < objSize; iEff++) {
			saveList[i].effectList.push_back(CEFFECT());
			inp >> objType >> saveList[i].effectList[iEff].mX   >> saveList[i].effectList[iEff].mY   >> saveList[i].effectList[iEff].lane  ;
			saveList[i].effectList[iEff].type = EFFECT(objType);
		}
		inp >> objSize;
		for (int iLan = 0; iLan < objSize; iLan++) {
			saveList[i].vLane.push_back(laneType());
			int TIME = 0, STATE;
			inp >> TIME >> STATE;
			saveList[i].vLane[iLan].light.setTime(TIME);
			saveList[i].vLane[iLan].light.setState(LIGHTst(STATE));
		}
		inp >> saveList[i].player.mX >> saveList[i].player.mY ;
		for (int iState = 0; iState < 3; iState++) {
			int TIME;
			inp >> TIME  ;
			saveList[i].player.changeEffect(EFFECT(iState), TIME);
		}
		inp >> saveList[i].path;
		saveImage.push_back(loadTexture(saveList[i].path));
	}
	inp.close();
}

void CGAME::drawGame(){
	std::cerr << "DRAW " << curSave.isRunning << "\n";
	while (curSave.isRunning) {
		++frame;
		frame %= FPS;
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		Background_Load();
		People_Load(curSave.player.flip + curSave.player.animation_flip);
		Effect_Load();
		Vehicle_Load();
		Animals_Load();
		TrafficLight_Load();

		int gameState = curSave.CheckState();
		if (gameState != 0) {
			curSave.isRunning = 0;
			if (gameState < 0) {
				curSave.level = -1;
				PlaySound("music/collision/collision1.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
			}
			else {
				++curSave.level;
			}
		}
		while (SDL_PollEvent(&mainEvent)) {
			switch (mainEvent.type) {
			case SDL_QUIT: {
				curSave.isRunning = 0;
				break;
			}
			case SDL_KEYDOWN: {
				++curSave.player.animation_flip;
				curSave.player.animation_flip %= 3;
				switch (mainEvent.key.keysym.sym) {
				case SDLK_ESCAPE: {
					curSave.path = "save/image/" + std::to_string(saveList.size()) + ".bmp";
					saveList.push_back(curSave);
					screenShot(curSave.path);
					saveImage.push_back(loadTexture(curSave.path));
					saveGame();
					if (!userSaveChoice()) {
						curSave.level = -1;
						curSave.isRunning = 0;
					}
					
					break;
				}
				case SDLK_UP: {
					curSave.player.up();
					curSave.player.flip = 0;
					break;
				}
				case SDLK_DOWN: {
					curSave.player.down();
					curSave.player.flip = 3;
					break;
				}
				case SDLK_LEFT: {
					curSave.player.left();
					curSave.player.flip = 6;
					break;
				}
				case SDLK_RIGHT: {
					curSave.player.right();
					curSave.player.flip = 9;
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
	int cnt = 0;
	std::cerr << saveList.size() << "\n";
	SDL_Event gameEvent;
	bool running = 1;
	int userChoice = -1, curChoice = 0;
	while (running) {
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
			curSave = CSAVE();
			while (curSave.level > -1) {
				curSave.Init();
				drawGame();
			} 
			curChoice = 0;
			userChoice = -1;
			break;
		case (1): {
			PlaySound("music/musicgame/musicgame.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC | SND_LOOP);
			idGame = getIdgame();
			if (idGame == -1) {
				curChoice = 0;
				userChoice = -1;
				break;
			}
			curSave = saveList[idGame];
			cnt = 0;
			while (curSave.level != -1) {
				if (cnt)
					curSave.Init();
				drawGame();
				++cnt;
			}
			curChoice = 0;
			userChoice = -1;
			break;
		}
		case(2): {
			getCharMusic();
			curChoice = 0;
			userChoice = -1;
			break;
		}
		case(3): {
			About_Load();
			curChoice = 0;
			userChoice = -1;
			break;
		}
		default:

			break;
		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
}

