#include <Windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	TCHAR	*szClassName    = TEXT("ICONDEMO");
	TCHAR	*szWindowName   = TEXT("MYICON");

	MSG		    msg;
    WNDCLASS    wc;
	HWND	    hwnd;

    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hbrBackground    = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    //wc.hIcon            = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIcon            = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wc.hInstance        = hInstance;
    wc.lpfnWndProc      = WndProc;
    wc.lpszClassName    = szClassName;
    wc.lpszMenuName     = NULL;
    wc.style            = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, TEXT("Register Class Failed!"), TEXT("ERROR"), MB_ICONERROR);
        return 0;
    }

    hwnd    = CreateWindow (szClassName, szWindowName, WS_OVERLAPPEDWINDOW, 
                            CW_USEDEFAULT,CW_USEDEFAULT, 
                            CW_USEDEFAULT,CW_USEDEFAULT,
                            NULL, NULL, hInstance, NULL);
    
    UpdateWindow(hwnd);
    ShowWindow(hwnd, nCmdShow);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static int      cxClient, cyClient;
    static int      cxICON, cyICON;
    static HICON    icon;       

    HDC             hdc;
    PAINTSTRUCT     ps;
    int             i, j;

    switch(msg)
    {
    case WM_CREATE:
        {
            icon = LoadIcon((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDI_ICON1));
            cxICON  = GetSystemMetrics(SM_CXICON);
            cyICON  = GetSystemMetrics(SM_CYICON);
            break;
        }
    case WM_SIZE:
        {
            cxClient    = LOWORD(lParam);
            cyClient    = HIWORD(lParam);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
    case WM_PAINT:
        {
            hdc = BeginPaint(hwnd, &ps);
            for (i = 0; i < cxClient; i += cxICON)
            {
                for (j = 0; j <= cyClient; j += cyICON)
                {
                    DrawIcon(hdc, i, j, icon);
                }
            }
            EndPaint(hwnd, &ps);
            break;
        }
    case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
