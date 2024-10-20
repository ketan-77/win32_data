#define UNICODE
//changes are with respect to ClassFactoryDLLServer - 16 changes ( 14 in cpp 1 - header and 1 - Reg file)
#include <windows.h>
#include <stdio.h> // for swprintf_s()
#include "AutomationServer.h" 

//coclass declaration

class CMyMath : public IMyMath
{
private:
	long m_cRef;
	ITypeInfo* m_pITypeInfo;
public:
	//constructor
	CMyMath(void);
	//destructor
	~CMyMath(void);

	//IUknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IDispatch specific method declaration (inherited)
	HRESULT __stdcall GetTypeInfoCount(UINT*);
	HRESULT __stdcall GetTypeInfo(UINT, LCID, ITypeInfo**); //LCID - Local ID
	HRESULT __stdcall GetIDsOfNames(REFIID, LPOLESTR*, UINT, LCID, DISPID*); //DISPID - Dispatch ID, LPOLESTR is COM specific string (long ptr OLE string)
	HRESULT __stdcall Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*);
	//WORD - 16 bit integer, DISPPARAMS - Dispatch parameters, EXCEPINFO - Info related Exception 


	//IMyMath Methods
	HRESULT __stdcall SumOfTwoIntegers(int, int, int*); 
	HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*); 

	//custom method
	HRESULT InitInstance(void);
};

class CMyMathClassFactory : public IClassFactory
{
private:
	long m_cRef;
public:
	CMyMathClassFactory(void);
	~CMyMathClassFactory(void);

	//IUknown specific method declarations (inherited)
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IClassFactory specific method declaration
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

//global declarations
HMODULE	ghModule = NULL; //this is req for exe server

long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

// {7039A875-84C0-4AD5-917A-8A332600052E} - used for TLB
const GUID LIBID_AutomtionServer = {
	0x7039a875, 0x84c0, 0x4ad5, 0x91, 0x7a, 0x8a, 0x33, 0x26, 0x0, 0x5, 0x2e
};

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

//Implementation of CMyMath's constructor method
CMyMath::CMyMath(void)
{
	m_cRef = 1;
	m_pITypeInfo = NULL;
	//hardcoded init to anticipate possible failure of QI()
	InterlockedIncrement(&glNumberOfActiveComponents);  //increment global counter
}

CMyMath::~CMyMath(void)
{
	if (m_pITypeInfo) {
		m_pITypeInfo->Release();
		m_pITypeInfo = NULL;;
	}
	InterlockedDecrement(&glNumberOfActiveComponents); //decrement global count
}

HRESULT CMyMath::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IMyMath*>(this);
	else if (riid == IID_IDispatch)
		*ppv = static_cast<IMyMath*>(this);
	else if (riid == IID_IMyMath)
		*ppv = static_cast<IMyMath*>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	
	return (S_OK);
}
ULONG CMyMath::AddRef(void) {
	InterlockedIncrement(&m_cRef);  //increment global counter
	return (m_cRef);
}

ULONG CMyMath::Release(void) {
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0) {
		delete(this);
		return (0);
	}

	return (m_cRef);
}

//Implementation of IMyMath's method
HRESULT CMyMath::SumOfTwoIntegers(int num1, int num2, int *pSum) {
	*pSum = num1 + num2;
	return (S_OK);
}
HRESULT CMyMath::SubtractionOfTwoIntegers(int num1, int num2, int *pSum) {
	*pSum = num1 - num2;
	return (S_OK);
}

//implementation of CMyMathClassFactory's constructor
CMyMathClassFactory::CMyMathClassFactory(void) {
	m_cRef = 1; //hardcoded init to anticipate possible failure
}

CMyMathClassFactory::~CMyMathClassFactory(void) {
	//
}

HRESULT CMyMathClassFactory::QueryInterface(REFIID riid, void** ppv) {
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

ULONG CMyMathClassFactory::AddRef(void) {
	InterlockedIncrement(&m_cRef);  //increment global counter
	return (m_cRef);
}

ULONG CMyMathClassFactory::Release(void) {
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0) {
		delete(this);
		return (0);
	}

	return (m_cRef);
}

//implementation of CSumSubstractClassFactory's IClassFactory's method
HRESULT CMyMathClassFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	//variable declaration
	CMyMath *pCMyMath = NULL;
	HRESULT hr;
	if (pUnkOuter != NULL) {
		return (CLASS_E_NOAGGREGATION);
	}
	//create the instance of component i.e. of CSumSubtract
	pCMyMath = new CMyMath;
	if (pCMyMath == NULL) {
		return (E_OUTOFMEMORY);
	}

	hr = pCMyMath->QueryInterface(riid, ppv);
	pCMyMath->Release();
	return (hr);
}

HRESULT CMyMathClassFactory::LockServer(BOOL fLock)
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
	