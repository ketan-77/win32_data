//{00020420 - 0000 - 0000 - C000 - 000000000046} - GUID of IDispatch
//class IMyMath : public IDispatch {
//public:
//	//pure virtual
//	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0; //pure virtual
//	
//	//pure virtual
//	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
//};
#pragma once

#undef INTERFACE //it is saftey if their any interface active it will deactivate those

#define INTERFACE IMyMath

DECLARE_INTERFACE_(IMyMath, IDispatch) //similar to class IMyMath : public IDispatch
{
	//IUnknown method declaration in C style
	STDMETHOD(QueryInterface)(THIS_ REFIID, void**) PURE; //PURE it indicate pure virtual
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;
	//If we have 0 - parametrs only use THIS and more than one use THIS_
	//STDMETHOD - It is combination of HRESULT + __stdcall
	//STDMETHOD_ - only __stdcall and define return type with function name itself (return type, function name)

	//IDispatch method declaration in C style
	/*
	HRESULT __stdcall GetTypeInfoCount(UINT*);
	HRESULT __stdcall GetTypeInfo(UINT, LCID, ITypeInfo**); //LCID - Local ID
	HRESULT __stdcall GetIDsOfNames(REFIID, LPOLESTR*, UINT, LCID, DISPID*); //DISPID - Dispatch ID, LPOLESTR is COM specific string (long ptr OLE string)
	HRESULT __stdcall Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*);
	*/

	STDMETHOD(GetTypeInfoCount)(THIS_ UINT*) PURE;
	STDMETHOD(GetTypeInfo)(THIS_ UINT, LCID, ITypeInfo**) PURE;
	STDMETHOD(GetIDsOfNames)(THIS_ REFIID, LPOLESTR*, UINT, LCID, DISPID*) PURE;
	STDMETHOD(Invoke)(THIS_ DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT, EXCEPINFO*, UINT*) PURE;

	//IMyMath method declaration in C style

	STDMETHOD(SumOfTwoIntegers)(THIS_ int, int, int*) PURE;
	STDMETHOD(SubtractionOfTwoIntegers)(THIS_ int, int, int*) PURE;
};

// CLSID of MyMath component {16D4B18C-885C-4664-B673-714A59988C88}
const CLSID CLSID_MyMath = { 0x16d4b18c, 0x885c, 0x4664, 0xb6, 0x73, 0x71, 0x4a, 0x59, 0x98, 0x8c, 0x88 };

//IID of IMyMath Interface {A48C5C17-A81A-4353-AB58-EA34B94734E9}

const IID IID_IMyMath = { 0xa48c5c17, 0xa81a, 0x4353, 0xab, 0x58, 0xea, 0x34, 0xb9, 0x47, 0x34, 0xe9 };




































