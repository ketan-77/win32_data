cls

del *.obj

del *.dll

del *.exp

del *.lib


cl.exe /c /EHsc ContainmentOuterComponentWithregFile.cpp 

link.exe ContainmentOuterComponentWithregFile.obj /DLL /DEF:ContainmentOuterComponentWithregFile.def user32.lib ole32.lib /SUBSYSTEM:WINDOWS
