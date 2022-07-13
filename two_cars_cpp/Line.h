#pragma once
#include "BaseObj.h"

const COLORREF linesColor = RGB(130, 153, 246);

class Line : public BaseObj
{
public:
	Line();
	~Line();
	Line(int, int);
	HWND create(HWND);
	void paint(HDC);
	void paintThreeLineForGame(HDC);
private:
	int thickness = 0;
};