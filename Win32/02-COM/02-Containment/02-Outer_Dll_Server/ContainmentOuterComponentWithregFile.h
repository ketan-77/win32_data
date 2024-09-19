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

// CLSID of SumSubtract comp {3CE9FF2B-60AD-4C68-B56C-B81C39CDE250}
const CLSID CLSID_SumSubtract = { 0x3ce9ff2b, 0x60ad, 0x4c68, 0xb5, 0x6c, 0xb8, 0x1c, 0x39, 0xcd, 0xe2, 0x50 };

//IID of ISum Interface {23804BC3-3C8B-4500-A1A3-E2A84C136CC4}
const IID IID_ISum = { 0x23804bc3, 0x3c8b, 0x4500, 0xa1, 0xa3, 0xe2, 0xa8, 0x4c, 0x13, 0x6c, 0xc4 };

//IID of ISubtract Interface {5F169385-231D-455F-AF79-C9CAC54889FF}
const IID IID_ISubtract = { 0x5f169385, 0x231d, 0x455f, 0xaf, 0x79, 0xc9, 0xca, 0xc5, 0x48, 0x89, 0xff };









