#include <windows.h>
#include <stdio.h>
#include "window.h"
#include <tchar.h>

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540

HINSTANCE hInst;

// global callback
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK OpenDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK EditDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);

// common dialog box to open image
HBITMAP GetFileName(HWND);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    // variable declaration
    WNDCLASSEX wndclass;
    HWND hwnd;
    MSG msg;
    TCHAR szClassName[] = TEXT("MyWindow_KM");

    // Initialize window class
    ZeroMemory((void *)&wndclass, sizeof(WNDCLASSEX));
    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.lpszClassName = szClassName;
    wndclass.lpszMenuName = "MyMenu";
    wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass.hInstance = hInstance;
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(KSM_ICON));
    wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(KSM_ICON));

    // Register the window class
    RegisterClassEx(&wndclass);

    // Create window in memory
    hwnd = CreateWindow(szClassName,
                        TEXT("Ketan Mundhe : First Window"),
                        WS_OVERLAPPEDWINDOW,
                        0,
                        0,
                        WINDOW_WIDTH,
                        WINDOW_HEIGHT,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);

    // Show the window on the desktop
    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    // Message loop
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// Window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = NULL;
    static HBITMAP hBitmap;
    static PAINTSTRUCT ps;
    static RECT rect;
    HDC hMemDc = NULL;
    TCHAR str[] = TEXT("Click on File Menu and Select 'Open' To open image file");
    static TCHAR fileName[500];
    static unsigned int resizeWndWidth = 0, resizeWndHeight = 0;

    switch (iMsg)
    {
    case WM_CREATE:
        ZeroMemory((void *)&ps, sizeof(PAINTSTRUCT));
        ZeroMemory((void *)&rect, sizeof(RECT));
        hInst = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
        break;
    case WM_PAINT:
        GetClientRect(hwnd, &rect);
        hdc = BeginPaint(hwnd, &ps);
        SetBkColor(hdc, RGB(0, 0, 0));
        SetTextColor(hdc, RGB(0, 255, 0));
        DrawText(hdc, str, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        if (hBitmap)
        {
            // Create a memory device context
            hMemDc = CreateCompatibleDC(hdc);
            SelectObject(hMemDc, hBitmap);

            // Set the stretch mode
            SetStretchBltMode(hdc, COLORONCOLOR);

            // Stretch the bitmap to fit the window size
            StretchBlt(hdc, 0, 0, resizeWndWidth, resizeWndHeight, hMemDc, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SRCCOPY);
            // Clean up
            DeleteDC(hMemDc);
        }

        EndPaint(hwnd, &ps);
        break;
    case WM_SIZE:
        resizeWndWidth = LOWORD(lParam);
        resizeWndHeight = HIWORD(lParam);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDM_OPEN:

            hBitmap = GetFileName(hwnd);

            InvalidateRect(hwnd, NULL, TRUE);
            break;
        case IDM_EXIT:
            PostQuitMessage(0);
            break;
        case IDM_EDIT:
            DialogBox(hInst, MAKEINTRESOURCE(DB_EDIT), hwnd, EditDlgProc);
            break;
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(DB_ABOUT), hwnd, AboutDlgProc);
            break;
        default:
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, iMsg, wParam, lParam);
    }
    return 0;
}

// Dialog procedure
BOOL CALLBACK OpenDlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            EndDialog(hwndDlg, IDOK);
            return TRUE;

        case IDCANCEL:
            EndDialog(hwndDlg, IDCANCEL);
            return TRUE;
        }
        break;
    }
    return FALSE;
}

