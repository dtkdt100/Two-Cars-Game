#include <Windows.h>
#include "const.h"
#include "MainWindow.h"

MainWindow::MainWindow(): BaseObj(CW_USEDEFAULT, CW_USEDEFAULT)
{
}

MainWindow::~MainWindow()
{
}

HWND MainWindow::create(HWND n) 
{
    this->hwnd = CreateWindow(
        g_szClassName,
        L"TWO CARS",
        WS_OVERLAPPEDWINDOW,
        this->x, this->y,
        windowWidth, windowHeight,
        NULL,
        NULL,
        NULL,
        0);
    return this->hwnd;
}

void MainWindow::show(int nCmdShow) 
{
    this->centerWindow();
	ShowWindow(this->hwnd, nCmdShow);
	UpdateWindow(this->hwnd);
}

void MainWindow::centerWindow()
{
    int screen_w = GetSystemMetrics(SM_CXSCREEN);
    int screen_h = GetSystemMetrics(SM_CYSCREEN);
    SetWindowPos(this->hwnd, HWND_TOP, (screen_w - windowWidth) / 2,
        (screen_h - windowHeight) / 2, 0, 0, SWP_NOSIZE);
}

WNDCLASSEX MainWindow::registerClassEx(WNDPROC MainWindowWndProc)
{
    WNDCLASSEX wc = { sizeof(wc) };
    wc.style = 0;
    wc.lpfnWndProc = MainWindowWndProc;
    wc.hbrBackground = CreateSolidBrush(backgourndColor);
    wc.lpszClassName = g_szClassName;
    RegisterClassEx(&wc);
    return wc;
}