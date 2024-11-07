cls 

del *.exp

del *.lib

del *.dll

del *.obj

cl.exe /c /EHsc /D REGISTER_PROXY_DLL AutomationProxyStub.c AutomationProxyStubGuids.c AutomationProxyStubDllData.c

link.exe AutomationProxyStub.obj AutomationProxyStubGuids.obj AutomationProxyStubDllData.obj /DLL /DEF:AutomationProxyStub.def user32.lib ole32.lib oleaut32.lib advapi32.lib rpcns4.lib rpcrt4.lib /SUBSYSTEM:WINDOWS