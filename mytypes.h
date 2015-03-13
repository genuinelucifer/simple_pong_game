#ifndef __MYTYPES__H_
#define __MYTYPES__H_

typedef enum tagGameErrors
{
    GE_NO_ERROR                      =  0,
    GE_CLASS_NOT_REGISTERED          =  22,
    GE_WINDOW_NOT_CREATED            =  23,
    GE_FULLSCREEN_NOT_AVAILABLE      =  24,
    GE_SOUND_ENGINE_NOT_CREATED      =  25

}GameErrors;

typedef enum tagTrueFalse
{
    MY_FALSE =0,
    MY_TRUE  =1
}TrueFalse;

typedef struct tagBat
{
    int  posx;           /* x co-ord of the Bat   */
    float  curx;
    float  speedx;                 /* speed of the bat right/left (+/- speed)    */

}Bat;


typedef struct tagBall
{
    int posx,posy;      /* x and y co-ords of the Bat   */
    float curx, cury;
    float speedx, speedy;           /* speed of the ball leftright(+/- speed) and up/down (+/- speed)   */

}Ball;


typedef struct tagBricks
{
    int x,y;
    int color;               /* 1 = red,  2 = blue 3 = green */
    TrueFalse isliving;
}Bricks;

typedef enum tagGameStates
{
   GSMenu           = 1,
   GSPlaying        = 2,
   GSControls       = 3,
   GSCredits        = 4,
   GSSplashWelcome  = 5

}GameStates;


#endif

