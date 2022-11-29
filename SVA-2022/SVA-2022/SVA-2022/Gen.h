#pragma once
#include"stdafx.h"

#define BEGIN	".586\n"\
				".model flat, stdcall\n"\
				"includelib libucrt.lib\n"\
				"includelib kernel32.lib\n"\
				"incudelib ../Debug/GenLib.lib\n"\
				"ExitProcess		PROTO:DWORD\n"\
				"SetConsoleTitleA	PROTO : DWORD\n"\
				"GetStdHandle		PROTO : DWORD\n"\
				"WriteConsoleA		PROTO : DWORD, : DWORD, : DWORD, : DWORD, : DWORD\n"

#define EXTRN	"EXTRN Strlen proc\n"\
				"EXTRN Rand proc\n"\
				".stack 4096\n"

#define CONST	".const\n"

#define DATA	".data\n"

#define CODE	".code\n"

#define END		"push 0\n"\
				"call ExitProcess\n"\
				"main ENDP\n"\
				"end main\n"

namespace Generator {
	void CodeGeneration(Lex::Tables& tables);
}