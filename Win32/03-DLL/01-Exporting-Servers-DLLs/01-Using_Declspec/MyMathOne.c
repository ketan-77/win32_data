#include <Windows.h>

//DLL's entry point function
BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	default:
		break;
	}

	return TRUE;
}

//define DLL's functionality
//Function to be exported
__declspec(dllexport) int MakeSquare(int n) {
	void checkNumber(int n);

	//code
	checkNumber(n);
	return (n * n);
}

//Function(s) for Dll's internal usage
void checkNumber(int n) {
	if (n < 0) {
		MessageBox(NULL, TEXT("Number is negative"), TEXT("Check Number"), MB_ICONWARNING);
	}
}