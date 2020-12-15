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
	L2 BYTE 'Hello wolrd!', 0
	L3 SDWORD 5
	L4 SDWORD 2
	L5 SDWORD 0
.DATA
	tempfactorial SDWORD 0
	qsunlight SDWORD 0
	strokaENTRY DWORD ?
	lenENTRY SDWORD 0
	resultENTRY SDWORD 0
.CODE
factorialGLOBAL PROC xfactorial:SDWORD
	mov eax, xfactorial
	cmp eax, L0
		jl ifi1
		jge else1
ifi1:
	push L0
	jmp local0
else1:
	mov eax, xfactorial
	cmp eax, L0
		jz ifi2
		jnz else2
ifi2:
	push L1
	jmp local0
	jmp ifEnd2
else2:
	push xfactorial
	push L1
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop eax
	mov tempfactorial, eax
	push tempfactorial
	call factorialGLOBAL
	push eax
	push xfactorial
	pop eax
	pop ebx
	mul ebx
	push eax
	jmp local0
ifEnd2:
local0:
	pop eax
	ret
factorialGLOBAL ENDP

sunlightGLOBAL PROC bsunlight:DWORD, asunlight:DWORD
	push asunlight
	push bsunlight
	call lexStrCmp
	push eax
	pop eax
	mov qsunlight, eax
	push qsunlight
	jmp local1
local1:
	pop eax
	ret
sunlightGLOBAL ENDP

main PROC
	push offset L2
	pop strokaENTRY

	push strokaENTRY
	call stringLen
	push eax
	pop eax
	mov lenENTRY, eax
	push strokaENTRY
	push offset L2
	call sunlightGLOBAL
	push eax
	pop eax
	mov resultENTRY, eax
	push resultENTRY

	call outStreamN
	push L3
	call factorialGLOBAL
	push eax
	push L4
	pop eax
	pop ebx
	mul ebx
	push eax

	call outStreamN
	push lenENTRY

	call outStreamN
	push L5
	jmp theend
theend:
	call ExitProcess
SOMETHINGWRONG:
	push offset null_division
	call outStreamW
	jmp konec
konec:
	push -1
	call ExitProcess
main ENDP
end main