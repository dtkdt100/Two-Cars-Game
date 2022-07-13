#pragma once
#include "BaseObj.h"

const int srartX = 10;
const int srartY = 10;
const int scoreSize = 50;
const COLORREF scoreColor = RGB(255, 255, 255);
const LPCTSTR scoreFont = L"Agency FB Bold";

class Score : public BaseObj {
public:
	Score();
	~Score();
	Score(int, int, int);
	void reset(HWND);
	int getScore();
	HWND create(HWND);
	void paint(HDC hdc);
	void increaseScore(HWND);
private:
	void update(HWND);
	int score;
};