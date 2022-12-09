.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib ../Debug/GenLib.lib
ExitProcess		PROTO:DWORD

Strlen			PROTO : DWORD
Rand			PROTO : DWORD
Input			PROTO : DWORD
Printstroke	PROTO : DWORD
PrintNumb		PROTO : DWORD
.stack 4096

.const

		L0 byte "q", 0
.data

		mainS dword ?
.code


;----------- MAIN ------------

main PROC
mov mainS, offset L0

push mainS
call PrintStroke



;------------------------------

push 0
call ExitProcess
main ENDP
end main

