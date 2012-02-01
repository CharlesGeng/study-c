#include <windows.h>

#define POINTCOUNT  1000

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    static TCHAR *szAppName  = TEXT("CONNECT");
    static TCHAR *szTitle    = TEXT("Connect the points mouse move");

    MSG         msg;
    WNDCLASS    wc;
    HWND        hwnd;
    
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hbrBackground    = GetStockObject(WHITE_BRUSH);
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon            = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance        = hInstance;
    wc.lpfnWndProc      = WndProc;
    wc.lpszClassName    = szAppName;
    wc.lpszMenuName     = NULL;
    wc.style            = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&wc))
    {
        return 0;
    }

    hwnd = CreateWindow(szAppName, szTitle, WS_OVERLAPPEDWINDOW, 
        CW_USEDEFAULT, CW_USEDEFAULT, 
        CW_USEDEFAULT, CW_USEDEFAULT, 
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static POINT    points[POINTCOUNT];
    static  int     nIndex;

    PAINTSTRUCT ps;
    int         i, j;
    HDC         hdc;

    switch(uMsg)
    {
        //Save the points and show point
    case WM_MOUSEMOVE:
        if ((MK_LBUTTON & wParam) && nIndex < POINTCOUNT)
        {
            points[nIndex].x = LOWORD(lParam);
            points[nIndex].y = HIWORD(lParam);
            ++nIndex;

            hdc = GetDC(hwnd);
            SetPixel(hdc, LOWORD(lParam), HIWORD(lParam), RGB(0,0,0));
            ReleaseDC(hwnd, hdc);
        }
        break;
        //Draw the lines;
    case WM_LBUTTONUP:
        InvalidateRect(hwnd, NULL, TRUE);
        break;
        //Clear the Client Area
    case WM_RBUTTONDOWN:
    case WM_LBUTTONDOWN:
        nIndex = 0;
        InvalidateRect(hwnd, NULL, TRUE);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);

        SetCursor(LoadCursor(NULL, IDC_WAIT));
        ShowCursor(TRUE);

        for (i = 1; i < nIndex; ++i)
        {
            for (j = 0; j < i; ++j)
            {
                MoveToEx(hdc, points[j].x, points[j].y, NULL);
                LineTo(hdc, points[i].x, points[i].y);
            }
        }

        SetCursor(LoadCursor(NULL, IDC_ARROW));
        ShowCursor(FALSE);

        EndPaint(hwnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}