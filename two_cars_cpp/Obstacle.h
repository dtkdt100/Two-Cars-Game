#pragma once
#include "BaseObj.h"
#include "const.h"

const int obsWidth = 45;
const int obsHeight = 45;
const int movePixelsObs = 105;
const int startAfterReset = 50;
const int distanceBetweenObs = windowHeight / numberOfObsInSide;

const int startObsLeft = 26;
const int startObsRight = 220;


class Obstacle : public BaseObj
{
public:
	Obstacle();
	~Obstacle();
	Obstacle(int, int, bool, HWND);
	Obstacle(int, HWND);
	HWND create(HWND);
	bool checkReset();
	void restartObs();
	bool gainedPoint(bool, bool*), isSqr;

private:
	bool isLeft, isInLeftPlace, carTouched = false;
	std::string getImagePath() const;
	void initObs(HWND);
};
