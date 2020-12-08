.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib ..\Debug\LIB.lib
	ExitProcess PROTO :DWORD

outStreamW PROTO: SDWORD
outStreamN PROTO: DWORD
stringLen PROTO: DWORD
lexStrCmp PROTO: DWORD, :DWORD
.stack 4096
.CONST
	null_division BYTE 'ERROR: DIVISION BY ZERO', 0
	OVER_FLOW BYTE 'ERROR: OVERFLOW', 0
	L0 SDWORD 5
	L1 SDWORD 5
	L2 SDWORD 0
.DATA
.CODE
	test PROC atest:SDWORD
	push L0
		jmp local0
local0:
	pop eax
	ret
test ENDP

main PROC
	push L1

call outStreamN
	push L2
		jmp theend
theend:

	call ExitProcess
SOMETHINGWRONG::
	push offset null_division
	call outStreamW
jmp konec
konec:
	push -1
	call ExitProcess
main ENDP
end main