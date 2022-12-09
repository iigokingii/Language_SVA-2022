#pragma once
#include"stdafx.h"
#include<iostream>
#define MaxNumberOfSeparators 13

//char t[10];
//itoa(LitNumber, t, 10);
namespace Lex {
	struct Tables {
		IT::IdTable idtable;
		LT::LexTable lextable;
	};
	Tables LexAnalizer(In::IN in, Out::OUT out);
	void getid(int& stroke, char* id, char** words, int m);
	bool CMP(char* str1, const char* str2);
}