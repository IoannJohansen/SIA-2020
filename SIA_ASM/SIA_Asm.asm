.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib ..\Debug\Lib.lib
	ExitProcess PROTO :DWORD

	readw PROTO: DWORD
	readr PROTO: DWORD
	strln PROTO: DWORD
	Strcmp PROTO: DWORD, :DWORD
.stack 4096
.const
Hello wordl!	-	-	-	-	-	-	-	-	-	-