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
	L0 BYTE 'Hello gays', 0
	L1 BYTE 'Hay', 0
	L2 BYTE 'Hoy', 0
	L3 BYTE 'Lalalali', 0
	L4 SDWORD 1
	L5 SDWORD 0
.DATA
.CODE
	hey PROC sthey:DWORD
	push offset L0
		jmp local0
local0:
	pop eax
	ret
hey ENDP

	get PROC aget:SDWORD
	push offset L1
		call stringLen
	push eax
	push offset L2
		call stringLen
	push eax
	pop eax
	pop ebx
	add eax, ebx
	push eax
	push offset L3
		call stringLen
	push eax
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop eax
	mov aget, eax
	push aget
		jmp local1
local1:
	pop eax
	ret
get ENDP

main PROC
	push L4
		call get
	push eax

call outStreamN
	push L5
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