cls

del *.obj

del *.dll

del *.exp

del *.lib


cl.exe /c /EHsc MyMathTwo.cpp 

link.exe MyMathTwo.obj /DLL /DEF:MyMathTwo.def user32.lib /SUBSYSTEM:WINDOWS
