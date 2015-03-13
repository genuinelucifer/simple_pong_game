#include"myfuncs.h"



using namespace irrklang;

//      #pragma comment(lib, "irrKlang.lib")


ISoundEngine* se = NULL;

int My_PlaySound(char * filename)
{

	// Play some sound

	if(se->play2D(filename) != 0)
	{
		MessageBox(gethCurrentWindow(),"Couldn't play the file...","ERROR??",MB_ICONERROR);
		return 0;
	}

	return 1;

}



HPEN red_pen=CreatePen(PS_SOLID,1,RGB(255,0,0));
HPEN green_pen=CreatePen(PS_SOLID,1,RGB(0,255,0));
HPEN blue_pen=CreatePen(PS_SOLID,1,RGB(0,0,255));
HPEN black_pen=CreatePen(PS_SOLID,1,RGB(0,0,0));

HBRUSH red_brush=CreateSolidBrush(RGB(255,0,0));
HBRUSH black_brush=CreateSolidBrush(RGB(0,0,0));
HBRUSH green_brush=CreateSolidBrush(RGB(0,255,0));
HBRUSH blue_brush=CreateSolidBrush(RGB(0,0,255));



Bat global_curBat;
Ball global_curBall;
GameStates global_curState;

int done=0;

HWND  hCurrentWindow = NULL;
HINSTANCE hThisInstance = NULL;
HDC game_dc = NULL;

Bricks ALL_BRICKS[TOTAL_BRICKS];

DEVMODE game_screen;

int BricksLeft = TOTAL_BRICKS;
int Cur_Level = 0;



int isdone()
{
    return done;
}
void setdone(int i)
{
    done = i;
}
HWND gethCurrentWindow()
{
    return hCurrentWindow;
}

HFONT CreateMyFont(int width,int height,int orientation)
{
    return CreateFont(height,width,orientation,0,FW_NORMAL,FALSE,FALSE,FALSE,ANSI_CHARSET,
                      OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_ROMAN,
                      "Times New Roman");
}


