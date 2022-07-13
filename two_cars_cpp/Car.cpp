#include <Windows.h>
#include "Car.h"
#include "const.h"
#include "ResourcePathUtils.h"

Car::Car(): BaseObj(0, 0), isLeft(true), isInLeftPlace(0) {}


Car::Car(int x, int y, bool startLeft): BaseObj(x, y), isLeft(startLeft), isInLeftPlace(startLeft) {}

Car Car::getGameCar(HWND p, bool isLeft)
{
    Car c = Car(isLeft ? startCarLeft : startCarRight, windowHeight / 1.3, isLeft);
    c.create(p);
    return c;
}

HWND Car::create(HWND parentHwnd) {
    this->hwnd = CreateWindow(L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_BITMAP, x, y, carWidth, carHeight, parentHwnd, (HMENU)0, NULL, NULL);
    HBITMAP hBitmap = (HBITMAP)LoadImageA(NULL, isLeft ? ResourcePathUtils::getCarPath(2).c_str() : ResourcePathUtils::getCarPath(1).c_str(), IMAGE_BITMAP, carWidth, carHeight, LR_LOADFROMFILE);
    SendMessage(this->hwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
    return this->hwnd;
}

void Car::moveLeft() {
    if (!this->isInLeftPlace) {
        this->moveWindow(-movePixels, 0);
        this->isInLeftPlace = true;
    }
}

void Car::moveRight() {
    if (this->isInLeftPlace) {
        this->moveWindow(movePixels, 0);
        this->isInLeftPlace = false;
    }
}