#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR szCmdLine, int nCmdShow)
{
    TCHAR       szAppName[16], szCaption[64];
    MSG         msg;
    HWND        hwnd;
    WNDCLASS    wc;

    LoadString(hInstance, IDS_APPNAME, szAppName, sizeof(szAppName) / sizeof(TCHAR));
    LoadString(hInstance, IDS_CAPTION, szCaption, sizeof(szCaption) / sizeof(TCHAR));
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hbrBackground    = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon            = LoadIcon(hInstance, szAppName);
    wc.hInstance        = hInstance;
    wc.lpfnWndProc      = WndProc;
    wc.lpszClassName    = szAppName;
    wc.lpszMenuName     = NULL;
    wc.style            = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, TEXT("Register"), TEXT("adf"), MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(szAppName, szCaption, 
                        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, 
                        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static int          nLineCount,lineNo;
    static int          cyClient, cxChar, cyChar;
    static int          xScroll;
    static HGLOBAL      hResource;
    static HWND         hwndScroll;
    static HWND         hScroll;

    CHAR        *szText;
    HINSTANCE   hInstance;
    HDC         hdc;
    PAINTSTRUCT ps;
    RECT        clientRect;
    int         i;

    switch(msg)
    {
    case WM_CREATE:
        hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
        lineNo = 0;
        //Load Text resource
        hResource = LoadResource(hInstance, FindResource(hInstance, TEXT("ANNABELLEE"), TEXT("TEXT")));
        szText = (CHAR *)LockResource(hResource);

        //Create Scrollbar
        hScroll = CreateWindow(TEXT("scrollbar"), NULL, SB_VERT | WS_CHILD | WS_VISIBLE, 
                    0, 0, 0, 0,
                    hwnd, (HMENU)1, hInstance, NULL);
        //calculate line count
        while(*szText != '\0' && *szText != '\\')
        {
            if (*szText == '\n')
                ++nLineCount;
            szText = AnsiNext(szText);
        }
        *szText == '\0';

        //Get char size
        cxChar = LOWORD(GetDialogBaseUnits());
        cyChar = HIWORD(GetDialogBaseUnits());
        xScroll = GetSystemMetrics(SM_CXVSCROLL);

        //Setup scroll 
        SetScrollRange(hScroll, SB_CTL, 0, nLineCount, TRUE);
        SetScrollPos(hScroll, SB_CTL, 0, TRUE);
        break;
    case WM_SIZE:
        {
            MoveWindow(hScroll, LOWORD(lParam) - xScroll, 0, xScroll, HIWORD(lParam), TRUE); 
            cyClient = HIWORD(lParam);
            SetFocus(hScroll);
            break;
        }
    case WM_SETFOCUS:
        {
            SetFocus(hScroll);
            break;
        }
    case WM_VSCROLL:
        {
            switch(wParam)
            {
                case SB_TOP:
                    lineNo = 0;
                    break;
                case SB_BOTTOM:
                    lineNo = nLineCount;
                    break;
                case SB_LINEDOWN:
                    lineNo++;
                    break;
                case SB_LINEUP:
                    lineNo--;
                    break;
                case SB_PAGEDOWN:
                    lineNo += cyClient / cyChar;
                    break;
                case SB_PAGEUP:
                    lineNo -= cyClient / cyChar;
                    break;
                default:
                    break;
            }
            lineNo = max(0, lineNo);
            lineNo = min(lineNo, nLineCount);
            SetScrollPos(hScroll, SB_CTL, lineNo, TRUE);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
    case WM_PAINT:
        {
            hdc = BeginPaint(hwnd, &ps);
            GetClientRect(hwnd, &clientRect);
            clientRect.left += cxChar;
            clientRect.top += cyChar*(1 - lineNo);
            szText = (CHAR *)LockResource(hResource);
            DrawTextA(hdc, szText, -1, &clientRect, DT_TOP); 
            EndPaint(hwnd, &ps);
            break;
        }
    case WM_DESTROY:
        {
            FreeResource(hResource);
            PostQuitMessage(0);
            break;
        }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}