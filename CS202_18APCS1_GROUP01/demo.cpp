#include "CGAME.h"

CGAME game;

void testDraw() {
	std::cout << "#DEMO 01 - Test Draw from CGAME\n\n";
	game.drawGame();
	std::cout << "\n#END DEMO 01\n\n";
}
int main() {
	srand(time(NULL));
	autoConfig();
	game = CGAME(7);
	while (1) {
		system("cls");
		testDraw();
		if (GetAsyncKeyState(VK_ESCAPE)) {
			break;
		}
		Sleep(1000);
	}
	system("pause");
}
