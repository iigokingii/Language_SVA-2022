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
		L0 SDWORD 123
		L1 SDWORD 45
		L2 SDWORD 15
		L3 SDWORD 2
		L4 byte 'some text', 0
		L5 SDWORD 13
		L6 byte 'Length of str1 is ', 0
		L7 SDWORD 1
		L8 SDWORD 10
		L9 SDWORD 12
		L10 byte "a", 0
		TRUE equ 1
		FALSE equ 0
		L11 word 0
		L12 SDWORD 22
		L13 byte 'Result of function max: ', 0
		L14 byte 'нижний и верхний пределы:', 0
		L15 byte 'Result of function loo :', 0
		L16 SDWORD 1000
		L17 byte 'Rand number :', 0
.data
		maxresult sdword 0
		maxk sdword 0
		maxstr1 dword ?
		maxlen sdword 0
		circuita sdword 0
		circuititer sdword 0
		maina sdword 0
		mainb sdword 0
		mainc sdword 0
		mainS dword ?
		mainb1 word ?
		mainresult sdword 0
		mainstart sdword 0
		mainend sdword 0
		maink sdword 0
		mainran sdword 0
		mainx sdword 0
.code

;----------- max ------------

max PROC,
	maxq : sdword, maxv : sdword, maxz : sdword  
push ebx
push edx

push L0
pop ebx
mov maxk, ebx

mov edx, maxq
cmp edx, maxv

jl right1
jg wrong1
	right1:
mov edx, maxv
cmp edx, maxz

jl right2
jg wrong2
	right2:
push L1
push L2
pop ebx
pop eax
cdq
idiv ebx
push eax
push L3
pop ebx
pop eax
imul eax, ebx
push eax
pop ebx
mov maxresult, ebx

mov maxstr1, offset L4
jmp next2
	wrong2:
push maxk
push maxq
pop ebx
pop eax
imul eax, ebx
push eax
push maxz
pop ebx
pop eax
imul eax, ebx
push eax
pop ebx
mov maxresult, ebx

next2:
jmp next1
	wrong1:
push L5
pop ebx
mov maxresult, ebx

next1:

push maxstr1
call PrintStroke


push maxstr1
call Strlen
mov maxlen, eax

push offset L6
call PrintStroke



push maxlen
call PrintNumb



pop ebx
pop edx
mov eax, maxresult
ret
max ENDP
;------------------------------


;----------- circuit ------------

circuit PROC,
	circuitstart : sdword, circuitend : sdword  
push ebx
push edx

push L3
pop ebx
mov circuita, ebx

push L7
pop ebx
mov circuititer, ebx

mov edx, circuitstart
cmp edx, circuitend

jl repeat3
jmp repeatnext3
repeat3:


push circuitstart
call PrintNumb


push circuitstart
push L3
pop ebx
pop eax
add eax, ebx
push eax
pop ebx
mov circuitstart, ebx

push circuititer
push L3
pop ebx
pop eax
imul eax, ebx
push eax
pop ebx
mov circuititer, ebx

mov edx, circuitstart
cmp edx, circuitend

jl repeat3
repeatnext3:

pop ebx
pop edx
mov eax, circuititer
ret
circuit ENDP
;------------------------------


;----------- MAIN ------------

main PROC
push L7
pop ebx
mov maina, ebx

push L8
pop ebx
mov mainb, ebx

push L9
pop ebx
mov mainc, ebx

mov mainS, offset L10
mov cx, L11
mov mainb1, cx

push mainc
push mainb
push maina
call max
mov mainresult, eax
push L12
pop ebx
add eax, ebx
push eax
mov mainresult, eax


push offset L13
call PrintStroke



push mainresult
call PrintNumb



push offset L14
call PrintStroke


call Input
mov mainstart, eax
call Input
mov mainend, eax
push mainend
push mainstart
call circuit

mov maink,eax


push offset L15
call PrintStroke



push maink
call PrintNumb


push L16
call Rand
mov mainran, eax

push offset L17
call PrintStroke



push mainran
call PrintNumb


push L9
push L3
pop ebx
pop eax
cdq
idiv ebx
push eax
pop ebx
mov mainx, ebx


push mainx
call PrintNumb



;------------------------------

push 0
call ExitProcess
main ENDP
end main

