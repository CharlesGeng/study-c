#include <windows.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nShowCmd)
{
    //TODO: Application name
    TCHAR       *szAppName  = TEXT("STATICCLASS");
    //TODO: Widow's title
    TCHAR       *szTitle    = TEXT("Static Class Test");
    WNDCLASS    wc;
    HWND        hWnd;
    MSG         msg;

    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hbrBackground    = CreateSolidBrush(RGB(0xCC, 0xE8, 0xCF));
    wc.hCursor          = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
    wc.hIcon            = (HICON)LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance        = hInstance;
    wc.lpfnWndProc      = WndProc;
    wc.lpszClassName    = szAppName;
    wc.lpszMenuName     = NULL;
    wc.style            = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, TEXT("Register WNDCLASS failed!"), TEXT("ERROR"), MB_ICONERROR);
        return 0;
    }

    hWnd = CreateWindow(szAppName, szTitle,
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    ShowWindow(hWnd, nShowCmd);
    UpdateWindow(hWnd);

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC				hdc;
    PAINTSTRUCT		ps;
    HWND            hwndSC;
    int             i;

    switch(uMsg)
    {
    case WM_CREATE:
        {
            i = 1;
            hwndSC = CreateWindow(TEXT("STATIC"), TEXT("TEST"), WS_CHILD | SS_WHITERECT | WS_VISIBLE, 0, 0, 50, 50, hwnd, (HMENU)i++, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            hwndSC = CreateWindow(TEXT("STATIC"), TEXT("TEST"), WS_CHILD | SS_GRAYRECT  | WS_VISIBLE, 0, 60, 50, 50, hwnd, (HMENU)i++, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            hwndSC = CreateWindow(TEXT("STATIC"), TEXT("TEST"), WS_CHILD | SS_BLACKRECT | WS_VISIBLE, 0, 120, 50, 50, hwnd, (HMENU)i++, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            hwndSC = CreateWindow(TEXT("STATIC"), TEXT("TEST"), WS_CHILD | SS_WHITEFRAME| WS_VISIBLE, 60, 0, 50, 50, hwnd, (HMENU)i++, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            hwndSC = CreateWindow(TEXT("STATIC"), TEXT("TEST"), WS_CHILD | SS_GRAYFRAME | WS_VISIBLE, 60, 60, 50, 50, hwnd, (HMENU)i++, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            hwndSC = CreateWindow(TEXT("STATIC"), TEXT("TEST"), WS_CHILD | SS_BLACKFRAME| WS_VISIBLE, 60, 120, 50, 50, hwnd, (HMENU)i++, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            hwndSC = CreateWindow(TEXT("STATIC"), TEXT("TEST"), WS_CHILD | SS_LEFT      | WS_VISIBLE, 120, 0, 50, 50, hwnd, (HMENU)i++, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            hwndSC = CreateWindow(TEXT("STATIC"), TEXT("TEST"), WS_CHILD | SS_RIGHT     | WS_VISIBLE, 120, 60, 50, 50, hwnd, (HMENU)i++, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            hwndSC = CreateWindow(TEXT("STATIC"), TEXT("TEST"), WS_CHILD | SS_CENTER    | WS_VISIBLE, 120, 120, 50, 50, hwnd, (HMENU)i++, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            hwndSC = CreateWindow(TEXT("STATIC"), TEXT("TEST"), WS_CHILD | SS_ETCHEDHORZ| WS_VISIBLE, 180, 0, 50, 50, hwnd, (HMENU)i++, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            hwndSC = CreateWindow(TEXT("STATIC"), TEXT("TEST"), WS_CHILD | SS_ETCHEDVERT| WS_VISIBLE, 180, 60, 50, 50, hwnd, (HMENU)i++, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            hwndSC = CreateWindow(TEXT("STATIC"), TEXT("TEST"), WS_CHILD | SS_ETCHEDFRAME|WS_VISIBLE, 180, 120, 50, 50, hwnd, (HMENU)i++, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            break;
        }
    case WM_PAINT:
        {
            hdc = BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);
            break;
        }
    case WM_CTLCOLORSTATIC:
        {
            hwndSC = (HWND)lParam;
            hdc = GetDC(hwndSC);
            SetTextColor(hdc, RGB(0xFF, 0, 0));
            ReleaseDC(hwndSC, hdc);
            break;
        }
    case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
