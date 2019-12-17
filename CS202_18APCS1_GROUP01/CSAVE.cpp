#include "CSAVE.h"

void CSAVE::Init() {
	std::cerr << "NEWGAME\n"; 
	isRunning = 1;
	vLane.clear();
	player.updatePos(800, 790);
	if (level < 0) {
		player.changeEffect(SHIELD, 0);
		player.changeEffect(SLOW, 0);
	}
	player.changeEffect(REDLIGHT, 0);
	vehicleList.clear();
	animalList.clear();
	effectList.clear();
	SetLane(0, 0);
	SetLane(1, 1);
	SetLane(2, 0);
	return;
}

void CSAVE::SetLane(int laneID, bool objectType) { // 0 : vehicle, 1 : animal
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
			animalList.push_back(CDINOSAUR(cur_pos, -5 + lanePixel[laneID], laneID));
			break;
		case OBJECT::CROCODILE:
			animalList.push_back(CCROCODILE(cur_pos, (90 - 56) + lanePixel[laneID], laneID));
			break;
		case OBJECT::HORSE:
			animalList.push_back(CHORSE(cur_pos, -5 + lanePixel[laneID], laneID));
			break;
		default:
			break;
		}
		if (!objectType)
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

int CSAVE::CheckState() {
	bool live = 1;
	int pxl, pyl, pxr, pyr;
	pxl = player.getmX() + 50;
	pxr = player.getmX() - 50 + 110;
	pyl = player.getmY() + 20;
	pyr = player.getmY() - 20 + 110;
	int iVeDel = -1, iAniDel = -1;
	for (int iVe = 0; iVe < vehicleList.size(); iVe++) {
		if (pxl >= vehicleList[iVe].mX && pxl <= vehicleList[iVe].mX + vehicleList[iVe].sX
			&& pyl >= vehicleList[iVe].mY && pyl <= vehicleList[iVe].mY + vehicleList[iVe].sY) {
			iVeDel = iVe;
			live = 0;
			break;
		}
		if (pxr >= vehicleList[iVe].mX && pxr <= vehicleList[iVe].mX + vehicleList[iVe].sX
			&& pyr >= vehicleList[iVe].mY && pyr <= vehicleList[iVe].mY + vehicleList[iVe].sY) {
			iVeDel = iVe;
			player.mState = 0;
			live = 0;
			break;
		}
		if (pxl >= vehicleList[iVe].mX && pxl <= vehicleList[iVe].mX + vehicleList[iVe].sX
			&& pyr >= vehicleList[iVe].mY && pyr <= vehicleList[iVe].mY + vehicleList[iVe].sY) {
			iVeDel = iVe;
			player.mState = 0;
			live = 0;
			break;
		}
		if (pxr >= vehicleList[iVe].mX && pxr <= vehicleList[iVe].mX + vehicleList[iVe].sX
			&& pyl >= vehicleList[iVe].mY && pyl <= vehicleList[iVe].mY + vehicleList[iVe].sY) {
			iVeDel = iVe;
			player.mState = 0;
			live = 0;
			break;
		}
	}
	for (int iVe = 0; iVe < animalList.size(); iVe++) {
		if (pxl >= animalList[iVe].mX && pxl <= animalList[iVe].mX + animalList[iVe].sX
			&& pyl >= animalList[iVe].mY && pyl <= animalList[iVe].mY + animalList[iVe].sY) {
			iAniDel = iVe;
			live = 0;
			break;
		}
		if (pxr >= animalList[iVe].mX && pxr <= animalList[iVe].mX + animalList[iVe].sX
			&& pyr >= animalList[iVe].mY && pyr <= animalList[iVe].mY + animalList[iVe].sY) {
			iAniDel = iVe;
			player.mState = 0;
			live = 0;
			break;
		}
		if (pxl >= animalList[iVe].mX && pxl <= animalList[iVe].mX + animalList[iVe].sX
			&& pyr >= animalList[iVe].mY && pyr <= animalList[iVe].mY + animalList[iVe].sY) {
			iAniDel = iVe;
			player.mState = 0;
			live = 0;
			break;
		}
		if (pxr >= animalList[iVe].mX && pxr <= animalList[iVe].mX + animalList[iVe].sX
			&& pyl >= animalList[iVe].mY && pyl <= animalList[iVe].mY + animalList[iVe].sY) {
			iAniDel = iVe;
			player.mState = 0;
			live = 0;
			break;
		}
	}
	if (effectList.size() > 0)
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
			player.changeEffect(SHIELD, 0);
			if (iVeDel >= 0)
				vehicleList.erase(vehicleList.begin() + iVeDel);
			if (iAniDel >= 0)
				animalList.erase(animalList.begin() + iAniDel);
			return 0;
		}
		return -1;
	}
	return 0;
} // need to update
