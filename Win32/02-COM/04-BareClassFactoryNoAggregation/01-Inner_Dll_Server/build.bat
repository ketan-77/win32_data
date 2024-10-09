cls

del *.obj

del *.dll

del *.exp

del *.lib


cl.exe /c /EHsc AggregationInnerComponentWithRegFile.cpp 

link.exe AggregationInnerComponentWithRegFile.obj /DLL /DEF:AggregationInnerComponentWithRegFile.def user32.lib /SUBSYSTEM:WINDOWS
