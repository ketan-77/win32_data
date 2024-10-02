cls

del *.obj

del *.dll

del *.exp

del *.lib


cl.exe /c /EHsc AggregationOuterComponentWithregFile.cpp 

link.exe AggregationOuterComponentWithregFile.obj /DLL /DEF:AggregationOuterComponentWithregFile.def user32.lib ole32.lib /SUBSYSTEM:WINDOWS

