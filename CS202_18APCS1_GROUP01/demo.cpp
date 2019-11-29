#include "CGAME.h"

CGAME game;

void testDraw() {
	std::cout << "#DEMO 01 - Test Draw from CGAME\n\n";
	game.drawGame();
	std::cout << "\n#END DEMO 01\n\n";
}
int main() {
	srand(time(NULL));
	game = CGAME(3);
	while (1) {
		system("cls");
		testDraw();
		Sleep(1000);
	}
	system("pause");
}
