cls

del *.obj

del *.dll

del *.exp

del *.lib


cl.exe /c /EHsc ClassFactoryDllServerWithRegFile.cpp 

link.exe ClassFactoryDllServerWithRegFile.obj /DLL /DEF:ClassFactoryDllServerWithRegFile.def user32.lib /SUBSYSTEM:WINDOWS
