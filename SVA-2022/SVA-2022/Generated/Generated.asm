.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib ../Debug/GenLib.lib
ExitProcess		PROTO:DWORD

Strlen	PROTO : DWORD
Rand	PROTO : DWORD
.stack 4096

.const

		mainLINT0 SDWORD 1
		mainLINT1 SDWORD 5
		mainLSTR2 byte '1234567890', 0
		mainLSTR3 byte '1234567890', 0
		mainLSTR4 byte '๊๎ํ๒๐๎๋üํ๛้ ๏๐่์ๅ๐', 0
.data

		maxresult sdword 0
		fsc dword ?
		mainx sdword 0
		mainy sdword 0
		mainz sdword 0
		mainsa dword ?
		mainsb dword ?
		mainsc dword ?
.code


;----------- max ------------
max PROC,
	nmax : sdword, mmax : sdword  
push ebx
push edx

mov edx, maxn
cmp edx, maxm

jg right1
jl wrong1
right1:
push n
pop ebx
mov maxresult, ebx

wrong1:
push m
pop ebx
mov maxresult, ebx


pop ebx
pop edx
mov eax, maxresult
ret
max ENDP
;------------------------------


;----------- fs ------------
fs PROC,
	afs : dword, bfs : dword  
push ebx
push edx


;----------- substr ------------
substr PROC,
	asubstr : dword, psubstr : sdword, nsubstr : sdword  
push ebx
push edx

mov ecx, fsa
mov fsc, ecx

pop ebx
pop edx
mov eax, fsc
ret
substr ENDP
;------------------------------


;----------- MAIN ------------
main PROC
push p
call strlen

push LINT0
pop ebx
mov mainx, ebx

push LINT1
pop ebx
mov mainy, ebx

mov mainsa, offset mainLSTR2
mov mainsb, offset mainLSTR3
push x
push y
pop ebx
mov mainz, ebx

mov ecx, mainsa
mov mainsc, ecx

push offset LSTR4
call outstr



push z
call outnumb



push sc
call outstr



push sc
call outstr



pop ebx
pop edx
mov eax, ออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออýýýýออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออýýýý
ret
substr ENDP
;------------------------------

push 0
call ExitProcess
main ENDP
end main

