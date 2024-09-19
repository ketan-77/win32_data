#define UNICODE
#include <windows.h>
#include "ContainmentOuterComponentWithregFile.h"
#include "ContainmentInnerComponentWithRegFile.h"

class CSumSubtract : public ISum, ISubtract, IMultiplication, IDivision
{
private:
	long m_cRef;
	IMultiplication* m_pIMultiplication;
	IDivision* m_pIDivision;
public:
	CSumSubtract(void);
	~CSumSubtract(void);

	//IUknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall SumOfTwoIntegers(int, int, int*); //ISum method
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*); //ISubctract method

	HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*); //IMultiplcation method
	HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*); //IDivision method
	HRESULT __stdcall InitializeInnerComponent(void);

};

class CSumSubtractClassFactory : public IClassFactory
{
private:
	long m_cRef;
public:
	CSumSubtractClassFactory(void);
	~CSumSubtractClassFactory(void);

	//IUknown specific method declarations (inherited)
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

//Implementation of CSumSubtract's constructor method
CSumSubtract::CSumSubtract(void)
{
	//init private data member
	m_pIMultiplication = NULL;
	m_pIDivision = NULL;
	m_cRef = 1;

	InterlockedIncrement(&glNumberOfActiveComponents);  //increment global counter
}

CSumSubtract::~CSumSubtract(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents); //decrement global count
	if (m_pIDivision) 
	{
		m_pIDivision->Release();
		m_pIDivision = NULL;
	}
	
	if(m_pIMultiplication)
	{
		m_pIMultiplication->Release();
		m_pIMultiplication = NULL;
	}
}

HRESULT CSumSubtract::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum*>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract*>(this);
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
ULONG CSumSubtract::AddRef(void) {
	InterlockedIncrement(&m_cRef);  //increment global counter
	return (m_cRef);
}

ULONG CSumSubtract::Release(void) {
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0) {
		delete(this);
		return (0);
	}

	return (m_cRef);
}

//Implementation of ISum,s method
HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int *pSum) {
	*pSum = num1 + num2;
	return (S_OK);
}
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int *pSum) {
	*pSum = num1 - num2;
	return (S_OK);
}

HRESULT __stdcall CSumSubtract::MultiplicationOfTwoIntegers(int num1, int num2, int *pMultiplication) {
	m_pIMultiplication->MultiplicationOfTwoIntegers(num1, num2, pMultiplication);
	return S_OK;
}

HRESULT __stdcall CSumSubtract::DivisionOfTwoIntegers(int num1, int num2, int* pDivision) {
	m_pIDivision->DivisionOfTwoIntegers(num1, num2, pDivision);
	return S_OK;
}

HRESULT __stdcall CSumSubtract::InitializeInnerComponent(void) {
	HRESULT hr;
	
	hr = CoCreateInstance(CLSID_MulDiv, NULL, CLSCTX_INPROC_SERVER, IID_IMultiplication, (void**)&m_pIMultiplication);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("IMultiplication interface can not be obtained from inner component"), TEXT("Inner Server Error"), MB_ICONERROR);
		return E_FAIL;
	}
	hr = m_pIMultiplication->QueryInterface(IID_IDivision, (void**)&m_pIDivision);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("IDivision interface can not be obtained from inner component"), TEXT("Inner Server Error"), MB_ICONERROR);
		m_pIMultiplication->Release();
		m_pIMultiplication = NULL;
		return E_FAIL;
	}
	return S_OK;
}


//implementation of CSumSubtractrClassFactory's constructor
CSumSubtractClassFactory::CSumSubtractClassFactory(void) {
	m_cRef = 1; //hardcoded init to anticipate possible failure
}

CSumSubtractClassFactory::~CSumSubtractClassFactory(void) {
	//
}

HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void** ppv) {
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

ULONG CSumSubtractClassFactory::AddRef(void) {
	InterlockedIncrement(&m_cRef);  //increment global counter
	return (m_cRef);
}

ULONG CSumSubtractClassFactory::Release(void) {
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0) {
		delete(this);
		return (0);
	}

	return (m_cRef);
}

//implementation of CSumSubstractClassFactory's IClassFactory's method
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	//variable declaration
	CSumSubtract *pCSumSubtract = NULL;
	HRESULT hr;
	if (pUnkOuter != NULL) {
		return (CLASS_E_NOAGGREGATION);
	}
	//create the instance of component i.e. of CSumSubtract
	pCSumSubtract = new CSumSubtract;
	if (pCSumSubtract == NULL) {
		return (E_OUTOFMEMORY);
	}

	hr = pCSumSubtract->InitializeInnerComponent();
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("Failed to Init Inner Component"), TEXT("Inner Server Error"), MB_ICONERROR);
		pCSumSubtract->Release();
		return hr;
	}


	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release();
	pCSumSubtract = NULL;
	return (hr);
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfActiveComponents);
	else
		InterlockedDecrement(&glNumberOfActiveComponents);

	return (S_OK);
}

extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	CSumSubtractClassFactory *pCSumSubtractClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_SumSubtract)
		return (CLASS_E_CLASSNOTAVAILABLE);

	pCSumSubtractClassFactory = new CSumSubtractClassFactory;
	if (pCSumSubtractClassFactory == NULL)
		return (E_OUTOFMEMORY);

	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release();

	return (hr);
}

extern "C" HRESULT __stdcall DLLCanUnloadNow(void) {
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return (S_OK);
	else
		return (S_FALSE);
}
	