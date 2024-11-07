
--> Step 1 : Copy .dll and .tlb files at "C:\Windows\System32\"
	-AutomationServer.dll
	-AutomationProxyStub.dll
	-AutomationServerTypeLibrary.tlb

--> Step 2 : Open normal cmd promt in administrator mode and give the following
			command to register server
			# regsvr32.exe AutomationProxyStub.dll

--> Step 3 : Double click on AutomationServer.reg
	
-AutomationServer.h
-AutomationServer.reg


