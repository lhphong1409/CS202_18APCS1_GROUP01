#include "CGAME.h"

CGAME game;

void testDraw() {
	srand(time(NULL));
	autoConfig();
	game = CGAME();
	while (1) 
	{
		system("cls");
		std::cout << "#DEMO 01 - Test Draw from CGAME\n\n";
		game.drawGame();
		if (GetAsyncKeyState(VK_ESCAPE)) {
			break;
		}
		Sleep(1000);
	}
	std::cout << "\n#END DEMO 01\n\n";
}
int main() {
	testDraw();
	system("pause");
}
