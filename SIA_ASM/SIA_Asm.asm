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
Hello wordl!	L0	L1	L2	L3	L4	L5	L6	L7	L8	L9	L10	L11