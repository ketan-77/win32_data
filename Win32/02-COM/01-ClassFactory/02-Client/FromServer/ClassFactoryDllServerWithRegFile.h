#pragma once
//stringised GUID 

//Numeric form of GUID

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

// CLSID of SumSubtract comp {23D61BAE-D3AE-47F2-89FB-B1E5E67C1BC1}
const CLSID CLSID_SumSubtract = { 0x23d61bae, 0xd3ae, 0x47f2, 0x89, 0xfb, 0xb1, 0xe5, 0xe6, 0x7c, 0x1b, 0xc1 };

//IID of ISum Interface {D11379AB-08B1-4C35-945F-B8AA3A63F62D}
const IID IID_ISum = { 0xd11379ab, 0x8b1, 0x4c35, 0x94, 0x5f, 0xb8, 0xaa, 0x3a, 0x63, 0xf6, 0x2d };


//IID of ISubtract Interface {A9D3B612-5115-4DF3-8237-A5E72B2C3E68}
const IID IID_ISubtract = { 0xa9d3b612, 0x5115, 0x4df3, 0x82, 0x37, 0xa5, 0xe7, 0x2b, 0x2c, 0x3e, 0x68 };







