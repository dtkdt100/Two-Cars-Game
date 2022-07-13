#include <Windows.h>
#include <iostream>
#include "BaseObj.h"

BaseObj::BaseObj(int x, int y): x(x), y(y), hwnd(NULL)
{

};

BaseObj::~BaseObj()
{

}

void BaseObj::moveWindow(int xMov, int yMov) {
    this->x += xMov;
    this->y += yMov;
    if (this->hwnd == NULL) return;
    RECT rc = { 0 };
    GetWindowRect(this->hwnd, &rc);
    int width1 = rc.right - rc.left;
    int height1 = rc.bottom - rc.top;
    MapWindowPoints(HWND_DESKTOP, GetParent(this->hwnd), (LPPOINT)&rc, 2);

    MoveWindow(
        this->hwnd,
        rc.left + xMov,
        rc.top + yMov,
        width1,
        height1,
        true);
}

int BaseObj::getX() {
    return this->x;
}

int BaseObj::getY() {
	return this->y;
}

HWND BaseObj::getHWND() {
	return this->hwnd;
}

