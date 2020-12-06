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
	L1 BYTE 'Верни обратно!', 0
	L2 SDWORD 5
	L3 SDWORD 10
	L4 SDWORD 1
	L5 SDWORD 3
	L6 SDWORD 6
	L7 BYTE 'Оно работает', 0
	L8 SDWORD 20
	L9 SDWORD 8
	L10 SDWORD 2
	L11 BYTE 'Слово', 0
	L12 SDWORD 4
	L13 BYTE 'Yes1!', 0
	L14 BYTE 'Yes2!', 0
	L15 BYTE 'No2!', 0
	L16 BYTE 'No1!', 0
.DATA
	resretnum SDWORD 0
	lenfindlen SDWORD 0
	summasum SDWORD 0
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

main PROC
	push offset L1
		call getparm
	push eax
	pop parmsudaENTRY

	push L2
		call getnump
	push eax
	push L3
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop eax
	cmp eax, 2147483647
	jg overflow
	cmp eax, -2147483648
	jl overflow
	mov parmsudadENTRY, eax
	push L4
		call retnum
	push eax
	push L5
	pop eax
	pop ebx
	mul ebx
	push eax
	push L2
	push L6
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop eax
	pop ebx
	mul ebx
	push eax
	pop eax
	cmp eax, 2147483647
	jg overflow
	cmp eax, -2147483648
	jl overflow
	mov fourENTRY, eax
	push offset L7
	pop slovoENTRY

		call stringLen
	push eax
	push slovoENTRY
		call stringLen
	push eax
	pop eax
	cmp eax, 2147483647
	jg overflow
	cmp eax, -2147483648
	jl overflow
	mov lenENTRY, eax
	push L3
	push L8
		call sum
	push eax
	pop eax
	cmp eax, 2147483647
	jg overflow
	cmp eax, -2147483648
	jl overflow
	mov getsumENTRY, eax
	push L2
	pop eax
	cmp eax, 2147483647
	jg overflow
	cmp eax, -2147483648
	jl overflow
	mov expENTRY, eax
	push L2
	push L3
	pop eax
	pop ebx
	mul ebx
	push eax
	push L9
	push L5
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop ebx
	pop eax
	cmp ebx,0
	je SOMETHINGWRONG
	cdq
	idiv ebx
	push eax
	pop eax
	cmp eax, 2147483647
	jg overflow
	cmp eax, -2147483648
	jl overflow
	mov expENTRY, eax
	push expENTRY
	push L10
	pop eax
	pop ebx
	mul ebx
	push eax
	pop eax
	cmp eax, 2147483647
	jg overflow
	cmp eax, -2147483648
	jl overflow
	mov expENTRY, eax

push getsumENTRY
call outStreamN

push lenENTRY
call outStreamN

push parmsudadENTRY
call outStreamN

push parmsudaENTRY
call outStreamW

push fourENTRY
call outStreamN

push expENTRY
call outStreamN

push offset L11
call outStreamW

push slovoENTRY
call outStreamW
	mov eax, L2
	cmp eax, L12
		jg ifi1
		jl else1
ifi1:

push offset L13
call outStreamW
	mov eax, L5
	cmp eax, L10
		jl ifi2
		jg else2
ifi2:

push offset L14
call outStreamW
	jmp ifEnd2
else2:

push offset L15
call outStreamW
ifEnd2:
	jmp ifEnd1
else1:

push offset L16
call outStreamW
ifEnd1:
	push 5
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