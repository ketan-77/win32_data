#pragma once

//{00020420 - 0000 - 0000 - C000 - 000000000046} - GUID of IDispatch
class IMyMath : public IDispatch {
public:
	//pure virtual
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0; //pure virtual
	
	//pure virtual
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

// CLSID of MyMath component {16D4B18C-885C-4664-B673-714A59988C88}
const CLSID CLSID_MyMath = { 0x16d4b18c, 0x885c, 0x4664, 0xb6, 0x73, 0x71, 0x4a, 0x59, 0x98, 0x8c, 0x88 };

//IID of IMyMath Interface {A48C5C17-A81A-4353-AB58-EA34B94734E9}
const IID IID_IMyMath = { 0xa48c5c17, 0xa81a, 0x4353, 0xab, 0x58, 0xea, 0x34, 0xb9, 0x47, 0x34, 0xe9 };






