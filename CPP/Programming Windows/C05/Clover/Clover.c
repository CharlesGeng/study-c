#include <windows.h>

#define XWINDOW   32767
#define YWINDOW   32767
#define COUNT   10

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	TCHAR *szClassName	= TEXT("Clover");
	TCHAR *szAppName    = TEXT("Clover");
	WNDCLASS wc;
	HWND	hwnd;
	MSG		msg;

	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor			= (HCURSOR)LoadCursor(NULL, IDC_ARROW);
	wc.hIcon			= (HICON)LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance		= hInstance;
	wc.lpfnWndProc		= WndProc;
	wc.lpszClassName	= szClassName;
	wc.lpszMenuName		= NULL;
	wc.style			= CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClass(&wc))
	{
		return 0;
	}
	hwnd = CreateWindow(szClassName,
						szAppName,
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

    while (GetMessage(&msg, hwnd, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int cxClient, cyClient;
    HDC         hdc;
    HRGN        hrgn, hrgn1, hrgn2, hrgn3, hrgn4;
    HBRUSH      hbrush;
    PAINTSTRUCT ps;

    switch(uMsg)
    {
    case WM_SIZE:
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        SetMapMode(hdc, MM_ANISOTROPIC);
        SetWindowExtEx(hdc, XWINDOW, YWINDOW, NULL);
        SetViewportExtEx(hdc, cxClient, -cyClient, NULL);
        SetViewportOrgEx(hdc, cxClient/2, cyClient/2, NULL);

        hbrush = CreateHatchBrush(HS_VERTICAL, RGB(0, 0, 0));
        hrgn = CreateRectRgn(0,0, 1, 1);

        //Top Ellipse
        hrgn1 = CreateEllipticRgn(-XWINDOW/4, YWINDOW/2, XWINDOW/4, 0);

        //left Ellipse
        hrgn2 = CreateEllipticRgn(-XWINDOW/2, YWINDOW/4, 0, -YWINDOW/4);

        CombineRgn(hrgn, hrgn1, hrgn2, RGN_XOR);

        //Bottom Ellipse
        hrgn3 = CreateEllipticRgn(-XWINDOW/4, -YWINDOW/2, XWINDOW/4, 0);
        CombineRgn(hrgn, hrgn, hrgn3, RGN_XOR);

        //right Ellipse
        hrgn4 = CreateEllipticRgn(0, YWINDOW/4, XWINDOW/2, -YWINDOW/4);
        CombineRgn(hrgn, hrgn, hrgn4, RGN_XOR);

        FillRgn(hdc, hrgn, hbrush);

        EndPaint(hWnd,&ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
