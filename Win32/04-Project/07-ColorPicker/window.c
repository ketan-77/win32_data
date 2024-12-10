#include <windows.h>
#include <stdio.h>
#include <windowsx.h> //for GET_X_LPARAM and GET_Y_LPARAM
#include "window.h"

// Global callback function
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HBITMAP hBitmap;

FILE* gpFile_Userlog;
FILE* gpFile_ColorPickerLog;
FILE* gpFile_ColorPickerLog_RTR;


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
    //func declaration
    BOOL createAndOpenAllLogFiles(void);
    void closeAllLogFiles(void);

    // Variable declarations
    HDC hdc, hMemdc;
    static PAINTSTRUCT ps;
    static RECT rect;
    TCHAR str[] = TEXT("HELLO WORLD");
    static unsigned int resizeWndWidth = 0, resizeWndHeight = 0;
    //color picking related variables
    static unsigned int pickedPixelXcord = 0, pickedPixelYcord = 0;
    static BOOL LMBUTTONPRESSED = FALSE;

    // Code
    switch (iMsg) {
        case WM_CREATE:
            ZeroMemory((void*)&ps, sizeof(PAINTSTRUCT));
            ZeroMemory((void*)&rect, sizeof(RECT));

            if (!createAndOpenAllLogFiles()) {
                MessageBox(hwnd, "Failed to open file", TEXT("ERROR"), MB_ICONERROR | MB_OK);
                DestroyWindow(hwnd);
            }

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
            hdc = BeginPaint(hwnd, &ps); // this should use in WM_PAINT only
        
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
            
            //get pixel color at (pickedPixelXcord, pickedPixelYcord)
            if(LMBUTTONPRESSED)
            {
                COLORREF pickedPixelColorRGB = GetPixel(hdc, pickedPixelXcord, pickedPixelYcord);
                unsigned int pickedPixelColorR = GetRValue(pickedPixelColorRGB);
                unsigned int pickedPixelColorG = GetGValue(pickedPixelColorRGB);
                unsigned int pickedPixelColorB = GetBValue(pickedPixelColorRGB);
                //make entry of the picked color RGB in color picker log file
                fprintf(gpFile_Userlog, "user picked a color.\n");

                fprintf(gpFile_ColorPickerLog, "User picked color RGB = (%u, %u, %u)\n", pickedPixelColorR, pickedPixelColorG, pickedPixelColorB);
                
                float normalizedRed = (float)(pickedPixelColorR/255.0f);
                float normalizedGreen = (float)(pickedPixelColorG/255.0f);
                float normalizedBlue = (float)(pickedPixelColorB/255.0f);

                fprintf(gpFile_ColorPickerLog_RTR, "User picked color RGB for RTR= (%f, %f, %f)\n", normalizedRed, normalizedGreen, normalizedRed);

                LMBUTTONPRESSED = FALSE;
            }
            // Clean up the memory device context
            if (hMemdc) {
                DeleteDC(hMemdc);
            }

            // End the painting process
            if(hdc)
                EndPaint(hwnd, &ps);
            break;
        case WM_LBUTTONDOWN: // for color picking
            LMBUTTONPRESSED = TRUE;
            pickedPixelXcord = GET_X_LPARAM(lParam);
            pickedPixelYcord = GET_Y_LPARAM(lParam);
            //Trigger WM_PAINT msg to repaint the image and to get the pixel at x and y cords
            InvalidateRect(hwnd, NULL, FALSE);
            break;
        case WM_KEYDOWN:
            switch (LOWORD(wParam))
            {
            default:
                break;
            }
            break;
        case WM_DESTROY:
            closeAllLogFiles();
            PostQuitMessage(0);
            break;
        default:
            break;
    }
    // Call the default window procedure
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

BOOL createAndOpenAllLogFiles(void){
    //create file ptr
    gpFile_Userlog = fopen("ksm_testUserlog.txt", "w");
    if (!gpFile_Userlog) {
        MessageBox(NULL, "Unable to get ptr for user logger", TEXT("ERROR"), MB_ICONERROR | MB_OK);
        return FALSE;
    }
    fprintf(gpFile_Userlog, "Program started.\n");
    fprintf(gpFile_Userlog, "User log file created and opened successfully.\n");

    gpFile_ColorPickerLog = fopen("ksm_testColorPickerLog.txt", "w");
    if (!gpFile_Userlog) {
        MessageBox(NULL, "Unable to get ptr for color picker logger", TEXT("ERROR"), MB_ICONERROR | MB_OK);
        fclose(gpFile_Userlog);
        return FALSE;
    }

    gpFile_ColorPickerLog_RTR = fopen("ksm_testColorPickerLog_RTR.txt", "w");
    if (!gpFile_Userlog) {
        MessageBox(NULL, "Unable to get ptr for color picker logger RTR", TEXT("ERROR"), MB_ICONERROR | MB_OK);
        fclose(gpFile_ColorPickerLog_RTR);
        fclose(gpFile_Userlog);
        return FALSE;
    }

    fprintf(gpFile_Userlog, "All log files are created and open successfully.\n");
    return TRUE;
}
void closeAllLogFiles(void){
   
    if (gpFile_ColorPickerLog_RTR) {
        fclose(gpFile_ColorPickerLog_RTR);
        gpFile_ColorPickerLog_RTR = NULL;
    }
    if (gpFile_ColorPickerLog) {
        fclose(gpFile_ColorPickerLog);
        gpFile_ColorPickerLog = NULL;
    }
    if (gpFile_Userlog) {
        fprintf(gpFile_Userlog, "program terminated successfully.\n");
        fclose(gpFile_Userlog);
        gpFile_Userlog = NULL;
    }
    fprintf(gpFile_Userlog, "All log files are closed.\n");
}