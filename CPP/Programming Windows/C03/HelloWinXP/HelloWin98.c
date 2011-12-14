#include <windows.h>
#include <TCHAR.h>
#include <stdio.h>

LRESULT CALLBACK WndProc( HWND , UINT , WPARAM , LPARAM );

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	static TCHAR szAppName[] = TEXT("���Win98");
	HWND hwndMain; 
	HWND hwndsub;
	WNDCLASS wc;
	MSG msg ;

	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);		//����ͼ��
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			//�������
	wc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);	//��ȡͼ�ζ���
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= szAppName;

	if (!RegisterClass(&wc))	//ע�ᴰ����
	{
		MessageBox(NULL, TEXT("Register Window Class Structure Error!"), TEXT("ERROR"), MB_ICONERROR);
		return 0;
	}

	//�������ڴ�����Ĵ���
	hwndMain = CreateWindow(szAppName,
						TEXT("The Hello Program"), 
						WS_OVERLAPPEDWINDOW, 
						CW_USEDEFAULT, 
						CW_USEDEFAULT,
						CW_USEDEFAULT, 
						CW_USEDEFAULT,
						NULL, 
						NULL, 
						hInstance, 
						NULL);
	ShowWindow(hwndMain, nShowCmd);
	UpdateWindow(hwndMain);

	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	static int count = 0;
	PAINTSTRUCT ps;
	RECT rect;

	switch(uMsg)
	{
		case WM_CREATE:
		{
			PlaySound(TEXT("HelloWindows"), NULL, SND_FILENAME | SND_ASYNC);
			return 0;
		}
		case WM_PAINT:
		{
			HDC hdc = BeginPaint(hwnd, &ps);
			if (count % 2 == 0)
			{
				GetClientRect(hwnd, &rect);
				DrawText(hdc, TEXT("Hello Windows 98"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			}
			count++;
			EndPaint(hwnd, &ps);
			return 0;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		default:
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
	return 0;
}