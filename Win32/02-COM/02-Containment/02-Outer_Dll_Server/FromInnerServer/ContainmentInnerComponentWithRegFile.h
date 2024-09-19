#pragma once
//stringised GUID 

//Numeric form of GUID

class IMultiplication : public IUnknown
{
public:
	// ISum specific method declarations
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0; //pure virtual
};

class IDivision : public IUnknown
{
public:
	// ISum specific method declarations
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};

// CLSID of Muldiv comp {7FE5CED4-5D15-476C-9932-BFDB2DAE6E6B}
const CLSID CLSID_MulDiv = { 0x7fe5ced4, 0x5d15, 0x476c, 0x99, 0x32, 0xbf, 0xdb, 0x2d, 0xae, 0x6e, 0x6b };

//IID of IMultiplication Interface {BC806B40-C1CB-48EA-BEC4-8CEED35390CD}
const IID IID_IMultiplication = { 0xbc806b40, 0xc1cb, 0x48ea, 0xbe, 0xc4, 0x8c, 0xee, 0xd3, 0x53, 0x90, 0xcd };

//IID of IDivision Interface {122472A4-922E-4E61-B004-5992B5413697}
const IID IID_IDivision = { 0x122472a4, 0x922e, 0x4e61, 0xb0, 0x4, 0x59, 0x92, 0xb5, 0x41, 0x36, 0x97 };








