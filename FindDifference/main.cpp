#include <windows.h>
#include "resource.h"
#include <windowsx.h>


static int iSysWidth;
static int iSysHeight;

HINSTANCE hInst;

HINSTANCE hInstance;


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

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
    static HWND check1,check2,check3,check4,check5,hwndToolsGroup;

    HWND checks[8];
    int x = 400;
    static HDC hdcCat1, hdcCat2, hdcGuffy1, hdcGuffy2;

    static BITMAP bitmapCat1, bitmapCat2, bitmapGuffy1, bitmapGuffy2;
    static HBITMAP hbmpCat1 = NULL ;
    static HBITMAP hbmpCat2 = NULL;
    static HBITMAP hbmpGuffy1 = NULL;
    static HBITMAP hbmpGuffy2 = NULL;
    static HFONT font_forte, text_font;
    HDC hDC;
    PAINTSTRUCT Ps;
    HDC hdc = GetDC(hwnd);
    HBRUSH hbrush;
    RECT rect;

    // load bitmaps
    hbmpCat1 = (HBITMAP)LoadImage(hInst, "Cat1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hbmpCat1, sizeof(bitmapCat1), &bitmapCat1);

    hbmpCat2 = (HBITMAP)LoadImage(hInst, "Cat2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hbmpCat2, sizeof(bitmapCat2), &bitmapCat2);

    //Static variables for mouse Coordinates
    static int xMouse, yMouse;
	xMouse = GET_X_LPARAM(lParam);
	yMouse = GET_Y_LPARAM(lParam);

    /*hEllipse = (HBITMAP)LoadImage(hInstance, "ellipse.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hEllipse, sizeof(ellipsebit), &ellipsebit);

    hRect = (HBITMAP)LoadImage(hInstance, "rect.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(hRect, sizeof(rectbit), &rectbit);*/

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
           switch(LOWORD(wParam))
                {
                    //Exit Coammand
                    case IDI_EXIT:
                        {
                            PostQuitMessage (0);
                        }

                    case IDI_NEW:
                        {

                        }

                    break;

                }
        break;

            case WM_CREATE:

                for(int i=0;i<8;i++)
                {
                    checks[i] = CreateWindow(TEXT("button"), TEXT(""+i),
                            WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                            x, 500, 15, 12,
                            hwnd, (HMENU) 1, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
                    x+=20;
                }
           break;

            //Work with LButton
            case WM_LBUTTONDOWN:
                {

                    //if(xMouse >)
                    char str [256];
                    POINT pt;
                    pt.x = LOWORD(lParam);
                    pt.y = HIWORD(lParam);
                    wsprintf(str, "Co-ordinates are \nX=%i and Y=%i", pt.x, pt.y);
                //if(xMouse > 20 && xMouse < 410 && yMouse > 50 && yMouse <500)
                //{
                   MessageBoxA(NULL,str, "wada", MB_OK | MB_ICONINFORMATION);
                //}
                }
                break;


            case WM_PAINT:
                {
                    hDC = BeginPaint(hwnd, &Ps);

                    hdcCat1 = CreateCompatibleDC(hdc);
                    SelectObject(hdcCat1, hbmpCat1);
                    BitBlt(hdc, 37, 80, bitmapCat1.bmWidth, bitmapCat1.bmHeight, hdcCat1, 0, 0, SRCCOPY);
                    DeleteDC(hdcCat1);

                    hdcCat2 = CreateCompatibleDC(hdc);
                    SelectObject(hdcCat2, hbmpCat2);
                    BitBlt(hdc, 400, 80, bitmapCat2.bmWidth, bitmapCat2.bmHeight, hdcCat2, 0, 0, SRCCOPY);
                    DeleteDC(hdcCat2);

                    GetClientRect(hwnd, &rect);  // retrieves the coordinates of a window's client area

                    // create the title
                    font_forte   = CreateFont(30, 27.5, 0, 0, FW_DONTCARE, false, false, false,
                                      DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                      DEFAULT_QUALITY, FF_DONTCARE, "Forte");

                    text_font  = (HFONT)SelectObject(hdc, font_forte);   // setting new font for text
                    SetTextColor(hdc, TITLE_COLOR);                     // setting new text color
                    TextOut( hdc, 115, 20,  "Find the difference", 19);

                    EndPaint(hwnd, &Ps);

                }
                break;

        case WM_CTLCOLORSTATIC:
            {
                //SetTextColor((HDC)wParam,RGB(color_id + 20, 100, 255 - color_id)); // text color
                SetBkMode((HDC)wParam,TRANSPARENT);                                // transparent background
                hbrush=(HBRUSH)GetStockObject(NULL_BRUSH);                         // handle to brush, no background color
                return(LRESULT) hbrush;
            }
        break;


        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}
