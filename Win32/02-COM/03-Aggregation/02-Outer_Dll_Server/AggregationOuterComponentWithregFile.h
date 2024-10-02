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

// CLSID of SumSubtract comp {0BE42167-C269-4D8C-8DB6-36DF4510855B}
const CLSID CLSID_SumSubtract = { 0xbe42167, 0xc269, 0x4d8c, 0x8d, 0xb6, 0x36, 0xdf, 0x45, 0x10, 0x85, 0x5b };

//IID of ISum Interface {951BBD8E-C01F-4199-886D-5CA0FBA8633E}
const IID IID_ISum = { 0x951bbd8e, 0xc01f, 0x4199, 0x88, 0x6d, 0x5c, 0xa0, 0xfb, 0xa8, 0x63, 0x3e };

//IID of ISubtract Interface {CEC53178-4DCC-443D-AD19-0AA662D9AEC7}
const IID IID_ISubtract = { 0xcec53178, 0x4dcc, 0x443d, 0xad, 0x19, 0xa, 0xa6, 0x62, 0xd9, 0xae, 0xc7 };










