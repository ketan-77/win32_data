providing you with three files
ContainmentInnerComponentWithRegFile.h
ContainmentInnerComponentWithRegFile.dll
ContainmentInnerComponentWithRegFile.reg

//about header file
Header file contains two interfaces IMultiplication and IDivision
IMultiplication provide multiplication of two integers (functionality)
IDivision provide division of two integers (functionality)

Both interfaces inherit from IUnkonwn 
Both interfaces and required GUID's are given in header file
You can call above mentioned function on respective interface pointers

//before building your client application do the following steps:
1. Copy the dll to C:\Windows\System32\
2. Double click on the .reg file to register the dll
3. Run and build your client application
