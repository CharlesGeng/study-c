#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void MyDrawRect(HWND);
//x axle length, y axle length.
int cxClient, cyClient;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	TCHAR *szClassName	= TEXT("RandRect");
	TCHAR *szAppName    = TEXT("Random Rectangle");
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

	while(TRUE)
	{
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                return 0;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            MyDrawRect(hwnd);
        }
	}

	return 0;
}
void MyDrawRect(HWND hwnd)
{
    HDC     hdc;
    HBRUSH  brush;
    RECT    rect;

    if(cxClient == 0 || cyClient == 0)
        return;

    hdc = GetDC(hwnd);
    brush = CreateSolidBrush(RGB(rand()%256,rand()%256,rand()%256));
    SetRect(&rect, rand()%cxClient, rand()%cyClient, rand()%cxClient, rand()%cyClient);
    FillRect(hdc, &rect, brush);
    ReleaseDC(hwnd, hdc);
    DeleteObject(brush);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_SIZE:
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
