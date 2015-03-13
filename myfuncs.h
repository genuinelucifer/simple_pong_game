#ifndef __MYFUNCS__H_
#define __MYFUNCS__H_

#include <irrklang/irrKlang.h>

#include "mytypes.h"

#include <windows.h>
#include <windowsx.h>



#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define GAME_SPEED  30           //  Increase it to slow down frame rate


#define WINDOW_WIDTH 560
#define WINDOW_HEIGHT 480

#define MAX_LEVELS  5

#define BALL_WIDTH  16
#define BALL_HEIGHT 16
#define BALL_SPEED_Y  8.0f

#define BAT_HEIGHT  12
#define BAT_WIDTH  150
#define BAT_SPEED  9.5f

#define BRICK_WIDTH  32
#define BRICK_HEIGHT 24
#define TOTAL_BRICKS 50

#define WELCOME_SPLASH_TIME  4500
#define END_SPLASH_TIME  2000


#define KEYDOWN(vk_code)  ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0 )
#define KEYUP(vk_code)  ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1 )

int My_PlaySound(char* filename);

int isdone();
void setdone(int);

HWND gethCurrentWindow();

HFONT CreateMyFont(int width,int height,int orientation=0);

void SplashWelcome();
TrueFalse SplashEnd();

void GameInit(HINSTANCE hinst,HWND hWindow);

void GameMain();

GameStates ShowControls(HDC hdc);

GameStates ShowCredits(HDC hdc);

GameStates ShowMenu(HDC hdc);

void SetupLevel();

GameStates Play_MainGame();

void GameQuit();

void setMousePos(int x,int y,TrueFalse lbtn);

#endif
