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
.stack 4096
.const
		L0 SDWORD 100
.data
		maina sdword 0
.code

;----------- MAIN ------------

main PROC
push L0
call Rand
mov maina,eax


push maina
call PrintNumb



;------------------------------

push 0
call ExitProcess
main ENDP
end main

