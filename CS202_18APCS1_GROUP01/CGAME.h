#ifndef _CGAME_H
#define _CGAME_H

#include "TEMPLATE.h"
#include "DATA.h"
#include "CONFIG.h"
class CGAME {
private:
	std::vector<laneType> vLane;
	std::vector<std::string> boardGame;
	//boardGame[i*5][j] = row i col j
public:
	CGAME(const int &nLine);
	CGAME();
	void drawGame();
};
#endif
