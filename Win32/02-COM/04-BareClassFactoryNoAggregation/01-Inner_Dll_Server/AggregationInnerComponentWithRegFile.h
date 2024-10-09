#pragma once

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


// CLSID of Muldiv comp {031B2519-D6C5-4243-A1AF-EEA6F608A55F}
const CLSID CLSID_MulDiv = { 0x31b2519, 0xd6c5, 0x4243, 0xa1, 0xaf, 0xee, 0xa6, 0xf6, 0x8, 0xa5, 0x5f };

//IID of IMultiplication Interface {170CFF84-08DF-4344-BA09-7A3D43605640}
const IID IID_IMultiplication = { 0x170cff84, 0x8df, 0x4344, 0xba, 0x9, 0x7a, 0x3d, 0x43, 0x60, 0x56, 0x40 };

//IID of IDivision Interface {EC9A63BD-47B2-4885-9C36-D8B0A237BBDD}
const IID IID_IDivision = { 0xec9a63bd, 0x47b2, 0x4885, 0x9c, 0x36, 0xd8, 0xb0, 0xa2, 0x37, 0xbb, 0xdd };







