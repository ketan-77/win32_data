#include <windows.h>

BOOL WINAPI DllMain(HMODULE hDll, DWORD dwReason, LPVOID lpReserved) {
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
}

extern "C" int MakeCube(int n) {
	void checkNumber(int);

//code
	checkNumber(n);
	return (n * n * n);
}

extern "C" void checkNumber(int n) {
	if (n < 0) {
		MessageBox(NULL, TEXT("Number is -ve"), TEXT("Check Number"), MB_ICONWARNING);
	}
}
