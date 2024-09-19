#pragma once

class ISum : public IUnknown
{
public:
	// ISum specific method declarations
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0; //pure virtual
};

class ISubtract : public IUnknown
{
public:
	// ISum specific method declarations
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

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


// CLSID of SumSubtract comp {3CE9FF2B-60AD-4C68-B56C-B81C39CDE250}
const CLSID CLSID_SumSubtract = { 0x3ce9ff2b, 0x60ad, 0x4c68, 0xb5, 0x6c, 0xb8, 0x1c, 0x39, 0xcd, 0xe2, 0x50 };

//IID of ISum Interface {23804BC3-3C8B-4500-A1A3-E2A84C136CC4}
const IID IID_ISum = { 0x23804bc3, 0x3c8b, 0x4500, 0xa1, 0xa3, 0xe2, 0xa8, 0x4c, 0x13, 0x6c, 0xc4 };

//IID of ISubtract Interface {5F169385-231D-455F-AF79-C9CAC54889FF}
const IID IID_ISubtract = { 0x5f169385, 0x231d, 0x455f, 0xaf, 0x79, 0xc9, 0xca, 0xc5, 0x48, 0x89, 0xff };

//IID of IMultiplication Interface {BC806B40-C1CB-48EA-BEC4-8CEED35390CD}
const IID IID_IMultiplication = { 0xbc806b40, 0xc1cb, 0x48ea, 0xbe, 0xc4, 0x8c, 0xee, 0xd3, 0x53, 0x90, 0xcd };

//IID of IDivision Interface {122472A4-922E-4E61-B004-5992B5413697}
const IID IID_IDivision = { 0x122472a4, 0x922e, 0x4e61, 0xb0, 0x4, 0x59, 0x92, 0xb5, 0x41, 0x36, 0x97 };











