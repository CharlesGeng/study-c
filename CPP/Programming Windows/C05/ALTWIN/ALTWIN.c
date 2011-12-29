#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    TCHAR       *szAppName  = TEXT("ALTWIN");
    TCHAR       *szTitle    = TEXT("AlTERNATE WINDING");
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
    wc.lpszClassName    = szAppName;
    wc.lpszMenuName     = NULL;
    wc.style            = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, TEXT("Error"), TEXT("Register Window Class Error"), MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindowW(szAppName, szTitle,
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
    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int cxClient, cyClient;
    POINT   aptFigure[] = {10, 20, 10, 40, 30, 40, 30, 10, 50, 10, 50, 30, 20, 30, 20, 50, 40, 50, 40, 20};
    HBRUSH  hBrush;
    HDC     hdc;
    PAINTSTRUCT ps;
    int i;

    switch(uMsg)
    {
    case WM_SIZE:
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        //hBrush = CreateSolidBrush(RGB(0,0,255));
        hBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(0,0,255));
        SelectObject(hdc, hBrush);
        SelectObject(hdc, GetStockObject(NULL_PEN));
        SetPolyFillMode(hdc, ALTERNATE);
        for (i = 0; i < 10; ++i)
        {
            aptFigure[i].x = cxClient * aptFigure[i].x / 120;
            aptFigure[i].y = cyClient * aptFigure[i].y / 60;
        }
        Polygon(hdc, aptFigure, sizeof(aptFigure) / sizeof(POINT));

        SetPolyFillMode(hdc, WINDING);
        for (i = 0; i < 10; ++i)
        {
            aptFigure[i].x += cxClient / 2;
        }
        Polygon(hdc, aptFigure, sizeof(aptFigure) / sizeof(POINT));
//        DeleteObject(hBrush);
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
