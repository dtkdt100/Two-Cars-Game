#pragma comment (lib, "winmm.lib") // Sound
#include <Windows.h>
#include <iostream>
#include <thread>
#include <mmsystem.h>
#include "Car.h"
#include "Line.h"
#include "const.h"
#include "Obstacle.h"
#include "Score.h"
#include "MainWindow.h"
#include "ResourcePathUtils.h"

bool runGame = false;

Car rightCar;
Car leftCar;
Score scoreBoard;
Obstacle obstacles[numberOfObsInSide * 2];
MainWindow windowInstance;
HANDLE gameThreadHandle;
Line lines;
int speed = startSpeed;

void updateSpeed() {
    if (speed != startSpeed + (scoreBoard.getScore() / updateSpeedFreq)) {
        speed = startSpeed + (scoreBoard.getScore() / updateSpeedFreq);
    }    
}

DWORD WINAPI gameThread(LPVOID lparam) {
    class Obstacle* obstacles = new class Obstacle[numberOfObsInSide*2];
    obstacles = (class Obstacle*)lparam;

    while (runGame) {

        for (int i = 0; i < numberOfObsInSide * 2; i++) {
            if (obstacles[i].gainedPoint(i%2!=0 ? leftCar.isInLeftPlace : rightCar.isInLeftPlace, &runGame)) {
                scoreBoard.increaseScore(windowInstance.getHWND());

			}
            obstacles[i].moveWindow(0, speed);
            obstacles[i].checkReset();
            
        }
        updateSpeed();
        Sleep(10);		
    }
    return 0;
}

void initialize(HWND hwnd) 
{
    rightCar = rightCar.getGameCar(hwnd, false);
    leftCar = leftCar.getGameCar(hwnd, true);
    for (int i = 0; i < numberOfObsInSide * 2; i++) {
        obstacles[i] = Obstacle(i, hwnd);
    }
}

void paint(HWND hwnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    lines.paintThreeLineForGame(hdc);
    scoreBoard.paint(hdc);
    EndPaint(hwnd, &ps);
}

int destory() {
    PostQuitMessage(0);
    return 0;
}

void startGame() {
    if (!runGame) {
        gameThreadHandle = CreateThread(
            NULL,
            0,
            gameThread,
            obstacles,
            0,
            NULL
        );
        runGame = true;
    }
}

void resetGame() {
   if (!runGame) {
        scoreBoard.reset(windowInstance.getHWND());
        for (int i = 0; i < numberOfObsInSide * 2; i++) {
            obstacles[i].restartObs();
        }
        startGame();
    }
}

void pressP() {
	if (runGame) {
		runGame = false;
	}
    else {
		runGame = false;
        startGame();
    }
}

void keyDown(WPARAM wParam) {
    if (wParam == VK_LEFT) rightCar.moveLeft();
    if (wParam == VK_RIGHT) rightCar.moveRight();
    if (wParam == 'A') leftCar.moveLeft();
    if (wParam == 'D') leftCar.moveRight();
    if (wParam == 'R') resetGame();
    if (wParam == 'G' && gameThreadHandle == NULL) startGame();
    if (wParam == 'P') pressP();
    if (wParam == VK_ESCAPE) destory();
}

LRESULT CALLBACK FakeMenuDemo_WndProc(HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uiMsg)
    {
    case WM_KEYDOWN:
        keyDown(wParam);
		break;
    case WM_CREATE:
        PlaySoundA(ResourcePathUtils::getMusicPath().c_str(), NULL, SND_ASYNC | SND_LOOP);
        initialize(hwnd);
		break;
    case WM_PAINT:
        paint(hwnd);
        break;
    case WM_DESTROY:
        return destory();
    }

    return DefWindowProc(hwnd, uiMsg, wParam, lParam);
}

int WINAPI winMain(HINSTANCE hInstance, HINSTANCE , LPWSTR, int nCmdShow)
{
    windowInstance.registerClassEx(FakeMenuDemo_WndProc);
    windowInstance.create(NULL);
    windowInstance.show(nCmdShow);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

int main(void) 
{    
    winMain(GetModuleHandle(NULL), NULL, NULL, SW_SHOW);
    CloseHandle(gameThreadHandle);
    return 0;
}