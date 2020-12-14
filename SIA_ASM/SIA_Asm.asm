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
	L2 BYTE 'Seni0r QA - Art_K!', 0
	L3 SDWORD 2
	L4 SDWORD 1
	L5 BYTE 'Hello wolrd!', 0
	L6 BYTE '’ÛÈ', 0
	L7 BYTE 'Qwe', 0
	L8 BYTE 0
	L9 SDWORD 2
	L10 SDWORD 5
	L11 SDWORD 0
.DATA
	tempfactorial SDWORD 0
	qsunlight SDWORD 0
	strokaENTRY DWORD ?
	lenENTRY SDWORD 0
	resultENTRY SDWORD 0
.CODE
factorial PROC xfactorial:SDWORD
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
	call factorial
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
factorial ENDP

sunlight PROC bsunlight:DWORD, asunlight:DWORD
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
sunlight ENDP

artem PROC aartem:SDWORD
	push offset L2
	jmp local2
local2:
	pop eax
	ret
artem ENDP

retstr PROC aretstr:SDWORD
	push L3
	call artem
	push eax
	jmp local3
local3:
	pop eax
	ret
retstr ENDP

main PROC
	push L4
	call retstr
	push eax
	pop strokaENTRY

	push strokaENTRY

call outStreamW
	push offset L5
	pop strokaENTRY

	push strokaENTRY
	call stringLen
	push eax
	pop eax
	mov lenENTRY, eax
	push offset L6
	call stringLen
	push eax
	push offset L7
	push offset L8
	call lexStrCmp
	push eax
	push L9
	call factorial
	push eax
	pop eax
	pop ebx
	mul ebx
	push eax
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop eax
	mov lenENTRY, eax
	push strokaENTRY
	push offset L5
	call sunlight
	push eax
	pop eax
	mov resultENTRY, eax
	push resultENTRY

	call outStreamN
	push L10
	call factorial
	push eax
	push L9
	pop eax
	pop ebx
	mul ebx
	push eax

	call outStreamN
	push lenENTRY

	call outStreamN
	push L11
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