#pragma once

class BaseObj
{
private:
	
protected:
	int x, y;
	HWND hwnd;

public:
	BaseObj(int, int);
	~BaseObj();
	void moveWindow(int, int);
	int getX();
	int getY();
	HWND getHWND();

	virtual HWND create(HWND) = 0;
};