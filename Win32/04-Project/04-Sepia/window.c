#include <windows.h>
#include "window.h"

// Global callback function
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HBITMAP hBitmap;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {
    // Variable declaration
    WNDCLASSEX wndclass;
    HWND hwnd;
    MSG msg;
    TCHAR szClassName[] = TEXT("MyWindow_KM");

    // Code
    ZeroMemory((void*)&wndclass, sizeof(WNDCLASSEX));
    // Initializing window class
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

    // Create window in memory
    hwnd = CreateWindow(szClassName,
        TEXT("Ketan Mundhe : First Window"),
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

    // Update/Paint the window on the desktop
    UpdateWindow(hwnd);

    // Message loop
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// Window procedure (WndProc)
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
    // Variable declarations
    HDC hdc, hMemdc;
    static PAINTSTRUCT ps;
    static RECT rect;
    TCHAR str[] = TEXT("HELLO WORLD");
    static unsigned int resizeWndWidth = 0, resizeWndHeight = 0;
    unsigned int yRow = 0, xColumn = 0;
    static BOOL keyPressed = FALSE;

    // Code
    switch (iMsg) {
        case WM_CREATE:
            //MessageBox(NULL, TEXT("before"), TEXT("success"), MB_OK);
            hBitmap = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(KSM_BITMAP));
            if (!hBitmap) {
                TCHAR str[256];
                wsprintf(str, TEXT("Failed to load bit map (%d)"), MAKEINTRESOURCE(KSM_BITMAP));
                MessageBox(NULL, str, TEXT("ERROR"), MB_ICONERROR | MB_OK);
            }
            else
                MessageBox(NULL, TEXT("loaded"), TEXT("success"), MB_OK);
        
            break;
        case WM_SIZE:
            resizeWndWidth = LOWORD(lParam);
            resizeWndHeight = HIWORD(lParam);
            break;
        case WM_PAINT:
            // Get handle to device context
            hdc = BeginPaint(hwnd, &ps);
        
            // Get the client area rectangle of window
            GetClientRect(hwnd, &rect);
       
            hMemdc = CreateCompatibleDC(hdc);
            // Set background and text colors
            SetBkColor(hdc, RGB(0, 0, 255));
            SetTextColor(hdc, RGB(0, 255, 0));

            // Draw the text in the window
            DrawText(hdc, str, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            // Select bitmap into memory device context (hMemdc)
            SelectObject(hMemdc, hBitmap);

            // Set the stretch mode
            SetStretchBltMode(hdc, COLORONCOLOR);

            // Stretch the bitmap to fit the window size
            StretchBlt(hdc, 0, 0, resizeWndWidth, resizeWndHeight, hMemdc, 0, 0, 640, 426, SRCCOPY);

            if (keyPressed) {
                for (yRow = 0; yRow < resizeWndWidth; yRow++) {
                    for (xColumn = 0; xColumn < resizeWndHeight; xColumn++)
                    {
                        //get color from the pixel at coord (xCol, yRow)
                        COLORREF originalPixelColor = GetPixel(hdc, xColumn, yRow);
                        unsigned int ogR = GetRValue(originalPixelColor);
                        unsigned int ogG = GetGValue(originalPixelColor);
                        unsigned int ogB = GetBValue(originalPixelColor);
        
                        unsigned int sepiaR = (unsigned int)(((float)ogR * 0.393f) + ((float)ogG * 0.769f) + ((float)ogB * 0.189f));
                        sepiaR > 255 ? 255 : sepiaR;
                       
                        unsigned int sepiaG = (unsigned int)(((float)ogR * 0.349f) + ((float)ogG * 0.686f) + ((float)ogB * 0.168f));
                        sepiaG > 255 ? 255 : sepiaG;
                        
                        unsigned int sepiaB = (unsigned int)(((float)ogR * 0.272f) + ((float)ogG * 0.534f) + ((float)ogB * 0.189f));
                        sepiaB > 255 ? 255 : sepiaB;

                        //add all ds component to get final ds color for the pixel
                        unsigned int sepeiaColor; 
                        COLORREF sepiaColor = RGB(sepiaR, sepiaB, sepiaG);
                        SetPixel(hdc, xColumn, yRow, sepiaColor);
                    }
                }
            }

            // Clean up the memory device context
            if (hMemdc) {
                DeleteDC(hMemdc);
            }

            // End the painting process
            EndPaint(hwnd, &ps);
            break;
        case WM_KEYDOWN:
            switch (LOWORD(wParam))
            {
                case VK_SPACE:
                    keyPressed = TRUE;
                    InvalidateRect(hwnd, NULL, TRUE);
                    break;
                default:
                    break;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            break;
    }
    // Call the default window procedure
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
