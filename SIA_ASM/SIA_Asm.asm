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
	L0 SDWORD 11
	L1 SDWORD 0
	L2 SDWORD 1
	L3 BYTE 'Верни обратно!', 0
	L4 SDWORD 5
	L5 SDWORD 10
	L6 SDWORD 4
	L7 SDWORD 2
	L8 SDWORD 1
	L9 SDWORD 3
	L10 SDWORD 6
	L11 BYTE 'Оно работает', 0
	L12 SDWORD 20
	L13 SDWORD 8
	L14 BYTE 'Слово', 0
	L15 BYTE 'Yes1!', 0
	L16 BYTE 'Yes2!', 0
	L17 BYTE 'No2!', 0
	L18 BYTE 'No1!', 0
	L19 SDWORD 0
.DATA
	resretnum SDWORD 0
	lenfindlen SDWORD 0
	summasum SDWORD 0
	rescomp SDWORD 0
	slovoENTRY DWORD ?
	expENTRY SDWORD 0
	fourENTRY SDWORD 0
	parmsudaENTRY DWORD ?
	parmsudadENTRY SDWORD 0
	lenENTRY SDWORD 0
	getsumENTRY SDWORD 0
.CODE
	retnum PROC oneretnum:SDWORD
	push oneretnum
	push L0
	pop eax
	pop ebx
	mul ebx
	push eax
	pop eax
	cmp eax, 2147483647
	jg overflow
	cmp eax, -2147483648
	jl overflow
	mov resretnum, eax
	push resretnum
		jmp local0
local0:
	pop eax
	ret
retnum ENDP

	getparm PROC pgetparm:DWORD
	push pgetparm
		jmp local1
local1:
	pop eax
	ret
getparm ENDP

	getnump PROC pgetnump:SDWORD
	push pgetnump
		jmp local2
local2:
	pop eax
	ret
getnump ENDP

	findlen PROC pfindlen:DWORD
		call stringLen
	push eax
	push pfindlen
		call stringLen
	push eax
	pop eax
	cmp eax, 2147483647
	jg overflow
	cmp eax, -2147483648
	jl overflow
	mov lenfindlen, eax
	push lenfindlen
		jmp local3
local3:
	pop eax
	ret
findlen ENDP

	sum PROC bsum:SDWORD, asum:SDWORD
	push asum
	push bsum
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop eax
	cmp eax, 2147483647
	jg overflow
	cmp eax, -2147483648
	jl overflow
	mov summasum, eax
	push summasum
		jmp local4
local4:
	pop eax
	ret
sum ENDP

	comp PROC bcomp:DWORD, acomp:DWORD
		call lexStrCmp
	push eax
	push acomp
	push bcomp
		call lexStrCmp
	push eax
	pop eax
	cmp eax, 2147483647
	jg overflow
	cmp eax, -2147483648
	jl overflow
	mov rescomp, eax
	mov eax, rescomp
	cmp eax, L1
		jl ifi1
		jg else1
