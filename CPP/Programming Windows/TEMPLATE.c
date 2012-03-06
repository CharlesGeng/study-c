#include <windows.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nShowCmd)
{
    //TODO: Application name
	TCHAR       *szAppName  = TEXT("");
    //TODO: Widow's title
	TCHAR       *szTitle    = TEXT("");
	WNDCLASS    wc;
	HWND        hWnd;
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

	switch(uMsg)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
