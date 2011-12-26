#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    WNDCLASS    wc;
    HWND        hwnd;
    MSG         msg;

    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hbrBackground    = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.hCursor          = (HCURSOR)LoadCursorW(NULL, IDC_ARROW);
    wc.hIcon            = (HICON)LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance        = hInstance;
    wc.lpfnWndProc      = WndProc;
    wc.lpszClassName    = TEXT("DRAWBEZIER");
    wc.lpszMenuName     = NULL;
    wc.style            = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, TEXT("Error"), TEXT("ERROR"), MB_ICONERROR);
    }

    hwnd = CreateWindowW(TEXT("DRAWBEZIER"), TEXT("Draw Bezier Line"),
                         WS_OVERLAPPEDWINDOW,
                         CW_USEDEFAULT,
                         CW_USEDEFAULT,
                         CW_USEDEFAULT,
                         CW_USEDEFAULT,
                         NULL,
                         NULL,
                         hInstance,
                         NULL);

    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int cxClient, cyClient;
    POINT   apt[7];
    HDC     hdc;
    PAINTSTRUCT ps;

    switch(uMsg)
    {
    case WM_SIZE:
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        apt[0].x = cxClient / 8;
        apt[1].x = 2 * cxClient / 8;
        apt[2].x = 3 * cxClient / 8;;
        apt[3].x = 4 * cxClient / 8;
        apt[4].x = 5 * cxClient / 8;
        apt[5].x = 6 * cxClient / 8;
        apt[6].x = 7 * cxClient / 8;

        apt[0].y = cyClient / 2;
        apt[1].y = cyClient / 8;
        apt[2].y = 7 * cyClient / 8;
        apt[3].y = cyClient / 2;
        apt[4].y = cyClient / 8;
        apt[5].y = 7 * cyClient / 8;
        apt[6].y = cyClient / 2;

        PolyBezier(hdc, apt, 7);
        MoveToEx(hdc, apt[0].x, apt[0].y, &apt[0]);
        LineTo(hdc, apt[6].x, apt[6].y);
        EndPaint(hwnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
