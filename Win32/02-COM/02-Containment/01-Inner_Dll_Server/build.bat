cls

del *.obj

del *.dll

del *.exp

del *.lib


cl.exe /c /EHsc ContainmentInnerComponentWithRegFile.cpp 

link.exe ContainmentInnerComponentWithRegFile.obj /DLL /DEF:ContainmentInnerComponentWithRegFile.def user32.lib /SUBSYSTEM:WINDOWS
