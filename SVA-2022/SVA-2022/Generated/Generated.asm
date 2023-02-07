.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib ../Debug/GenLib.lib
ExitProcess		PROTO:DWORD

Remainder		PROTO : DWORD, :DWORD
Rand			PROTO : DWORD
Input			PROTO : DWORD
Printstroke		PROTO : DWORD
PrintNumb		PROTO : DWORD
Strlen			PROTO : DWORD
.stack 4096
.const
		TRUE equ 1
		FALSE equ 0
		L0 word 0
		L1 word 1
		L2 SDWORD 20
		L3 SDWORD 132
.data
		mainb1 word ?
		mainb2 word ?
		mainres sdword 0
.code

;----------- MAIN ------------

main PROC
mov cx, L0
mov mainb1, cx

mov cx, L1
mov mainb2, cx

push mainb1
pop bx
and bx, cx

cmp bx, TRUE

jz right1
jnz wrong1
	right1:
push L2
pop ebx
mov mainres, ebx

jmp next1
	wrong1:
push L3
pop ebx
mov mainres, ebx

next1:

push mainres
call PrintNumb



;------------------------------

push 0
call ExitProcess
main ENDP
end main

