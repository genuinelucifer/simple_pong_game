#define WIN32_LEAN_AND_MEAN

#include "myfuncs.h"



/*  Make the class name into a global variable  */
char szClassName[ ] = "MainWindow";


/**    Declare Functions       */

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/* Declare more Procedures    */
ATOM RegisterMyClass(HINSTANCE hThisInstance);



int WINAPI WinMain (HINSTANCE hTheInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{


   if(!RegisterMyClass(hTheInstance))
       return GE_CLASS_NOT_REGISTERED;           /** ERROR : Class could not be registered */

    /* The class is registered, let's create the program*/
    HWND hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "Classic Pong...  :)",       /* Title Text */
           WS_POPUP | WS_VISIBLE, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           SCREEN_WIDTH,                 /* The programs width */
           SCREEN_HEIGHT,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hTheInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );
    if(!hwnd)
       return  GE_WINDOW_NOT_CREATED;        /** ERROR : Window could not be Created */


    GameInit(hTheInstance,hwnd);


    MSG messages;            /* Here messages to the application are saved */
    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (!isdone())
    {
        DWORD start_tick = GetTickCount();
        if(PeekMessage(&messages,NULL,0,0,PM_REMOVE))
        {
                /* Translate virtual-key messages into character messages */
                 TranslateMessage(&messages);
               /* Send message to WindowProcedure */
                 DispatchMessage(&messages);

        }

        GameMain();

        //take care of frame rate
        while((GetTickCount()-start_tick)<GAME_SPEED)
            ;


    }
    while(SplashEnd()==MY_FALSE)
        ;

    GameQuit();

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_MOUSEMOVE :
          setMousePos((int)LOWORD(lParam),(int)HIWORD(lParam),MY_FALSE);
        break;
        case WM_LBUTTONDOWN :
          setMousePos((int)LOWORD(lParam),(int)HIWORD(lParam),MY_TRUE);
        break;

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

          case  WM_CLOSE:
        {
                    int res;
                    res= MessageBox(gethCurrentWindow(),"Are U sure to quit!!!!","Really quit???",MB_YESNO | MB_ICONQUESTION);
                    if(res==IDNO)
                      return 0;
                    setdone(1);
                    PostQuitMessage(WM_QUIT);
       }
       break;
       case WM_DESTROY:
           PostQuitMessage(0);
           break;
       default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

ATOM RegisterMyClass(HINSTANCE hThisInstance)
{
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName =0 ;                      /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) (HBRUSH) GetStockObject(BLACK_BRUSH);

    /* Register the window class, and if it fails quit the program */
    return RegisterClassEx (&wincl);
}



