#include <windows.h>
#include "resource.h"
#include <iostream>
#include <windowsx.h>
#include <mmsystem.h>
#include <string>
#include <stdio.h>
#include <time.h>
#pragma comment(lib,"Winmm.lib")

using namespace std;

static int iSysWidth;
static int iSysHeight;
HINSTANCE hInst;

char* Images[4] = {"Cat","Guffy","Lupu","Ass"};


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
int GetRandom(int n);

/*  Make the class name into a global variable  */
char szClassName[ ] = "CodeBlocksWindowsApp";

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    //Getting width of the screen
    iSysWidth = GetSystemMetrics(SM_CXSCREEN);

    //Getting Height of the screen
    iSysHeight = GetSystemMetrics(SM_CYSCREEN);

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    hInst = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon   = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));     // custom icon
    wincl.hIconSm = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));     // custom icon
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = MAKEINTRESOURCE(IDI_MENU);                                  // custom menu
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "Game::Find the difference",       /* Title Text */
           WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX, /* default window */
           iSysWidth/4,       /* Windows decides the position */
           iSysHeight/25,       /* where the window ends up on the screen */
           750,                 /* The programs width */
           700,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND checks[11];
    static int  IDs[11] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int x = 400,y = 500;
    static HDC hdcCat1, hdcCat2;

    static BITMAP bitmapCat1, bitmapCat2;
    static HBITMAP hbmpImg1 = NULL ;
    static HBITMAP hbmpImg2 = NULL;

    static HFONT font_forte, text_font;
    static RECT area = {400, 80, 707, 470};

    PAINTSTRUCT Ps;
    HDC hdc = GetDC(hwnd);
    HBRUSH hbrush;
    RECT rect;
    int random = GetRandom(4);
    printf("%d",random);
    char* current_img = Images[random];

    char str[15];
    sprintf(str,"%s1.bmp",current_img);
    // load bitmaps
    hbmpImg1 = (HBITMAP)LoadImage(hInst, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hbmpImg1, sizeof(bitmapCat1), &bitmapCat1);

    sprintf(str,"%s2.bmp",current_img);
    hbmpImg2 = (HBITMAP)LoadImage(hInst, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hbmpImg2, sizeof(bitmapCat2), &bitmapCat2);

    //Static variables for mouse Coordinates
    static int xMouse, yMouse;
	xMouse = GET_X_LPARAM(lParam);
	yMouse = GET_Y_LPARAM(lParam);

    //Array of Rectangles
    RECT arr[11];

    //Coordinates of the differences
    RECT rect1 = {508,122,569,165};
    RECT rect2 = {511,161,568,180};  //sprincene
    RECT rect3 = {540, 197, 560, 217 };//ochi
    RECT rect4 = {583, 228, 614, 245};//mustata dreapta
    RECT rect5 = {645, 328, 685, 348};//coada
    RECT rect6 = {586, 292, 630, 327};//fluture
    RECT rect7 = {498, 359, 526, 388};//hand
    RECT rect8 = {520, 289, 557, 305};//piept
    RECT rect9 = {540, 390, 550, 400 };//flowerbottom
    RECT rect10 = {450, 310, 470, 330};//left
    RECT rect11 = {469, 230, 500, 245};//mustata dreapta

    //Assigning the values of rect to it's possition in array
    arr[0] = rect1;
    arr[1] = rect2;
    arr[2] = rect3;
    arr[3] = rect4;
    arr[4] = rect5;
    arr[5] = rect6;
    arr[6] = rect7;
    arr[7] = rect8;
    arr[8] = rect9;
    arr[9] = rect10;
    arr[10] = rect11;

    switch (message)                  /* handle the messages */
    {
    case WM_GETMINMAXINFO:
        {
            LPMINMAXINFO pInfo = (LPMINMAXINFO)lParam;
            pInfo -> ptMaxTrackSize.x = 750;
            pInfo -> ptMaxTrackSize.y = 700;

            pInfo -> ptMinTrackSize.x= 750;
            pInfo -> ptMinTrackSize.y = 700;
        }
    break;

    case WM_COMMAND:
        {
        switch(LOWORD(wParam))
            {
             case IDI_EXIT:      //Exit Coammand
                {
                    PostQuitMessage (0);
                }

            case IDI_NEW:
                {
                    InvalidateRect(hwnd, &area, FALSE);
                    InvalidateRect(hwnd, &area, TRUE);

                    for (int i=0; i<11; i++)
                    {
                        CheckDlgButton(hwnd, IDs[i], BST_UNCHECKED);
                    }
                }
            }
        break;
        }
    break;

    case WM_CREATE:
        {
           for(int i=0; i<sizeof(checks)/sizeof(HWND); i++)
            {
                checks[i] = CreateWindow(TEXT("button"), TEXT(""),
                        WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                        x, 500, 12, 12,
                        hwnd, (HMENU) IDs[i], hInst, NULL);
                cout << IDs[i] << endl;
                x+=16;
            }
       break;
        }

    //Work with LButton
    case WM_LBUTTONDOWN:
        {
            for (int i = 0; i < sizeof(arr)/sizeof(RECT); i++)
            {
                if(arr[i].left < xMouse && xMouse < arr[i].right && arr[i].top < yMouse && yMouse < arr[i].bottom )
                {
                    PlaySound("Level.wav", NULL, SND_ASYNC);
                    DrawEdge(hdc, &arr[i], BDR_RAISEDOUTER | BDR_SUNKENINNER, BF_RECT);
                    CheckDlgButton(hwnd, IDs[i], BST_CHECKED);
                    MessageBoxA(NULL,"You found it! Good Job", "Congrats", MB_OK | MB_ICONINFORMATION);

                }

            }



        }
    break;

    case WM_LBUTTONDBLCLK:
        {
                     char str [256];
                    POINT pt;
                    pt.x = LOWORD(lParam);
                    pt.y = HIWORD(lParam);
                    wsprintf(str, "Co-ordinates are \nX=%i and Y=%i", pt.x, pt.y);
                    MessageBoxA(NULL,str, "Message", MB_OK | MB_ICONINFORMATION);
        }
    break;

    case WM_PAINT:
        {
            BeginPaint(hwnd, &Ps);

            hdcCat1 = CreateCompatibleDC(hdc);
            SelectObject(hdcCat1, hbmpImg1);
            BitBlt(hdc, 37, 80, bitmapCat1.bmWidth, bitmapCat1.bmHeight, hdcCat1, 0, 0, SRCCOPY);
            DeleteObject(hdcCat1);

            hdcCat2 = CreateCompatibleDC(hdc);
            SelectObject(hdcCat2, hbmpImg2);
            BitBlt(hdc, 400, 80, bitmapCat2.bmWidth, bitmapCat2.bmHeight, hdcCat2, 0, 0, SRCCOPY);
            DeleteObject(hdcCat2);

            GetClientRect(hwnd, &rect);  // retrieves the coordinates of a window's client area

            // create the title
            font_forte   = CreateFont(30, 27.5, 0, 0, FW_DONTCARE, false, false, false,
                              DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                              DEFAULT_QUALITY, FF_DONTCARE, "Forte");

            text_font  = (HFONT)SelectObject(hdc, font_forte);   // setting new font for text
            SetTextColor(hdc, TITLE_COLOR);                     // setting new text color
            TextOut( hdc, 115, 20,  "Find the difference", 19);

            DeleteObject(font_forte);
            DeleteObject(text_font);

            EndPaint(hwnd, &Ps);

        }
    break;

    case WM_CTLCOLORSTATIC:
        {
            SetBkMode((HDC)wParam,TRANSPARENT);                                // transparent background
            hbrush=(HBRUSH)GetStockObject(NULL_BRUSH);                         // handle to brush, no background color
            return(LRESULT) hbrush;
        }
    break;

    case WM_DESTROY:
        {
            DeleteFont(font_forte);
            DeleteFont(text_font);
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        }
    break;

        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}

int GetRandom(int n)
{
   srand (time(NULL));
   return rand()%n;

}


