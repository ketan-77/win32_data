#include<windows.h>
#include"window.h"
#include "ClassFactoryDllServerWithRegFile.h"


//global callback declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Global variables
ISum *pISum = NULL;
ISubtract *pISubtract = NULL;

//Entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {
	//variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("MyWindow_km");
	//TCHAR typedef to WCHAR
	HRESULT hr = S_OK;

	//code
	hr = CoInitialize(NULL);
	if(FAILED(hr))
	{
		MessageBox(NULL, TEXT("CoInit Failed"), TEXT("COM ERROR"), MB_ICONERROR);
		exit(0);
	}

	ZeroMemory((void*)&wndclass, sizeof(WNDCLASSEX)); //memory set to 0 
	
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
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	CoUninitialize();
	return((int)msg.wParam);
}

//Window procedure(wndproc)
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//Function declaration
	void SafeInterfaceRelease(void);

	//variable declaration
	HRESULT hr = S_OK;
	int iNum1, iNum2, iSum;
	TCHAR str[255];

	//code
	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);
		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("ISum Interface didn't obtained"), TEXT("COM ERROR"), MB_ICONERROR);
			DestroyWindow(hwnd);
		}
		MessageBox(NULL, TEXT("ISum Interface obtained"), TEXT("COM SUCCESS"), MB_ICONINFORMATION);
		//init var
		iNum1 = 55;
		iNum2 = 51;

		pISum->SumOfTwoIntegers(iNum1, iNum2, &iSum);
		wsprintf(str, TEXT("Sum of %d And %d = %d"), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);

		//call QueryInterface() on ISum to get ISubtract's pointer
		hr = pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);
		if (FAILED(hr))
		{
			MessageBox(NULL, TEXT("ISubtract Interface didn't obtained"), TEXT("COM ERROR"), MB_ICONERROR);
			DestroyWindow(hwnd);
		}

		//As we don't req ISum Release it
		pISum->Release();
		pISum = NULL;

		//
		iNum1 = 155;
		iNum2 = 51;
		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iSum);
		wsprintf(str, TEXT("Subtraction of %d And %d = %d"), iNum1, iNum2, iSum);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK);
		pISubtract->Release();
		pISubtract = NULL;

		DestroyWindow(hwnd); //send WM_DESTROY
		break;
	case WM_DESTROY:
		SafeInterfaceRelease();
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	//calling default window procedure
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void SafeInterfaceRelease(void)
{
	//code
	if (pISubtract)
	{
		pISubtract->Release();
		pISubtract = NULL;
	}
	if (pISum)
	{
		pISum->Release();
		pISum = NULL;
	}
}