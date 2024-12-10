#include <windows.h>
#include "window.h"

#define WINDOW_WIDTH  960
#define WINDOW_HEIGHT 540

//global callback
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK OpenDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK EditDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
                                                                                        
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {
    //variable declaration
    WNDCLASSEX wndclass;
    HWND hwnd;
    MSG msg;
    TCHAR szClassName[] = TEXT("MyWindow_KM");

    // Initialize window class
    ZeroMemory((void*)&wndclass, sizeof(WNDCLASSEX));
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
    /*
    HMENU hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hEditMenu = CreateMenu();
    HMENU hHelpMenu = CreateMenu();

    // File menu options
    AppendMenu(hFileMenu, MF_STRING, FILE_OPEN, TEXT("&Open"));
    AppendMenu(hFileMenu, MF_STRING, FILE_EXIT, TEXT("&Exit"));

    AppendMenu(hEditMenu, MF_STRING, EDIT_EDIT, TEXT("&Edit"));

    // Help menu options
    AppendMenu(hHelpMenu, MF_STRING, HELP_ABOUT, TEXT("&About"));

    // Append to the menu bar
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, TEXT("&File"));
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hEditMenu, TEXT("&Edit"));
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, TEXT("&Help"));
*/
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
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// Window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
    HDC hdc = NULL;
    HINSTANCE hInst;
    static PAINTSTRUCT ps;
    static RECT rect;
    TCHAR str[] = TEXT("Click on File Menu and Select 'Open' To open image file");

    switch (iMsg) {
    case WM_CREATE:
        ZeroMemory((void*)&ps, sizeof(PAINTSTRUCT));
        ZeroMemory((void*)&rect, sizeof(RECT));
        hInst = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);

        break;
    case WM_PAINT:
        GetClientRect(hwnd, &rect);
        hdc = BeginPaint(hwnd, &ps);
        SetBkColor(hdc, RGB(0, 0, 0));
        SetTextColor(hdc, RGB(0, 255, 0));
        DrawText(hdc, str, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        EndPaint(hwnd, &ps);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
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
BOOL CALLBACK OpenDlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDOK:
            MessageBox(hwndDlg, TEXT("Ok on dialog box"), TEXT("OK"), MB_OK);
            EndDialog(hwndDlg, IDOK);
            return TRUE;

        case IDCANCEL:
            MessageBox(hwndDlg, TEXT("Cancel on dialog box"), TEXT("CANCEL"), MB_OK);
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
    switch (message) {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case WM_INITDIALOG:
            GetWindowRect(GetDesktopWindow(), &rect);
            int screenWidth = rect.right;
            int screenHeight = rect.bottom;

            int posX = screenWidth - 300;
            int posY = 0;

            SetWindowPos(hwndDlg, HWND_TOP, posX, posY, 0, 0, SWP_NOSIZE);
            return TRUE;
        case IDOK:
            MessageBox(hwndDlg, TEXT("Ok on edit dialog box"), TEXT("OK"), MB_OK);
            EndDialog(hwndDlg, IDOK);
            return TRUE;
        case IDEXIT:
            MessageBox(hwndDlg, TEXT("EXIT on edit dialog box"), TEXT("EXIT"), MB_OK);
            EndDialog(hwndDlg, IDEXIT);
            return TRUE;
        case IDABOUT:
            MessageBox(hwndDlg, TEXT("About on edit dialog box"), TEXT("ABOUT"), MB_OK);
            EndDialog(hwndDlg, IDABOUT);
            return TRUE;
        }
        break;
    }
    return FALSE;
}

//BOOL CALLBACK AboutDlgProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    switch (message) {
//    case WM_COMMAND:
//        switch (LOWORD(wParam)) {
//        case IDOK:
//            MessageBox(hwndDlg, TEXT("Ok on edit dialog box"), TEXT("OK"), MB_OK);
//            EndDialog(hwndDlg, IDOK);
//            return TRUE;
//        case IDEXIT:
//            MessageBox(hwndDlg, TEXT("EXIT on edit dialog box"), TEXT("EXIT"), MB_OK);
//            EndDialog(hwndDlg, IDEXIT);
//            return TRUE;
//        case IDABOUT:
//            MessageBox(hwndDlg, TEXT("About on edit dialog box"), TEXT("ABOUT"), MB_OK);
//            EndDialog(hwndDlg, IDABOUT);
//            return TRUE;
//        }
//        break;
//    }
//    return FALSE;
//}
