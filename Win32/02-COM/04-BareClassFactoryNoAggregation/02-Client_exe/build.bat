cls

del *.exe

del *.res

del *.obj

cl.exe /c /EHsc window.cpp 

rc.exe Window.rc 

link.exe window.obj Window.res user32.lib gdi32.lib ole32.lib /SUBSYSTEM:WINDOWS
