#include <windows.h>

#define		TIMERID		1

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void FindWindowSize(int *, int *);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nShowCmd)
{
	TCHAR       *szAppName  = TEXT("WHATCLR");
	TCHAR       *szTitle    = TEXT("What color");
	WNDCLASS    wc;
	HWND        hWnd;
	MSG         msg;
	int			cxWindow, cyWindow;

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
		MessageBox(NULL, TEXT("Register WNDCLASS failed!"), TEXT("ERROR"), MB_ICONERROR);
		return 0;
	}

	FindWindowSize(&cxWindow, &cyWindow);

	hWnd = CreateWindow(szAppName, szTitle,
		WS_OVERLAPPED | WS_SYSMENU | WS_BORDER | WS_CAPTION, 
		CW_USEDEFAULT, CW_USEDEFAULT, 
		cxWindow, cyWindow, 
		NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

void FindWindowSize(int *cxWindow, int *cyWindow)
{
	HDC				hdc;
	TEXTMETRIC		tm;

	hdc = CreateIC(TEXT("DISPLAY"), NULL, NULL, NULL);
	GetTextMetrics(hdc, &tm);
	DeleteDC(hdc);

	*cxWindow = 2 * GetSystemMetrics(SM_CXBORDER) + 12  * tm.tmMaxCharWidth;
	*cyWindow = 2 * GetSystemMetrics(SM_CYBORDER) + GetSystemMetrics(SM_CYCAPTION) + 2	* (tm.tmHeight+tm.tmExternalLeading);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HDC			hdcFullScreen;
	static COLORREF		color, colorPast;

	HDC				hdc;
	PAINTSTRUCT		ps;
	POINT	        ptCursor;
	TCHAR			szBuffer[120];
    RECT            rect;

	switch(uMsg)
	{
	case WM_CREATE:
		hdcFullScreen = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
		SetTimer(hwnd, TIMERID, 100, NULL);
		break;
    case WM_DISPLAYCHANGE:
        DeleteDC(hdcFullScreen);
		hdcFullScreen = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
        break;
	case WM_TIMER:
		GetCursorPos(&ptCursor);
        color = GetPixel(hdcFullScreen, ptCursor.x, ptCursor.y);

        if (color != colorPast)
        {
            colorPast = color; 
            InvalidateRect(hwnd, NULL, TRUE);
        }
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
        GetClientRect(hwnd, &rect);
		wsprintf(szBuffer, TEXT("%02X %02X %02X"), GetRValue(color), GetGValue(color), GetBValue(color)); 
        DrawText(hdc, szBuffer, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
        KillTimer(hwnd, TIMERID);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
