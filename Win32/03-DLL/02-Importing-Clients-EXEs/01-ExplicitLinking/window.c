#include <windows.h>
#include "window.h"

//global callback
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {
	//variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("MyWindow_KM");

	//code
	ZeroMemory((void*)&wndclass, sizeof(WNDCLASSEX));
	//Initializing window classs
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szClassName;
	wndclass.lpszMenuName = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hInstance = hInstance;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(KSM_ICON));
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(KSM_ICON));

	//Register the above window class			
	RegisterClassEx(&wndclass);

	//create window in memory
	hwnd = CreateWindow(szClassName,
		TEXT("Ketan Mundhe : First Widnow"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	//Show the window on the desktop
	ShowWindow(hwnd, iCmdShow);

	//Update /Paint the window on the desktop
	UpdateWindow(hwnd);
	/* [zorder rule / topmost order rule] - if any window
	overlapping the topmost window gets priority */

	//Message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);

}

//Window procedure(wndproc)
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//variable declarations
	HDC hdc = NULL;
	TCHAR str[] = TEXT("HELLO WORLD");
	typedef int (*MakeCubePtr)(int);
	MakeCubePtr fnPtr = NULL;
	int cube = 0, num = 7;
	HMODULE hDll = NULL;
	//code
	switch (iMsg)
	{
	case WM_CREATE:
		//step 1: Load the desired DLL explicitly
		hDll = LoadLibrary(TEXT("MyMathTwo.dll"));
		if (hDll == NULL) {
			MessageBox(hwnd, TEXT("load lib failed"), TEXT("ERROR"), MB_ICONERROR);
			DestroyWindow(hwnd);
		}
		/* Name of function is address of function
			step 2: Get address of desired function from loaded DLL
		*/
		fnPtr = (MakeCubePtr)GetProcAddress(hDll, "MakeCube");
		//1st param - tells from where we have to find the function
		//2nd param - function that we have to find
		// FARPROC return type 
		if (fnPtr == NULL) {
			FreeLibrary(hDll);
			hDll = NULL;
			MessageBox(hwnd, TEXT("Failed - GetProcAddress"), TEXT("ERROR"), MB_ICONERROR);
			DestroyWindow(hwnd);
		}
		//step 3: Now call the function pointer(fnPtr) just as if calling MakeCube()
		cube = fnPtr(num);
		wsprintf(str, TEXT("Cube of %d is %d"), num, cube);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		//step 4: Free library
		if (hDll) {
			FreeLibrary(hDll);
			hDll = NULL;
		}
		fnPtr = NULL;
		DestroyWindow(hwnd);
		break;
	case WM_SIZE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	//calling default window procedure
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}