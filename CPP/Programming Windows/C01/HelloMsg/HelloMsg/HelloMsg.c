#include <windows.h>

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpComdLine, int nShowCmd)
{
	MessageBox(NULL, TEXT("Hello, world!"), TEXT("HelloMsg"), MB_OK);
	return 0;
}