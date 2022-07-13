#include <Windows.h>
#include "Line.h"
#include "const.h"

Line::Line() : BaseObj(0, 0) 
{

}

Line::~Line()
{

}

Line::Line(int x, int th): BaseObj(x, 0), thickness(th)
{
	
}

HWND Line::create(HWND parentHwnd) {
	return NULL;
}

void Line::paint(HDC hdc) {
	HBRUSH hBrush1;
	HGDIOBJ holdBrush;
	hBrush1 = CreateSolidBrush(linesColor);
	holdBrush = SelectObject(hdc, hBrush1);
	Rectangle(hdc, x, 0,x+thickness, windowHeight);
	SelectObject(hdc, holdBrush);
	DeleteObject(hBrush1);
}

void Line::paintThreeLineForGame(HDC hdc) 
{
	HBRUSH hBrush1;
	HGDIOBJ holdBrush;
	hBrush1 = CreateSolidBrush(linesColor);
	holdBrush = SelectObject(hdc, hBrush1);
	Rectangle(hdc, windowWidth / 2 - 7.5, 0, windowWidth / 2 - 2.5, windowHeight);
	Rectangle(hdc, windowWidth / 4 - 4.5, 0, windowWidth / 4 - 1.5, windowHeight);
	Rectangle(hdc, windowWidth / 4 * 3 - 9, 0, windowWidth / 4 * 3 - 6, windowHeight);
	SelectObject(hdc, holdBrush);
	DeleteObject(hBrush1);
}