#include <windows.h>
#include "window.h"

//global callback
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HBITMAP hBitmap;

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
	hBitmap = (HBITMAP)LoadImage(NULL, "image.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (!hBitmap) {
		MessageBox(hwnd, "Failed to load bitmap.", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

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
	// Cleanup
	if (hBitmap) {
		DeleteObject(hBitmap);
	}

	return((int)msg.wParam);

}

//Window procedure(wndproc)
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//variable declarations
	HDC hdc = NULL, hMemdc;
	static PAINTSTRUCT ps;
	static RECT rect;
	TCHAR str[] = TEXT("HELLO WORLD");
	static unsigned int resizeWndWidth = 0, resizeWndHeight = 0;
	unsigned int yRow = 0, xColumn = 0;

	//code
	switch (iMsg)
	{
	case WM_CREATE:
		ZeroMemory((void*)&ps, sizeof(PAINTSTRUCT));
		ZeroMemory((void*)&rect, sizeof(RECT));
		hBitmap = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(KSM_BITMAP));
		if (hBitmap == NULL) {
			MessageBox(hwnd, "Failed to load bitmap from resources.", "Error", MB_OK | MB_ICONERROR);
		}
		break;
	case WM_SIZE:
		resizeWndWidth = LOWORD(lParam);
		resizeWndHeight = HIWORD(lParam);
		break;
	case WM_PAINT:
		//get the client area rectangle of window
		GetClientRect(hwnd, &rect);
		//get handle to device context

		hdc = BeginPaint(hwnd, &ps);
		hMemdc = CreateCompatibleDC(hdc);
		//tell hdc to set background color
		SetBkColor(hdc, RGB(0, 0, 255));
		SetTextColor(hdc, RGB(0, 255, 0));
		DrawText(hdc, str, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		
		SelectObject(hMemdc, hBitmapRec);
		SetStretchBltMode(hdc, COLORONCOLOR);
		StretchBlt(hdc, 0, 0, resizeWndWidth, resizeWndHeight, hMemdc, 0, 0, 800, 600, SRCCOPY);
		
		//pixel by pixel desaturation nested loop

		if(hMemdc)
			DeleteDC(hMemdc);
		EndPaint(hwnd, &ps);

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