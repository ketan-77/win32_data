#define UNICODE
#include <windows.h>
#include "ContainmentInnerComponentWithRegFile.h"

class CMulDivision : public IMultiplication, IDivision
{
private:
	long m_cRef;
public:
	CMulDivision(void);
	~CMulDivision(void);

	//IUknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*); //IMultiplication method
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*); //IDivision method
};

class CMulDivisionClassFactory : public IClassFactory
{
private:
	long m_cRef;
public:
	CMulDivisionClassFactory(void);
	~CMulDivisionClassFactory(void);

	//IUnknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IClassFactory specific method declaration
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

//global declarations
long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

//DllMain
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved) {
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	default:
		break;
	}

	return (TRUE);
}

//Implementation of CMulDivision's constructor method
CMulDivision::CMulDivision(void)
{
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);  //increment global counter
}

CMulDivision::~CMulDivision(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents); //decrement global count
}

HRESULT CMulDivision::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IMultiplication*>(this);
	else if (riid == IID_IMultiplication)
		*ppv = static_cast<IMultiplication*>(this);
	else if (riid == IID_IDivision)
		*ppv = static_cast<IDivision*>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	
	return (S_OK);
}
ULONG CMulDivision::AddRef(void) {
	InterlockedIncrement(&m_cRef);  //increment global counter
	return (m_cRef);
}

ULONG CMulDivision::Release(void) {
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0) {
		delete(this);
		return (0);
	}

	return (m_cRef);
}

//Implementation of IMultiplications,s method
HRESULT CMulDivision::MultiplicationOfTwoIntegers(int num1, int num2, int *pSum) {
	*pSum = num1 * num2;
	return (S_OK);
}
HRESULT CMulDivision::DivisionOfTwoIntegers(int num1, int num2, int *pSum) {
	*pSum = num1 / num2;
	return (S_OK);
}

//implementation of CMulDivisionrClassFactory's constructor
CMulDivisionClassFactory::CMulDivisionClassFactory(void) {
	m_cRef = 1; //hardcoded init to anticipate possible failure
}

CMulDivisionClassFactory::~CMulDivisionClassFactory(void) {
	//
}

HRESULT CMulDivisionClassFactory::QueryInterface(REFIID riid, void** ppv) {
	if (riid == IID_IUnknown) {
		*ppv = static_cast<IClassFactory*>(this);
	}
	else if (riid == IID_IClassFactory) {
		*ppv = static_cast<IClassFactory*>(this);
	}
	else {
		*ppv = NULL;
		return (E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();

	return (S_OK);
}

ULONG CMulDivisionClassFactory::AddRef(void) {
	InterlockedIncrement(&m_cRef);  //increment global counter
	return (m_cRef);
}

ULONG CMulDivisionClassFactory::Release(void) {
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0) {
		delete(this);
		return (0);
	}

	return (m_cRef);
}

//implementation of CMulDivisionClassFactory's IClassFactory's method
HRESULT CMulDivisionClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	//variable declaration
	CMulDivision *pCMulDivision = NULL;
	HRESULT hr;
	if (pUnkOuter != NULL) {
		return (CLASS_E_NOAGGREGATION);
	}
	//create the instance of component i.e. of CMulDivision
	pCMulDivision = new CMulDivision;
	if (pCMulDivision == NULL) {
		return (E_OUTOFMEMORY);
	}

	hr = pCMulDivision->QueryInterface(riid, ppv);
	pCMulDivision->Release();
	return (hr);
}

HRESULT CMulDivisionClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfActiveComponents);
	else
		InterlockedDecrement(&glNumberOfActiveComponents);

	return (S_OK);
}

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	CMulDivisionClassFactory *pCMulDivisionClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_MulDiv)
		return (CLASS_E_CLASSNOTAVAILABLE);

	pCMulDivisionClassFactory = new CMulDivisionClassFactory;
	if (pCMulDivisionClassFactory == NULL)
		return (E_OUTOFMEMORY);

	hr = pCMulDivisionClassFactory->QueryInterface(riid, ppv);
	pCMulDivisionClassFactory->Release();

	return (hr);
}

extern "C" HRESULT __stdcall DLLCanUnloadNow(void) {
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return (S_OK);
	else
		return (S_FALSE);
}
	