#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	TCHAR *szClassName	= TEXT("MapMode");
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
						TEXT("Test Map Mode"), 
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
	while(GetMessage(&msg, hwnd, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static int cxClient, cyClient;
	HDC hdc;
	SIZE sizeView, sizeWindow;
	PAINTSTRUCT ps;
	switch(uMsg)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		SetMapMode(hdc, MM_ISOTROPIC);
		SetWindowExtEx(hdc, 4096, 1024, NULL);
		SetViewportExtEx(hdc, cxClient, -cyClient, NULL);
		SetViewportOrgEx(hdc, 0, cyClient, NULL);
		GetWindowExtEx(hdc, &sizeWindow);
		GetViewportExtEx(hdc, &sizeView);

		TextOut(hdc, sizeWindow.cx / 2, sizeWindow.cy/2, TEXT("HELLO"), 5);
		EndPaint(hWnd, &ps);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}