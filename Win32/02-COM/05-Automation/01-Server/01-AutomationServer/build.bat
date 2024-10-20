cls

del *.obj

del *.dll

del *.exp

del *.lib


cl.exe /c /EHsc AutomationServer.cpp 

link.exe AutomationServer.obj /DLL /DEF:AutomationServer.def user32.lib /SUBSYSTEM:WINDOWS
