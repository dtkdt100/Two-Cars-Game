#pragma once
#include "BaseObj.h"
#include "const.h"

const int carWidth = 45;
const int carHeight = 90;
const int movePixels = 96;

const int startCarLeft = windowWidth / 4 - carWidth * 1.7;
const int startCarRight = startCarLeft + windowWidth/4*3;

class Car : public BaseObj
{
public:
	Car();
	Car(int, int, bool);
	HWND create(HWND);
	void moveLeft();
	void moveRight();
	bool isInLeftPlace = true;
	static Car getGameCar(HWND, bool);
	
private:
	bool isLeft;
};