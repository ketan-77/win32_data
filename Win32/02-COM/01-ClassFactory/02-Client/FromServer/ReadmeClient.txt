providing you with three files
ClassFactoryDllServerWithRegFile.h
ClassFactoryWithRegFile.dll
ClassFactoryDllServerWithRegFile.reg

//about header file
Header file contains two interfaces ISum and ISubtract
ISum provide sum of two integers (functionality)
ISubtraction provide subtraction of two integers (functionality)

Both interfaces inherit from IUnkonwn 
Both interfaces and required GUID's are given in header file
You can call above mentioned function on respective interface pointers

//before building your client application do the following steps:
1. Copy the dll to C:\Windows\System32\
2. Double click on the .reg file to register the dll
3. Run and build your client application
