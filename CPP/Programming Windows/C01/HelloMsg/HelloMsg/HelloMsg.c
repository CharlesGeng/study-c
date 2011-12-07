#include<Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE HPrevInstance, PSTR szCMDLine, int iCmdShow)
{
	MessageBox(NULL, TEXT("Hello, World!"), TEXT("HelloMsg"), 0);
	return 0;
}