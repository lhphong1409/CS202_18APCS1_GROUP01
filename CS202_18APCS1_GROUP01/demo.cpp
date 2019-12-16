#include"TEMPLATE.h"
#include "CGAME.h"


// init SDL



// test


void testIngame() {
	PlaySound("musicgame.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC | SND_LOOP);
	CGAME game;
	game.playGame();
}

void testPeople() {

}

int main() {
	testIngame();
	return 0;
}
