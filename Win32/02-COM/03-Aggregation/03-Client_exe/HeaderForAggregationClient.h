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


// CLSID of SumSubtract comp {0BE42167-C269-4D8C-8DB6-36DF4510855B}
const CLSID CLSID_SumSubtract = { 0xbe42167, 0xc269, 0x4d8c, 0x8d, 0xb6, 0x36, 0xdf, 0x45, 0x10, 0x85, 0x5b };

//IID of ISum Interface {951BBD8E-C01F-4199-886D-5CA0FBA8633E}
const IID IID_ISum = { 0x951bbd8e, 0xc01f, 0x4199, 0x88, 0x6d, 0x5c, 0xa0, 0xfb, 0xa8, 0x63, 0x3e };

//IID of ISubtract Interface {CEC53178-4DCC-443D-AD19-0AA662D9AEC7}
const IID IID_ISubtract = { 0xcec53178, 0x4dcc, 0x443d, 0xad, 0x19, 0xa, 0xa6, 0x62, 0xd9, 0xae, 0xc7 };

//IID of IMultiplication Interface {170CFF84-08DF-4344-BA09-7A3D43605640}
const IID IID_IMultiplication = { 0x170cff84, 0x8df, 0x4344, 0xba, 0x9, 0x7a, 0x3d, 0x43, 0x60, 0x56, 0x40 };

//IID of IDivision Interface {EC9A63BD-47B2-4885-9C36-D8B0A237BBDD}
const IID IID_IDivision = { 0xec9a63bd, 0x47b2, 0x4885, 0x9c, 0x36, 0xd8, 0xb0, 0xa2, 0x37, 0xbb, 0xdd };











