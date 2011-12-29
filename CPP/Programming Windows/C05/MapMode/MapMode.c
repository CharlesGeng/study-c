#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    TCHAR       *szAppName    = TEXT("MapMode");
    WNDCLASS    wc;
    MSG         msg;
    HWND        hwnd;

    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hbrBackground    = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.hCursor          = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
    wc.hIcon            = (HICON)LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance        = hInstance;
    wc.lpfnWndProc      = WndProc;
    wc.lpszClassName    = szAppName;
    wc.lpszMenuName     = NULL;
    wc.style            = CS_VREDRAW | CS_HREDRAW;

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, TEXT("ERROR"), TEXT("ERROR"), MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(szAppName, TEXT("Test Map Mode"),
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

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static int cxClient, cyClient;
    SIZE sizeWnd, sizeView;
    PAINTSTRUCT ps;
    HDC hdc;
    int i ;
    switch (msg)
    {
    case WM_SIZE:
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);

        SetMapMode(hdc, MM_ISOTROPIC);
        SetWindowExtEx(hdc, 16, 16, NULL);
        SetViewportExtEx(hdc, GetDeviceCaps(hdc, LOGPIXELSX), GetDeviceCaps(hdc, LOGPIXELSY), NULL);
        Ellipse(hdc, 0, 0, 16, 16);
        EndPaint(hwnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}