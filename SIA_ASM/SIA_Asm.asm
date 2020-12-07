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
	L2 BYTE 'Words are different', 0
	L3 SDWORD 1
	L4 BYTE 'Words are equals', 0
	L5 SDWORD 0
	L6 SDWORD 10
	L7 BYTE 'Верни обратно!', 0
	L8 SDWORD 5
	L9 SDWORD 4
	L10 SDWORD 2
	L11 SDWORD 1
	L12 SDWORD 3
	L13 SDWORD 6
	L14 BYTE 'Оно работает', 0
	L15 SDWORD 123
	L16 SDWORD 8
	L17 BYTE 'Слово', 0
	L18 BYTE 'Yes2!', 0
	L19 BYTE 'No2!', 0
	L20 BYTE 'No1!', 0
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
	negnENTRY SDWORD 0
.CODE
	retnum PROC oneretnum:SDWORD
	push oneretnum
	push L0
	pop eax
	pop ebx
	mul ebx
	push eax
	pop eax
	jo overflow
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
	jo overflow
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
	jo overflow
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
	jo overflow
	mov rescomp, eax
	mov eax, rescomp
	cmp eax, L1
		jl ifi1
		jg else1
ifi1:

push offset L2
call outStreamW
	mov eax, rescomp
	cmp eax, L1
		jg ifi2
		jl else2
ifi2:

push offset L2
call outStreamW
	push 1
		jmp local5
	jmp ifEnd2
else2:

push offset L4
call outStreamW
	push 0
		jmp local5
ifEnd2:
	push 1
		jmp local5
	jmp ifEnd1
else1:
	mov eax, rescomp
	cmp eax, L1
		jg ifi3
		jl else3
ifi3:

push offset L2
call outStreamW
	push 1
		jmp local5
	jmp ifEnd3
else3:

push offset L4
call outStreamW
	push 0
		jmp local5
ifEnd3:
ifEnd1:
local5:
	pop eax
	ret
comp ENDP

main PROC
	push L5
	push L6
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop eax
	jo overflow
	mov negnENTRY, eax
	push offset L7
		call getparm
	push eax
	pop parmsudaENTRY

	push L8
		call getnump
	push eax
	push L6
	push L9
	push L10
	pop ebx
	pop eax
	cmp ebx,0
	je SOMETHINGWRONG
	cdq
	idiv ebx
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
	jo overflow
	mov parmsudadENTRY, eax
	push L11
		call retnum
	push eax
	push L12
	pop eax
	pop ebx
	mul ebx
	push eax
	push L8
	push L13
	pop eax
	pop ebx
	add eax, ebx
	push eax
	pop eax
	pop ebx
	mul ebx
	push eax
	pop eax
	jo overflow
	mov fourENTRY, eax
	push offset L14
	pop slovoENTRY

		call stringLen
	push eax
	push slovoENTRY
		call stringLen
	push eax
	pop eax
	jo overflow
	mov lenENTRY, eax
	push negnENTRY
	push L15
		call sum
	push eax
	pop eax
	jo overflow
	mov getsumENTRY, eax
	push L8
	pop eax
	jo overflow
	mov expENTRY, eax
	push L8
	push L6
	pop eax
	pop ebx
	mul ebx
	push eax
	push L16
	push L12
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
	jo overflow
	mov expENTRY, eax
	push L12
	push L10
	pop ebx
	pop eax
	cmp ebx,0
	je SOMETHINGWRONG
	cdq
	idiv ebx
	push edx
	push L5
	push L11
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop eax
	pop ebx
	mul ebx
	push eax
	pop eax
	jo overflow
	mov expENTRY, eax

push negnENTRY
call outStreamN

push parmsudadENTRY
call outStreamN

push expENTRY
call outStreamN

push getsumENTRY
call outStreamN

push lenENTRY
call outStreamN

push parmsudaENTRY
call outStreamW

push fourENTRY
call outStreamN

push offset L17
call outStreamW

push slovoENTRY
call outStreamW
	mov eax, L8
	cmp eax, L9
		jg ifi4
		jl else4
ifi4:
	mov eax, L12
	cmp eax, L10
		jl ifi5
		jg else5
ifi5:

push offset L18
call outStreamW
	jmp ifEnd5
else5:

push offset L19
call outStreamW
ifEnd5:

push slovoENTRY
call outStreamW
	jmp ifEnd4
else4:

push offset L20
call outStreamW
ifEnd4:
	push 0
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