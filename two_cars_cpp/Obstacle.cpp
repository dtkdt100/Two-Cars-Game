#include <Windows.h>
#include <iostream>
#include "Obstacle.h"
#include <random>
#include "ResourcePathUtils.h"


int randomNum(int lNum, int hNum) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(lNum, hNum);
	return dist(gen);
}

Obstacle::Obstacle(): BaseObj(0, 0), isSqr(true), isLeft(true) , isInLeftPlace(true)
{

};

Obstacle::~Obstacle() 
{

};

Obstacle::Obstacle(int index, HWND p): BaseObj(index%2 ? startObsLeft : startObsRight,
	-startAfterReset - (index / 2) * distanceBetweenObs), isLeft(index % 2)
{
	this->initObs(p);
}

Obstacle::Obstacle(int x, int y, bool isL, HWND p): BaseObj(x, y), isLeft(isL)
{	
	this->initObs(p);
};

void Obstacle::initObs(HWND p)
{
	this->isSqr = randomNum(0, 1);;
	bool startLeft = randomNum(0, 1);
	if (!startLeft) {
		this->moveWindow(movePixelsObs, 0);
	}
	this->isInLeftPlace = startLeft;
	this->create(p);
}

bool Obstacle::gainedPoint(bool isCarLeft, bool* runGame) {
	if (!this->carTouched) {
		if (this->y >= windowHeight / 1.3 - 45) {
			if (this->isInLeftPlace == isCarLeft) {
				this->carTouched = true;
				if (this->y <= windowHeight / 1.3 + 40) {
					if (!this->isSqr) {
						SetWindowPos(this->hwnd, HWND_TOP, this->x, this->y, 0, 0, SWP_NOMOVE);
						return true;
					}
					*runGame = false;
					return false;
				}
			}
		}
		if (!this->isSqr) {
			if (this->y >= windowHeight / 1.3 + 40) {
				if (!this->isSqr) {
					*runGame = false;
				}
			}

		}
		return false;
	}
	return false;
}

std::string Obstacle::getImagePath() const{
	if (this->isLeft) {
		if (this->isSqr) return ResourcePathUtils::getSqrPath(2);
		return ResourcePathUtils::getCirPath(2);
	}
	else {
		if (this->isSqr) return ResourcePathUtils::getSqrPath(1);
		return ResourcePathUtils::getCirPath(1);
	}
}

void Obstacle::restartObs() {
	SetWindowPos(this->hwnd, HWND_TOP, this->x, this->y, obsWidth, obsHeight, SWP_NOMOVE);
	if (randomNum(0, 1) == 0) {
		this->moveWindow(0, -windowHeight-startAfterReset);
	}
	else if (this->isInLeftPlace) {
		this->moveWindow(movePixelsObs, -windowHeight-startAfterReset);
		this->isInLeftPlace = false;
	}
	else {
		this->moveWindow(-movePixelsObs, -windowHeight-startAfterReset);
		this->isInLeftPlace = true;
	}
	if (randomNum(0, 1) == true) {
		this->isSqr = !this->isSqr;
		HBITMAP hBitmap = (HBITMAP)LoadImageA(NULL, this->getImagePath().c_str(), IMAGE_BITMAP, obsWidth, obsHeight, LR_LOADFROMFILE);
		SendMessage(this->hwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
	}
	this->carTouched = false;
	
}

bool Obstacle::checkReset() {
	if (this->y >= 800) {
		this->restartObs();
		return true;
	}
	return false;
}


HWND Obstacle::create(HWND parentHwnd)
{
	this->hwnd = CreateWindow(L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_BITMAP, x, y, obsWidth, obsHeight, parentHwnd, (HMENU)0, NULL, NULL);
	HBITMAP hBitmap = (HBITMAP)LoadImageA(NULL, this->getImagePath().c_str(), IMAGE_BITMAP, obsWidth, obsHeight, LR_LOADFROMFILE);
	SendMessage(this->hwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
	return this->hwnd;
}

