#include <windows.h>

#define POINTCOUNT  1000

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    static TCHAR *szAppName  = TEXT("BLOKOUT");
    static TCHAR *szTitle    = TEXT("Draw a rectangle");

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
    static POINT    ptBegin, ptEnd;
    static BOOL     bBlocking, bValidBox;

    PAINTSTRUCT     ps;
    HDC             hdc;

    switch(uMsg)
    {
    case WM_CREATE:
        {
            ptBegin.x   = 0;
            ptBegin.y   = 0;
            ptEnd.x     = 0;
            ptEnd.y     = 0;

            bBlocking   = FALSE;
            bValidBox   = FALSE;

            break;
        }
    case WM_LBUTTONDOWN:
        {
            ptBegin.x = ptEnd.x = LOWORD(lParam);
            ptBegin.y = ptEnd.y = HIWORD(lParam);

            bBlocking = TRUE;
            bValidBox = FALSE;
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
    case WM_MOUSEMOVE:
        {
            //Is Left button down
            if (wParam & MK_LBUTTON)
            {
                ptEnd.x = LOWORD(lParam);
                ptEnd.y = HIWORD(lParam);
                InvalidateRect(hwnd, NULL, TRUE);
            }
            break;
        }
    case WM_LBUTTONUP:
        {
            ptEnd.x = LOWORD(lParam);
            ptEnd.y = HIWORD(lParam);

            bBlocking = FALSE;
            bValidBox = TRUE;
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        if (bBlocking)
        {
            SelectObject(hdc, GetStockObject(NULL_BRUSH));
            Rectangle(hdc, ptBegin.x, ptBegin.y, ptEnd.x, ptEnd.y);
        }
        else if (bValidBox)
        {
            SelectObject(hdc, GetStockObject(BLACK_BRUSH));
            Rectangle(hdc, ptBegin.x, ptBegin.y, ptEnd.x, ptEnd.y);
        }
        EndPaint(hwnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}