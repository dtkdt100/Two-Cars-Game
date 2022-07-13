#pragma once
#include "BaseObj.h"

const LPCWSTR g_szClassName = L"WinMain";

class MainWindow : public BaseObj
{
public:
	MainWindow();
	~MainWindow();
	HWND create(HWND);
	WNDCLASSEX registerClassEx(WNDPROC);
	void show(int);
	void centerWindow();
};