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
	L0 DWORD 5
	L1 BYTE "Hello", 0
	L2 BYTE "World!", 0
	diverror BYTE "Error: Делить на 0 нельзя"

.data
	sumx DWORD ?
	entrylena DWORD ?
	entrysome DWORD ?
	entrywoo DWORD ?
	entrycm DWORD ?

.code

sum PROC sumb : DWORD
	push sumb
	pop edx
	push sumb
		call strln
	push eax
	pop sumx
	push sumx
	ret
	er_zero:
push offset diverror
	call readw
	push 0
	call ExitProcess
sum ENDP

main PROC
	push L0
	pop entrycm
	push offset L1
	pop entrysome
	push offset L2
	pop entrywoo
	push entrysome
	push entrywoo
	pop edx
	pop edx
	push entrywoo
	push entrysome
		call Strcmp
	push eax
	pop entrylena
mov eax, entrylena
mov ebx, entrycm
cmp eax, ebx
jl go_true_57
jg go_false_57
go_true_57:
	push entrylena
		call readr
go_false_57:
	
	push 0
	call ExitProcess
	er_zero:
push offset diverror
	call readw
	push 0
	call ExitProcess
	main ENDP
end main