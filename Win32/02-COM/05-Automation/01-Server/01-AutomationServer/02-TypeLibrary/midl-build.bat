cls 

del *.c

del *.h

del *.tlb


midl.exe /h AutomationProxyStub.h /iid AutomationProxyStubGuids.c /dlldata AutomationProxyStubDllData.c /proxy AutomationProxyStub.c AutomationServerTypeLibrary.idl