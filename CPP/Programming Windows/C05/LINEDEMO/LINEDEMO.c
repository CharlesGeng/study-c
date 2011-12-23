#include <windows.h>
#include <math.h>

#define COUNT 1500
#define M_PI    3.14159265358979323846

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    TCHAR       *szAppName    = TEXT("LINEDEMO");
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

    hwnd = CreateWindowW(szAppName, TEXT("Line Demo"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,CW_USEDEFAULT, CW_USEDEFAULT,CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
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
    static int  top, left, bottom, right;
    int xrRect, yrRect;
    HDC         hdc;
    PAINTSTRUCT ps;

    int         i;

    switch(msg)
    {
    case WM_SIZE:
        {
            //��ȡ�ͻ�������
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
            top     = cyClient / 5;
            left    = cxClient / 5;
            right   = cxClient * 4 / 5;
            bottom  = cyClient * 4 / 5;
            return 0;
        }
    case WM_PAINT:
        {
            hdc = BeginPaint(hwnd, &ps);
            //������
            Rectangle(hdc, left, top, right, bottom);

            //���Խ���
            MoveToEx(hdc, 0,0, NULL);
            LineTo(hdc, cxClient, cyClient);
            MoveToEx(hdc, 0, cyClient, NULL);
            LineTo(hdc, cxClient, 0);
            
            //����Բ
            Ellipse(hdc, left, top, right, bottom);

            //��Բ�Ǿ���
            xrRect = (right -left) / 5;
            yrRect = (bottom - top) / 5;
            RoundRect(hdc, left + xrRect, top + yrRect, right - xrRect, bottom -yrRect, cxClient /10, cxClient /10);

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
