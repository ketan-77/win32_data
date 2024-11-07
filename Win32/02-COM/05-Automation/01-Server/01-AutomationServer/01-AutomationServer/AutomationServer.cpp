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
	ITypeInfo* m_pITypeInfo = NULL;
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
		m_pITypeInfo->Release();
		m_pITypeInfo = NULL;
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

HRESULT CMyMath::InitInstance(void)
{
	void ComErrorDescriptionString(HWND, HRESULT);

	//
	HRESULT hr;
	ITypeLib* pITypeLib = NULL;

	if (m_pITypeInfo == NULL)
	{
		hr = LoadRegTypeLib( //this is com helper function
			LIBID_AutomtionServer, // 
			1, 0, //major and minor (versioning)
			0x00, //which language and country (locale) - default - en-US
			&pITypeLib //to load type library
		);

		if (FAILED(hr))
		{
			ComErrorDescriptionString(NULL, hr);
			return (hr);
		}
	
		hr = pITypeLib->GetTypeInfoOfGuid(IID_IMyMath, &m_pITypeInfo);
		if (FAILED(hr))
		{
			ComErrorDescriptionString(NULL, hr);
			pITypeLib->Release();
			return (hr);
		}

		pITypeLib->Release();
	}

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

	//call automation related init method
	pCMyMath->InitInstance();

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

//Implementation of IDispatch methods
HRESULT CMyMath::GetTypeInfoCount(UINT* pCountTypeInfo)
{
	*pCountTypeInfo = 1;

	return (S_OK);
}

HRESULT CMyMath::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo** ppITypeInfo)
{
	*ppITypeInfo = NULL;
	//i - index
	if (iTypeInfo != 0)
	{
		return (DISP_E_BADINDEX);
	}

	m_pITypeInfo->AddRef();
	*ppITypeInfo = m_pITypeInfo;

	return (S_OK);
}

HRESULT CMyMath::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId)
{
	return (DispGetIDsOfNames(m_pITypeInfo, rgszNames, cNames, rgDispId));
}

HRESULT CMyMath::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo, UINT* puArgErr)
{
	//var declaration
	HRESULT hr;

	hr = DispInvoke(
		this,
		m_pITypeInfo,
		dispIdMember,
		wFlags,
		pDispParams,
		pVarResult,
		pExcepInfo,
		puArgErr
	);

	return (hr);
}



extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	CMyMathClassFactory *pCMyMathClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_MyMath)
		return (CLASS_E_CLASSNOTAVAILABLE);

	pCMyMathClassFactory = new CMyMathClassFactory;
	if (pCMyMathClassFactory == NULL)
		return (E_OUTOFMEMORY);

	hr = pCMyMathClassFactory->QueryInterface(riid, ppv);
	pCMyMathClassFactory->Release();

	return (hr);
}

extern "C" HRESULT __stdcall DLLCanUnloadNow(void) {
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return (S_OK);
	else
		return (S_FALSE);
}
	
void ComErrorDescriptionString(HWND hwnd, HRESULT hr)
{
	// variable declarations
	TCHAR* szErrorMessage = NULL;
	TCHAR str[255];
	if (FACILITY_WINDOWS == HRESULT_FACILITY(hr))
		hr = HRESULT_CODE(hr);
	//FormatMessage() win32 function - used for debugging
	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&szErrorMessage, 0, //MAKELANGID() - usemto give locale (en-US)
		NULL) != 0
	)
	{
		swprintf_s(str, TEXT("%#x : %s"), hr, szErrorMessage);
		LocalFree(szErrorMessage);
	}
	else
		swprintf_s(str, TEXT("[Could not find a description for error # %#x.]\n"),
			hr);
	MessageBox(hwnd, str, TEXT("COM Error"), MB_OK);
}
