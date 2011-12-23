#include <windows.h>
#include <math.h>

#define COUNT 1500
#define M_PI    3.14159265358979323846

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    TCHAR       *szAppName    = TEXT("SineWave");
    WNDCLASS    wc;
    HWND        hwnd;
    MSG         msg;

    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hbrBackground    = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.hCursor          = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
    wc.hIcon            = (HICON)LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance        = hInstance;
    wc.lpfnWndProc      = WndProc;
    wc.lpszClassName    = szAppName;
    wc.lpszMenuName     = NULL;
    wc.style            = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, TEXT("ERROR"), TEXT("ERROR"), MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindowW(szAppName, TEXT("Show Sine Wave"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,CW_USEDEFAULT, CW_USEDEFAULT,CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static int  cxClient, cyClient;
    HDC         hdc;
    PAINTSTRUCT ps;

    int         i;    
    POINT       pPoints[COUNT];

    switch(msg)
    {
    case WM_SIZE:
        {
            //获取客户区矩形
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
            return 0;
        }
    case WM_PAINT:
        {
            hdc = BeginPaint(hwnd, &ps);
            //画水平轴
            MoveToEx(hdc, 0, cyClient/2, NULL);
            LineTo(hdc, cxClient, cyClient/2);
            //计算各个x点对应的纵座标
            for (i = 0; i < COUNT; ++i)
            {
                pPoints[i].x = i * cxClient / COUNT;
                pPoints[i].y = (int)(cyClient / 2 * (1- sin(2 * M_PI * i / COUNT) ));
            }
            Polyline(hdc, pPoints, COUNT);
            EndPaint(hwnd, &ps);
            return 0;
        }
    case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
    default:
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}