//changes in aggregation inner are with respect to containment inner
#define UNICODE
#include <windows.h>
#include "AggregationInnerComponentWithRegFile.h"

//cahnge 1: Interface declaration (for internal use only i.e. not to ne included in .h file)
interface INoAggregationIUnknown
{
	virtual HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void**) = 0;
	virtual ULONG __stdcall AddRef_NoAggregation(void) = 0;
	virtual ULONG __stdcall Release_NoAggregation(void) = 0;
};

//change 2 : inherit INoAggregationIUnknown
class CMulDivision : public INoAggregationIUnknown, IMultiplication, IDivision
{
private:
	long m_cRef;
	IUnknown* m_pIUnknownOuter; //change 3 
public:
	CMulDivision(IUnknown *); // change 4a - parameterized constructor
	~CMulDivision(void);

	//change 4b Aggregation Nonsupported IUnknown specific method declaration (inherited)
	HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void**);
	ULONG __stdcall AddRef_NoAggregation(void);
	ULONG __stdcall Release_NoAggregation(void);

	//IUknown Aggregation supported specific method declarations (inherited)
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
CMulDivision::CMulDivision(IUnknown *pIUnknownOuter)
{
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);  //increment global counter

	if(pIUnknownOuter)
	{
		m_pIUnknownOuter = pIUnknownOuter;
	}
	else
	{
		//you will come to this block when inner server directly called by client
		m_pIUnknownOuter = reinterpret_cast<IUnknown*>(static_cast<INoAggregationIUnknown*>(this));
	}
}

CMulDivision::~CMulDivision(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents); //decrement global count
}
//Aggreagation nonsupporting methods change 6/7/8
HRESULT CMulDivision::QueryInterface_NoAggregation(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<INoAggregationIUnknown*>(this);
	else if (riid == IID_IMultiplication)
		*ppv = static_cast<IMultiplication*>(this); // in this case we inheriting og IUnknown (function ptr)
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
ULONG CMulDivision::AddRef_NoAggregation(void) {
	InterlockedIncrement(&m_cRef);  //increment global counter
	return (m_cRef);
}

ULONG CMulDivision::Release_NoAggregation(void) {
	InterlockedDecrement(&m_cRef);

	if (m_cRef == 0) {
		delete(this);
		return (0);
	}

	return (m_cRef);
}
//Aggregation supporting methods change 9/10/11
HRESULT CMulDivision::QueryInterface(REFIID riid, void **ppv)
{
	return m_pIUnknownOuter->QueryInterface(riid, ppv);
}

ULONG CMulDivision::AddRef(void)
{
	return m_pIUnknownOuter->AddRef();
}

ULONG CMulDivision::Release(void)
{
	return m_pIUnknownOuter->Release();
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
	if ((pUnkOuter != NULL) && (riid != IID_IUnknown)) //change 12a - if condition 
	{
		return (CLASS_E_NOAGGREGATION);
	}
	//create the instance of component i.e. of CMulDivision
	pCMulDivision = new CMulDivision(pUnkOuter); //change 12b - param constructor
	if (pCMulDivision == NULL) 
	{
		return (E_OUTOFMEMORY);
	}

	//change 12c
	hr = pCMulDivision->QueryInterface_NoAggregation(riid, ppv);
	pCMulDivision->Release_NoAggregation();
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
	