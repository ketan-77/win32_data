cls 

del *.obj

del *.dll

del *.exp

del *.lib

cl.exe /c /EHsc MyMathOne.c

link.exe MyMathOne.obj /DLL user32.lib /SUBSYSTEM:WINDOWS