BOOL CALLBACK EditDlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT rect;
    static HBRUSH hBrush = NULL;

    switch (message)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case WM_INITDIALOG:
            hBrush = CreateSolidBrush(RGB(255, 204, 153));
            GetWindowRect(GetDesktopWindow(), &rect);
            int screenWidth = rect.right;
            int screenHeight = rect.bottom;

            int posX = screenWidth - 300;
            int posY = 0;

            SetWindowPos(hwndDlg, HWND_TOP, posX, posY, 0, 0, SWP_NOSIZE);
            return TRUE;
        case IDOK:
            EndDialog(hwndDlg, IDOK);
            return TRUE;
        case IDEXIT:
            EndDialog(hwndDlg, IDEXIT);
            return TRUE;
        case IDABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(DB_ABOUT), hwndDlg, AboutDlgProc);
            return TRUE;
        }
        break;
    case WM_CTLCOLORDLG:
        // HDC hdcDlg = (HDC)wParam;
        // SetBkColor(hdcDlg, RGB(0, 0, 0));
        HBRUSH hBrush = CreateSolidBrush(RGB(135, 206, 235));
        return (LRESULT)hBrush;
    case WM_DESTROY:
        DeleteObject(hBrush);
        return TRUE;
    default:
        return FALSE;
    }
    return FALSE;
}

BOOL CALLBACK AboutDlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT rect;
    HDC hdc;
    PAINTSTRUCT ps;
    TCHAR str[] = TEXT("\nIMAGE EDITOR & COLOR PICKER \n\n\n A Project By : AstroMediComp \n Ketan Sunil Mundhe \n Email ID: ketanmundhe01@gmail.com\n");
    HICON hIcon;
    switch (message)
    {
    case WM_INITDIALOG:
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            EndDialog(hwndDlg, IDEXIT);
            return TRUE;
        }
        break;
    case WM_CTLCOLORDLG:
        HDC hdcDlg = (HDC)wParam;
        SetBkColor(hdcDlg, RGB(0, 0, 0));
        HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
        return (LRESULT)hBrush;
    case WM_PAINT:
        if (!(hdc = BeginPaint(hwndDlg, &ps)))
        {
            MessageBox(hwndDlg, TEXT("Begin paint failed in About Dlg Proc"), TEXT("ERROR"), MB_ICONERROR);
            return FALSE;
        }

        SetTextColor(hdc, RGB(255, 165, 0));
        SetBkColor(hdc, RGB(0, 0, 0));
        GetClientRect(hwndDlg, &rect);
        // DrawText(hdc, str, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        DrawText(hdc, str, -1, &rect, DT_CENTER | DT_VCENTER | DT_WORDBREAK);
        // if (!TextOut(hdc, 45, 45, "this is a test", 14))
        // {
        //     MessageBox(hwndDlg, TEXT("TextOut() failed"), TEXT("error"), MB_ICONERROR);
        //     return FALSE;
        // }
        EndPaint(hwndDlg, &ps);
        return TRUE;
    default:
        return FALSE;
    }
    return FALSE;
}

HBITMAP GetFileName(HWND hwnd)
{

    OPENFILENAME ofn;  // Common dialog box structure
    TCHAR szFile[260]; // Buffer for file name
    HBITMAP hBitMap = NULL;

    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = _T("All Files\0*.*\0");
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrTitle = _T("Select a File");
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Display the dialog box
    if (GetOpenFileName(&ofn) == TRUE)
    {
        // Extract the file name from the full path
        TCHAR *fileNamePtr = _tcsrchr(ofn.lpstrFile, '\\'); // Find the last '\\'

        if (fileNamePtr != NULL)
        {
            // Move the pointer past the '\\' to the actual file name
            fileNamePtr++; // Move pointer to the file name

            // Now, fileNamePtr points to the file name part of the path

            // You can now use fileNamePtr to do something, for example, copy it to another buffer
            TCHAR fileName[MAX_PATH];
            _tcscpy(fileName, fileNamePtr); // Copy the file name to a new buffer

            // Output the file name (you can use it further as needed)
            // MessageBox(hwnd, szFile, _T("Selected File"), MB_OK);

            hBitMap = (HBITMAP)LoadImage(hInst, szFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            if (!hBitMap)
            {
                MessageBox(hwnd, "Failed to load bitmap.", "Error", MB_OK | MB_ICONERROR);
                return 0;
            }

            return hBitMap;
        }
    }
    return hBitMap;
}
