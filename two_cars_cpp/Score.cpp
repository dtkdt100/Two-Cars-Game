#include <Windows.h>
#include <String>
#include <iostream>
#include "Score.h"
#include "Line.h"
#include "const.h"

Score::Score():BaseObj(srartX, srartY), score(0)
{
}

Score::~Score() 
{
}

Score::Score(int x, int y, int startScore):BaseObj(x, y), score(score)
{
}

void Score::increaseScore(HWND p) 
{
	this->score++;
	update(p);
}

int Score::getScore()
{
	return this->score;
}

void Score::reset(HWND p)
{
	this->score = 0;
	update(p);
}

void Score::paint(HDC hdc) {
	wchar_t buffer[256];
	wsprintfW(buffer, L"%d", this->score);

	HFONT hFont = CreateFont(
		scoreSize, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, scoreFont);
	

	
	SelectObject(hdc, hFont);	
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, scoreColor);
	TextOut(hdc, this->x, this->y, buffer, wcslen(buffer));
	DeleteObject(hFont);
	
}



void Score::update(HWND p) 
{
	InvalidateRect(p, NULL, TRUE);
	UpdateWindow(p);
	RedrawWindow(p, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

HWND Score::create(HWND parentHwnd) {
	return NULL;
}