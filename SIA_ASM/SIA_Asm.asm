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
	L0 SDWORD 0
	L1 SDWORD 1
	L2 SDWORD 1
	L3 SDWORD 2
	L4 SDWORD 0
	L5 BYTE 'Числа одинаковы', 0
	L6 BYTE 'Числа различны', 0
	L7 SDWORD 15
	L8 SDWORD 35
	L9 BYTE 'Hay', 0
.DATA
	rescmpENTRY SDWORD 0
	ressumENTRY SDWORD 0
.CODE
	sum PROC bsum:SDWORD, asum:SDWORD
	push asum
	push bsum
	pop eax
	pop ebx
	add eax, ebx
	push eax
		jmp local0
local0:
	pop eax
	ret
sum ENDP

	isequals PROC bisequals:SDWORD, aisequals:SDWORD
	mov eax, aisequals
	cmp eax, bisequals
		jz ifi1
		jnz else1
ifi1:
	push L0
		jmp local1
	jmp ifEnd1
else1:
	push L1
		jmp local1
ifEnd1:
local1:
	pop eax
	ret
isequals ENDP

	getlen PROC stringgetlen:DWORD
	push stringgetlen
		call stringLen
	push eax
		jmp local2
local2:
	pop eax
	ret
getlen ENDP

main PROC
	push L2
	push L3
		call isequals
	push eax
	pop eax
	mov rescmpENTRY, eax
	mov eax, rescmpENTRY
	cmp eax, L4
		jz ifi2
		jnz else2
ifi2:
	push offset L5

call outStreamW
	jmp ifEnd2
else2:
	push offset L6

call outStreamW
ifEnd2:
	push L7
	push L8
		call sum
	push eax
	pop eax
	mov ressumENTRY, eax
	push ressumENTRY

call outStreamN
	push offset L9
		call getlen
	push eax

call outStreamN
	push L4
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