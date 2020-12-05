.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib ..\Debug\LIB.lib
	ExitProcess PROTO :DWORD

outStreamW PROTO: DWORD
outStreamN PROTO: DWORD
stringLen PROTO: DWORD
lexStrCmp PROTO: DWORD, :DWORD
.stack 4096
.CONST
	null_division BYTE 'ERROR: DIVISION BY ZERO', 0
	OVER_FLOW BYTE 'ERROR: OVERFLOW', 0
	L0 BYTE 'Hello world!', 0
	L1 DWORD 1
.DATA
	hayMAIN DWORD 0
.CODE
main PROC

push offset L0
call outStreamW
	push 1
		jmp theend
theend:

	push 0
	call ExitProcess
SOMETHINGWRONG::
	push offset null_division
	call outStreamW
jmp konec
overflow::
	push offset OVER_FLOW
	call outStreamW
konec:
	push -1
	call ExitProcess
main ENDP
end main