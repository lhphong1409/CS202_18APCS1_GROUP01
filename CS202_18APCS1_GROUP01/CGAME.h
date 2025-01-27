#ifndef _CGAME_H
#define _CGAME_H

#include "CSAVE.h"

class CGAME {
private:
	std::vector<CSAVE> saveList;
	CSAVE curSave;
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Event mainEvent;
	SDL_Texture *carTexture = NULL;
	SDL_Texture* truckTexture = NULL;
	SDL_Texture* busTexture = NULL;
	SDL_Texture* dinosaurTexture[4];
	SDL_Texture* crocodileTexture[4];
	SDL_Texture* horseTexture[4];
	SDL_Texture* effectTexture[3];
	SDL_Texture *backgroundTexture[3];
	SDL_Texture *peopleTexture = NULL;
	SDL_Texture *trafficlightTexture = NULL;
	SDL_Texture *menuTexture[4];
	SDL_Texture *numberTexture[10];
	SDL_Texture *saveTexture[2];
	SDL_Texture *loadiTexture[12];
	SDL_Texture *optionTexture[14];
	SDL_Texture *aboutTexture = NULL;
	SDL_Texture* diedTexture[10];
	std::vector<SDL_Texture*> saveImage;
	int characterID = 1;
	bool Sound = 1;
	int idGame ;
	int frame = 0;
public:
	CGAME();
	SDL_Texture* loadTexture(std::string path);
	void screenShot(std::string savePath);
	void TextureLoad();
	void Text_Load(const std::string Text, const int dX, const int dY);
	void Menu_Load(int curChoice);
	void People_Load(const int animation);
	void Background_Load();
	void Effect_Load();
	void Vehicle_Load();
	void Animals_Load();
	void TrafficLight_Load();
	void Save_Load(int curChoice);
	void Load_Load(int curChoice);
	void Option_Load(int curChoice);
	void About_Load();
	void Died_Load();
	bool userSaveChoice();
	int getIdgame();
	void getCharMusic();
	void saveGame();
	void loadGame();
	void drawGame();
	void playGame();
};
#endif
