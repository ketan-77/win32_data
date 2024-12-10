#include <windows.h>
#include "window.h"
#include <sapi.h> //speech api

// global callback
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// declaring interface pointer for SAPI
ISpVoice *pISpVoice = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("MyWindow_KM");
	HRESULT hr = S_OK;

	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("CoInit Failed"), TEXT("ERROR"), MB_ICONERROR);
		exit(0);
	}

	// code
	ZeroMemory((void *)&wndclass, sizeof(WNDCLASSEX));
	// Initializing window classs
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

	// Register the above window class
	RegisterClassEx(&wndclass);

	// create window in memory
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

	// Show the window on the desktop
	ShowWindow(hwnd, iCmdShow);

	// Update /Paint the window on the desktop
	UpdateWindow(hwnd);
	/* [zorder rule / topmost order rule] - if any window
	overlapping the topmost window gets priority */

	// Message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	CoUninitialize();

	return ((int)msg.wParam);
}

// Window procedure(wndproc)
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void safeInterfaceRelease(void);
	// variable declarations
	HDC hdc = NULL;
	static PAINTSTRUCT ps;
	static RECT rect;
	TCHAR str[] = TEXT("HELLO WORLD");
	HRESULT hr = S_OK;
	wchar_t speechText[] = L"Hello Ketan Sunil Mundhe! from WinDev2024 Batch, Roll No 32";
	// code
	switch (iMsg)
	{
	case WM_CREATE:
		ZeroMemory((void *)&ps, sizeof(PAINTSTRUCT));
		ZeroMemory((void *)&rect, sizeof(RECT));
		hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_INPROC_SERVER, IID_ISpVoice, (void **)&pISpVoice);
		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("CoCreateInstance Failed to obtain ISpVoice Interface"), TEXT("ERROR"), MB_ICONERROR);
			DestroyWindow(hwnd);
		}
		break;
	case WM_SIZE:
		break;
	case WM_PAINT:
		// get the client area rectangle of window
		GetClientRect(hwnd, &rect);
		// get handle to device context
		hdc = BeginPaint(hwnd, &ps);
		// tell hdc to set background color
		SetBkColor(hdc, RGB(0, 0, 255));
		SetTextColor(hdc, RGB(0, 255, 0));

		DrawText(hdc, str, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		EndPaint(hwnd, &ps);

		break;
	case WM_LBUTTONDOWN:
		pISpVoice->Speak(speechText, 0, NULL);
		break;
	case WM_DESTROY:
		safeInterfaceRelease();
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	// calling default window procedure
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void safeInterfaceRelease(void)
{
	if (pISpVoice)
	{
		pISpVoice->Release();
		pISpVoice = NULL;
	}
}