void GameInit(HINSTANCE hinst,HWND hWindow)
{
    done =0;
    hThisInstance = hinst;
    hCurrentWindow = hWindow;

    se = createIrrKlangDevice();
	 // check for errors with creation
    	if(!se)
     	{
		MessageBox(gethCurrentWindow(),"Couldn't create sound engine...","ERROR??",MB_ICONERROR);
		exit(GE_SOUND_ENGINE_NOT_CREATED);
	    }
	    se->setSoundVolume(100);




    game_screen.dmSize = sizeof (game_screen);
    game_screen.dmPelsWidth=SCREEN_WIDTH;
    game_screen.dmPelsHeight=SCREEN_HEIGHT;
    game_screen.dmBitsPerPel=16;
    game_screen.dmFields= DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL ;
    if (ChangeDisplaySettings(&game_screen,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
	{
	    	MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By  Your Video Card...","Error!!!",MB_OK|MB_ICONERROR);
	    	exit(GE_FULLSCREEN_NOT_AVAILABLE);
	}


    global_curBat.posx = WINDOW_WIDTH/2;
    global_curBat.speedx = 0.0f;
    global_curBat.curx = (float) global_curBat.posx;

    global_curBall.posx = WINDOW_WIDTH/2;
    global_curBall.posy = WINDOW_HEIGHT - BAT_HEIGHT - (BALL_HEIGHT/2);
    global_curBall.curx = (float) global_curBall.posx;
    global_curBall.cury = (float) global_curBall.posy;
    global_curBall.speedx = 1.5f;
    global_curBall.speedy = 0;

    game_dc = GetDC(hCurrentWindow);

    global_curState = GSSplashWelcome;

}


GameStates ShowControls(HDC hdc)
{
    HFONT font=CreateMyFont(35,40);
    SetBkMode(game_dc,TRANSPARENT);

    SelectObject(game_dc,font);
    SetTextColor(game_dc,RGB(200,180,160));
    TextOut(game_dc,100,20,"PONG 2.0!",9);

    font=CreateMyFont(40,50);
    SelectObject(hdc,font);
    SetTextColor(hdc,RGB(120,50,20));
    TextOut(hdc,60,60,"CONTROLS",8);

    font=CreateMyFont(12,15);
    SelectObject(hdc,font);
    SetTextColor(hdc,RGB(150,160,82));
    TextOut(hdc,3,130,"*Use Left an Right arrow keys to move the bat.",45);
    TextOut(hdc,5,180,"*Use Esc to quit while playing.",30);

    font=CreateMyFont(10,12);
    SelectObject(hdc,font);
    SetTextColor(hdc,RGB(150,120,170));
    TextOut(hdc,8,405,"Click anywhere OR Press Spacebar to go back.",43);
    DeleteObject(font);
    if(KEYDOWN(VK_SPACE))
    {
        RECT myrect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
        FillRect(hdc,&myrect,black_brush);
        My_PlaySound((char*)"sounds\\whoah.mp3");
       return GSMenu;
    }
    return GSControls;

}

GameStates ShowCredits(HDC hdc)
{
    HFONT font=CreateMyFont(35,40);
    SetBkMode(game_dc,TRANSPARENT);

    SelectObject(game_dc,font);
    SetTextColor(game_dc,RGB(200,180,160));
    TextOut(game_dc,100,10,"PONG 2.0!",9);

    font=CreateMyFont(25,30);
    SelectObject(hdc,font);
    SetTextColor(game_dc,RGB(80,200,60));
    TextOut(hdc,10,130,"PROGRAMMER:",11);
    TextOut(hdc,10,250,"GRAPHICS DESIGNER:",18);

    font=CreateMyFont(30,35,45);
    SelectObject(hdc,font);
    SetTextColor(hdc,RGB(50,20,170));
    TextOut(hdc,250,180,"&",1);
    SetTextColor(hdc,RGB(250,50,70));
    TextOut(hdc,250,330,"Abhinav",7);

    font=CreateMyFont(35,40);
    SelectObject(hdc,font);
    SetTextColor(hdc,RGB(80,230,200));
    TextOut(hdc,100,70,"CREDITS",7);

    font=CreateMyFont(10,12);
    SelectObject(hdc,font);
    SetTextColor(hdc,RGB(150,120,170));
    TextOut(hdc,8,405,"Click anywhere OR Press Spacebar to go back.",43);

    DeleteObject(font);
    if(KEYDOWN(VK_SPACE))
    {
        RECT myrect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
        FillRect(hdc,&myrect,black_brush);
        My_PlaySound((char*)"sounds\\whoah.mp3");
       return GSMenu;
    }
    return GSCredits;
}

DWORD welcomestart = 0;
void SplashWelcome()
{
    if(welcomestart == 0)
       welcomestart = GetTickCount();
    HFONT font=CreateMyFont(35,40);
    SetBkMode(game_dc,TRANSPARENT);

    SelectObject(game_dc,font);
    SetTextColor(game_dc,RGB(200,180,160));
    TextOut(game_dc,100,20,"PONG 2.0!",9);

    font=CreateMyFont(35,40);
    SelectObject(game_dc,font);
    SetTextColor(game_dc,RGB(170,80,150));
    TextOut(game_dc,10,170,"Presented to You",16);
    TextOut(game_dc,50,210,"BY:",3);

    font=CreateMyFont(45,55,45);
    SelectObject(game_dc,font);
    SetTextColor(game_dc,RGB(250,50,70));
    TextOut(game_dc,200,300,"Abhinav",7);

    DeleteObject(font);

    if((GetTickCount()-welcomestart)>= WELCOME_SPLASH_TIME)
    {
        global_curState = GSMenu;
        My_PlaySound((char*)"sounds\\whoah.mp3");
        RECT myrect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
        FillRect(game_dc,&myrect,black_brush);
    }

}


DWORD endstart = 0;
TrueFalse SplashEnd()
{
     if(endstart == 0)
     {
         RECT myrect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
         FillRect(game_dc,&myrect,black_brush);
         endstart = GetTickCount();
     }


    HFONT font=CreateMyFont(35,40);
    SetBkMode(game_dc,TRANSPARENT);

    SelectObject(game_dc,font);
    SetTextColor(game_dc,RGB(200,180,160));
    TextOut(game_dc,100,20,"PONG 2.0!",9);

    font=CreateMyFont(28,35);
    SelectObject(game_dc,font);
    SetTextColor(game_dc,RGB(170,80,150));
    TextOut(game_dc,10,200,"Thanks For Playing...",21);

    DeleteObject(font);

    if((GetTickCount()-endstart)>= END_SPLASH_TIME)
    {
        return MY_TRUE;
    }
    return MY_FALSE;
}


void GameMain()
{
    switch(global_curState)
    {
        case GSSplashWelcome:
            SplashWelcome();
          break;
        case GSMenu :
          global_curState = ShowMenu(game_dc);
        break;

        break;
        case  GSPlaying :
            global_curState =  Play_MainGame();
          break;
        case GSCredits :
          global_curState = ShowCredits(game_dc);
          break;
        case GSControls :
         global_curState =  ShowControls(game_dc);
          break;

    }
}



char menucmds[4][16]={"  Play Game    ","   Controls    ","   Credits     ","     Exit      "};
int cursel=0;
bool upp=false,dp=false;
GameStates ShowMenu(HDC hdc)
{
    HFONT font=CreateMyFont(35,40);
    SetBkMode(game_dc,TRANSPARENT);

    SelectObject(game_dc,font);
    SetTextColor(game_dc,RGB(200,180,160));
    TextOut(game_dc,100,20,"PONG 2.0!",9);

    font=CreateMyFont(20,25);
    SelectObject(hdc,font);
    SetTextColor(hdc,RGB(98,22,120));

    int cury=150;
    for(int i=0;i<4;i++)
    {
        TextOut(hdc,170,cury,menucmds[i],15);
        cury+=35;
    }
    SetTextColor(hdc,RGB(210,200,225));
    cury=150+(cursel*35);
    TextOut(hdc,170,cury,menucmds[cursel],15);
    DeleteObject(font);
    if(KEYDOWN(VK_UP))
    {  if(!upp)
    {
        upp=true;
        cursel--;
        if(cursel<0)
            cursel=3;

    }}
    else upp=false;
    if(KEYDOWN(VK_DOWN))
    {if(!dp)
    {
        dp=true;
        cursel=(cursel+1)%4;

    }}
    else dp=false;
    if(KEYDOWN(VK_RETURN))
    {
        RECT myrect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
        FillRect(hdc,&myrect,black_brush);
        My_PlaySound((char *)"sounds\\whoah.mp3");
            switch(cursel)
           {
             case 0:
               return GSPlaying;
            break;
             case 1:
              return GSControls;
            break;
             case 2:
              return GSCredits;
            break;
             case 3:
              done = 1;
              break;
          }

    }
    return GSMenu;

}


void SetupLevel()
{
    global_curBall.speedy = -(BALL_SPEED_Y + ((float)(Cur_Level) * 2));

    BricksLeft = TOTAL_BRICKS;

    srand(GetTickCount());
    int x = 20 , y = 20;
    for(int i=0;i<TOTAL_BRICKS;i++)
    {
        ALL_BRICKS[i].x = x;
        ALL_BRICKS[i].y = y;
        ALL_BRICKS[i].color = rand()%4;
        if(ALL_BRICKS[i].color ==0)
        {
            ALL_BRICKS[i].isliving = MY_FALSE;
            BricksLeft--;
        }
        else
        {
            ALL_BRICKS[i].isliving = MY_TRUE;
        }

        x += 60;
        if(x > (WINDOW_WIDTH - 20))
        {
            y+=30;
            x = 20;
        }

    }
}


int islevelsetup = 0;

GameStates Play_MainGame()
{
    if(islevelsetup == 0)
    {
        SetupLevel();
        islevelsetup = 1;
    }

    Bat  curBat = global_curBat;

    curBat.curx += curBat.speedx;

    float batwideby2 = (float)BAT_WIDTH / 2.0;
    if(curBat.curx < (batwideby2 + 1.0f))
    {
        curBat.curx = batwideby2 + 1.0f;
    }
    else if(curBat.curx > ((float)WINDOW_WIDTH - batwideby2))
    {
        curBat.curx = ((float)WINDOW_WIDTH) - batwideby2;
    }
    curBat.posx = (int) curBat.curx;

    Ball curBall = global_curBall;

    curBall.curx += curBall.speedx;

    float ballwideby2 = (float)BALL_WIDTH / 2.0;
    if(curBall.curx < ballwideby2)
    {
        curBall.curx = ballwideby2;
        curBall.speedx = - curBall.speedx;
    }
    else if(curBall.curx > ((float)WINDOW_WIDTH - ballwideby2))
    {
        curBall.curx = (float)WINDOW_WIDTH - ballwideby2;
        curBall.speedx = -curBall.speedx;
    }
    curBall.posx = (int) curBall.curx;

    curBall.cury += curBall.speedy;
    float ballhiteby2 = (float)BALL_HEIGHT / 2.0;
    if(curBall.cury < ballhiteby2)
    {
        curBall.cury = ballhiteby2;
        curBall.speedy = - curBall.speedy;
    }
    else if(curBall.cury >= ((float)WINDOW_HEIGHT - ballhiteby2 - 3.0f))
    {
        if( ((curBall.curx+ ballwideby2) < (curBat.curx - batwideby2 - 1.0f)) || ((curBall.curx - ballwideby2) > (curBat.curx + batwideby2 + 1.0f)))
        {
            My_PlaySound((char*)"sounds\\paddlebreak.mp3");
            MessageBox(hCurrentWindow,"You Lost... \n Try again Later.....   :) ","OOPS!!!",MB_OK | MB_ICONINFORMATION);
            islevelsetup = 0;
             RECT myrect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
            FillRect(game_dc,&myrect,black_brush);
            return GSMenu;
        }
        else
        {
            curBall.speedy = -curBall.speedy;
            curBall.speedx = (curBall.curx - curBat.curx)/10.0f;
        }
    }
    curBall.posy = (int) curBall.cury;

    for(int i=0;i<TOTAL_BRICKS;i++)
    {
        if(ALL_BRICKS[i].isliving == MY_TRUE)
        {
            int diffx = ALL_BRICKS[i].x - curBall.posx;
            int diffy = ALL_BRICKS[i].y - curBall.posy;
            if(diffx < 0)
              diffx = -diffx;
            if(diffy < 0)
              diffy = -diffy;
            if((diffx < ((BALL_WIDTH + BRICK_WIDTH)/2)) &&  (diffy < ((BALL_HEIGHT + BRICK_HEIGHT)/2)))
            {
                int global_diffx = ALL_BRICKS[i].x - global_curBall.posx;
                int global_diffy = ALL_BRICKS[i].y - global_curBall.posy;
                if(global_diffx < 0)
                   global_diffx = -global_diffx;
                if(global_diffy < 0)
                   global_diffy = -global_diffy;

                if(global_diffx > ((BALL_WIDTH + BRICK_WIDTH)/2))         /** TURN BALL ON BRICK BREAK */
                  curBall.speedx = -curBall.speedx;
                else if(global_diffy > ((BALL_HEIGHT + BRICK_HEIGHT)/2))
                  curBall.speedy = -curBall.speedy;

                ALL_BRICKS[i].isliving = MY_FALSE;
                RECT myrect = {(ALL_BRICKS[i].x - (BRICK_WIDTH/2)),(ALL_BRICKS[i].y - (BRICK_HEIGHT/2)), (ALL_BRICKS[i].x + (BRICK_WIDTH / 2)),(ALL_BRICKS[i].y+(BRICK_HEIGHT/2))};
                FillRect(game_dc,&myrect,black_brush);

                BricksLeft--;

                My_PlaySound((char*)"sounds\\brickBreak.mp3");
                if(BricksLeft == 0)
               {
                  MessageBox(hCurrentWindow,"You WON... \n Continue to next Level....   :) ","WOWEEEE!!!",MB_OK | MB_ICONINFORMATION);
                  Cur_Level++;
                  My_PlaySound((char*)"sounds\\win.mp3");
                  if(Cur_Level >= MAX_LEVELS)
                  {
                      MessageBox(hCurrentWindow,"You COMPLETED the Whole Game.... \n Thanks For Playing.....   :) ","WOWEEEEEEEEEE!!!",MB_OK | MB_ICONEXCLAMATION);
                       RECT myrect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
                       FillRect(game_dc,&myrect,black_brush);
                       return GSMenu;

                  }
                  else
                  {
                      islevelsetup = 0;
                  }
               }


            }
            else
            {
                HBRUSH selbrush;
                switch(ALL_BRICKS[i].color)
              {
                 case 1:
                {
                 selbrush = red_brush;
               }break;
            case 2:
            {
                 selbrush = green_brush;
            }break;
            case 3:
            {
                 selbrush = blue_brush;
            }break;
            default :
                selbrush = black_brush;
                break;
           }

              RECT myrect = {(ALL_BRICKS[i].x - (BRICK_WIDTH/2)),(ALL_BRICKS[i].y - (BRICK_HEIGHT/2)), (ALL_BRICKS[i].x + (BRICK_WIDTH / 2)),(ALL_BRICKS[i].y+(BRICK_HEIGHT/2))};

              FillRect(game_dc,&myrect,selbrush);

            }

        }
    }

    /**    ERASE BATS AND BALL */
    SelectObject(game_dc,black_pen);
    SelectObject(game_dc,black_brush);
    Ellipse(game_dc,(global_curBat.posx - batwideby2),WINDOW_HEIGHT - BAT_HEIGHT - 2,(global_curBat.posx + batwideby2),WINDOW_HEIGHT - 2);
    Ellipse(game_dc,(global_curBall.posx - ballwideby2),(global_curBall.posy - ballhiteby2),(global_curBall.posx + ballwideby2),(global_curBall.posy + ballhiteby2));

    if(KEYDOWN(VK_LEFT))
       curBat.speedx = -  BAT_SPEED;
    else if(KEYDOWN(VK_RIGHT))
       curBat.speedx =  BAT_SPEED;
    else
       curBat.speedx = 0.0f;

    global_curBall = curBall;
    global_curBat = curBat;

    /**    DRAW BATS AND BALL */
    SelectObject(game_dc,red_brush);
    SelectObject(game_dc,red_pen);
    Ellipse(game_dc,(global_curBat.posx - batwideby2),WINDOW_HEIGHT - BAT_HEIGHT - 2,(global_curBat.posx + batwideby2),WINDOW_HEIGHT - 2);
    Ellipse(game_dc,(global_curBall.posx - ballwideby2),(global_curBall.posy - ballhiteby2),(global_curBall.posx + ballwideby2),(global_curBall.posy + ballhiteby2));

    /** WRITE the Required texts on Screen  */
    /** USE :
            TextOut(hdc,startx,starty,text,numberOfLetters);
    */

    HFONT font=CreateMyFont(9,14);

    SelectObject(game_dc,font);
    SetTextColor(game_dc,RGB(150,120,170));

    char s[10];
    sprintf(s,"%d",(Cur_Level + 1));
    TextOut(game_dc,WINDOW_WIDTH + 4,10,"LEVEL :",7);
    TextOut(game_dc,WINDOW_WIDTH + 18,30,s,1);

    SetTextColor(game_dc,RGB(20,10,200));
    TextOut(game_dc,WINDOW_WIDTH + 2,50,"Welcome",7);
    TextOut(game_dc,WINDOW_WIDTH + 20,80,"TO",2);

    SetTextColor(game_dc,RGB(200,10,20));
    font=CreateMyFont(10,18);
    SelectObject(game_dc,font);
    TextOut(game_dc,WINDOW_WIDTH + 5,150,"PONG!",5);
    TextOut(game_dc,WINDOW_WIDTH + 15,180,"2.0",3);

    DeleteObject(font);

    SelectObject(game_dc,blue_pen);
    MoveToEx(game_dc,WINDOW_WIDTH+1,1,NULL);
    LineTo(game_dc,WINDOW_WIDTH+1,WINDOW_HEIGHT);

    if(KEYDOWN(VK_ESCAPE))
    {
        RECT myrect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
        FillRect(game_dc,&myrect,black_brush);
        My_PlaySound((char*)"sounds\\whoah.mp3");
        return GSMenu;
    }

    return GSPlaying;
}



void GameQuit()
{
    if(se!=NULL)
      se->drop();

    DeleteObject(red_pen);
    DeleteObject(green_pen);
    DeleteObject(blue_pen);
    DeleteObject(black_pen);

    DeleteObject(red_brush);
    DeleteObject(green_brush);
    DeleteObject(blue_brush);
    DeleteObject(black_brush);

    ReleaseDC(hCurrentWindow,game_dc);

    ChangeDisplaySettings(NULL,NULL);    // return to Original display
}

void setMousePos(int x,int y,TrueFalse lbtn)
{
    if(global_curState == GSPlaying)
    {
        int batwideby2 = BAT_WIDTH /2;

       /**    ERASE BAT */
        SelectObject(game_dc,black_pen);
       SelectObject(game_dc,black_brush);
       Ellipse(game_dc,(global_curBat.posx - batwideby2),WINDOW_HEIGHT - BAT_HEIGHT - 2,(global_curBat.posx + batwideby2),WINDOW_HEIGHT - 2);


      if(x < batwideby2)
        x = batwideby2;
      else if(x> (WINDOW_WIDTH - batwideby2))
       x = WINDOW_WIDTH - batwideby2;
      global_curBat.posx = x;
      global_curBat.curx = (float)x;


      /**    DRAW BAT */
      SelectObject(game_dc,red_brush);
      SelectObject(game_dc,red_pen);
      Ellipse(game_dc,(global_curBat.posx - batwideby2),WINDOW_HEIGHT - BAT_HEIGHT - 2,(global_curBat.posx + batwideby2),WINDOW_HEIGHT - 2);
    }
    else if(global_curState==GSMenu)
    {
        if(y>145 && y <=180)
          cursel = 0;
        else if(y>180 && y<=215)
          cursel = 1;
        else if(y>215 && y<=250)
          cursel = 2;
        else if(y>250 && y<=285)
          cursel = 3;

        if(lbtn == MY_TRUE)
        {
            if(y>145 && y<=285)
            {
                RECT myrect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
               FillRect(game_dc,&myrect,black_brush);

               My_PlaySound((char*)"sounds\\whoah.mp3");
              switch(cursel)
             {
               case 0:
                global_curState = GSPlaying;
              break;
               case 1:
               global_curState = GSControls;
              break;
               case 2:
               global_curState = GSCredits;
              break;
               case 3:
                done = 1;
                break;
             }
            }
        }

    }
    else if(global_curState == GSCredits || global_curState == GSControls)
    {
        if(lbtn == MY_TRUE)
        {
            RECT myrect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
            FillRect(game_dc,&myrect,black_brush);
            global_curState = GSMenu;
            My_PlaySound((char*)"sounds\\whoah.mp3");
        }
    }

}
