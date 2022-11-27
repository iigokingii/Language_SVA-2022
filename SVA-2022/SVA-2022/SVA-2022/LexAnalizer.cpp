#include"stdafx.h"
// усечение , литералы('), параметр p('), таблица символов('),область видимости(')
#pragma warning(disable: 4996)
namespace Lex {
	char* buff = NULL;
	char* NameOfFunc = NULL;
	char* id = new char[TI_MAXSIZE];
	bool Flag = false;
	int LitNumber = 0;
	bool CMP(char* str1, const char* str2) {
		int i = 0;
		while (str1[i] != '\0' && str2[i] != '\0') {
			if (str1[i] != str2[i]) {
				return false;
			}
			i++;
			if (str1[i] == '\0' && str2[i] != '\0' || str2[i] == '\0' && str2[i] != '\0') {
				return false;
			}

		}
		return true;
	}

	void getid(int& stroke, char* id, char** words, int m) {
		int size = strlen(words[stroke]);
		//int counter = strlen(NameOfFunc);
		if (size + /*counter*/ +1 > ID_MAXSIZE)
			throw ERROR_THROW(162);
		/*strcpy(id, NameOfFunc);*/
		strcpy(id, words[stroke]);
	}

	Tables LexAnalizer(In::IN in, Out::OUT out) {
		Tables tables;
		LT::LexTable lextable = LT::Create(in.size);
		IT::IdTable idtable = IT::Create(in.size);
		LT::Entry LtEntr;
		IT::Entry ItEntr;

		char** words = new char* [MAX_NUMBER_OF_WORDS];
		for (int i = 0; i < MAX_NUMBER_OF_WORDS; i++)
			words[i] = new char[MAX_LENGTH_OF_WORD] {NULL};
		words = DivideTexT((char*)in.text, in.size);
		int stroke = -1;
		int sn = 0;
		while (words[stroke] != NULL) {
			stroke++;
			if (words[stroke] == NULL)
				break;
			FST::FST fstInt(words[stroke], FST_NUMB);
			//cout << words[stroke];
			if (FST::execute(fstInt)) {

				LtEntr.lexema = LEX_NUMB;
				LtEntr.sn = sn;
				LtEntr.idxTI = LT_TI_NULLIDX;
				LT::Add(lextable, LtEntr);
				continue;
			}
			FST::FST fstString(words[stroke], FST_STROKE);
			if (FST::execute(fstString)) {

				LtEntr.lexema = LEX_STROKE;
				LtEntr.sn = sn;
				LtEntr.idxTI = LT_TI_NULLIDX;
				LT::Add(lextable, LtEntr);
				continue;

			}
			FST::FST fstFunc(words[stroke], FST_FUNCTION);
			if (FST::execute(fstFunc)) {

				LtEntr.lexema = LEX_FUNCTION;
				LtEntr.sn = sn;
				LtEntr.idxTI = LT_TI_NULLIDX;
				LT::Add(lextable, LtEntr);
				continue;

			}
			FST::FST fstNew(words[stroke], FST_NEW);
			if (FST::execute(fstNew)) {

				LtEntr.lexema = LEX_NEW;
				LtEntr.sn = sn;
				LtEntr.idxTI = LT_TI_NULLIDX;
				LT::Add(lextable, LtEntr);
				continue;
			}
			FST::FST fstRet(words[stroke], FST_RETURN);
			if (FST::execute(fstRet)) {
				LtEntr.lexema = LEX_RETURN;
				LtEntr.sn = sn;
				LtEntr.idxTI = LT_TI_NULLIDX;
				LT::Add(lextable, LtEntr);
				continue;
			}
			FST::FST fstPrint(words[stroke], FST_PRINT);
			if (FST::execute(fstPrint)) {
				LtEntr.lexema = LEX_PRINT;
				LtEntr.sn = sn;
				LtEntr.idxTI = LT_TI_NULLIDX;
				LT::Add(lextable, LtEntr);
				continue;

			}
			FST::FST fstMain(words[stroke], FST_MAIN);
			if (FST::execute(fstMain)) {

				LtEntr.lexema = LEX_MAIN;
				LtEntr.sn = sn;
				LtEntr.idxTI = LT_TI_NULLIDX;
				strcpy(ItEntr.scope, "main");
				NameOfFunc = (char*)"main";
				buff = (char*)"main";
				LT::Add(lextable, LtEntr);
				continue;

			}
			FST::FST fstSemi(words[stroke], FST_SEMICOLON);
			if (FST::execute(fstSemi)) {
				LtEntr.lexema = LEX_SEMICOLON;
				LtEntr.sn = sn;
				LtEntr.idxTI = LT_TI_NULLIDX;
				LT::Add(lextable, LtEntr);
				continue;

			}
			FST::FST fstNewLine(words[stroke], FST_NEWLINE);
			if (FST::execute(fstNewLine)) {
				sn++;
				continue;
			}
			FST::FST fstLBrace(words[stroke], FST_LEFTBRACE);
			if (FST::execute(fstLBrace)) {
				LtEntr.lexema = LEX_LEFTBRACE;
				LtEntr.sn = sn;
				LtEntr.idxTI = LT_TI_NULLIDX;
				LT::Add(lextable, LtEntr);
				continue;
			}
			FST::FST fstBrace(words[stroke], FST_BRACELET);
			if (FST::execute(fstBrace)) {
				LtEntr.lexema = LEX_BRACELET;
				LtEntr.sn = sn;
				LtEntr.idxTI = LT_TI_NULLIDX;
				LT::Add(lextable, LtEntr);
				continue;
			}
			FST::FST fstLH(words[stroke], FST_LEFTTHESIS);
			if (FST::execute(fstLH)) {
				LtEntr.priority = 1;
				LtEntr.lexema = LEX_LEFTHESIS;
				LtEntr.sn = sn;
				LtEntr.idxTI = LT_TI_NULLIDX;
				LT::Add(lextable, LtEntr);
				continue;

			}
			FST::FST fstRH(words[stroke], FST_RIGHTTHESIS);
			if (FST::execute(fstRH)) {
				LtEntr.priority = 1;
				LtEntr.lexema = LEX_RIGHTHESIS;
				LtEntr.sn = sn;
				LtEntr.idxTI = LT_TI_NULLIDX;
				LT::Add(lextable, LtEntr);
				if (NameOfFunc != buff) {
					buff = NameOfFunc;
				}
				continue;
			}
			FST::FST fsrComma(words[stroke], FST_COMMA);
			if (FST::execute(fsrComma)) {
				LtEntr.lexema = LEX_COMMA;
				LtEntr.sn = sn;
				LtEntr.idxTI = LT_TI_NULLIDX;
				LT::Add(lextable, LtEntr);
				continue;
			}

			if (stroke >= 1 && CMP(words[stroke - 1], "return")) {//return z || return 0;
				FST::FST fstN(words[stroke], FST_INTLIT);
				if (FST::execute(fstN))
					LtEntr.lexema = LEX_LITERAL;
				else
					LtEntr.lexema = LEX_ID;
				LtEntr.sn = sn;
				LtEntr.idxTI = TI_NULLIDX;
				getid(stroke, id, words, 0);
				int position = IT::IsId(idtable, id);
				LtEntr.idxTI = position;
				LT::Add(lextable, LtEntr);
				continue;
			}

			FST::FST fstpr(words[stroke - 1], FST_PRINT);
			FST::FST fststrl(words[stroke - 2], FST_STRLEN);
			if (stroke >= 1 && (FST::execute(fstpr) || FST::execute(fststrl))) {//print 'контрольный пример'; strlen(string p)
				FST::FST fstLit(words[stroke], FST_STRLIT);
				if (FST::execute(fstLit)) {
					LtEntr.lexema = LEX_LITERAL;
					LtEntr.sn = sn;
					LtEntr.idxTI = idtable.size;

					ItEntr.idtype = IT::L;
					ItEntr.iddatatype = IT::STR;
					ItEntr.idxfirstLE = lextable.size;
					ItEntr.value.vstr.len = strlen(words[stroke]);
					char temporary[10] = "LSTR";
					char* temp = itoa(LitNumber, buff, 10);
					strcat(temporary, temp);
					strcpy(ItEntr.id, temporary);
					strcpy_s(ItEntr.value.vstr.str, words[stroke]);
					ItEntr.value.vstr.len = strlen(words[stroke]);

					LT::Add(lextable, LtEntr);
					IT::Add(idtable, ItEntr);
					LitNumber++;
					continue;
				}
				getid(stroke, id, words, 0);
				int position = IT::IsId(idtable, id);
				LtEntr.idxTI = position;
				LtEntr.lexema = LEX_ID;
				LtEntr.sn = sn;
				LT::Add(lextable, LtEntr);
				continue;
			}


			FST::FST FSTI(words[stroke - 2], FST_NUMB);
			FST::FST FSTS(words[stroke - 2], FST_STROKE);
			FST::FST FSTF(words[stroke - 1], FST_FUNCTION);
			if (stroke >= 2 && (FST::execute(FSTI) || FST::execute(FSTS)) && FST::execute(FSTF)) { //integer function fi
				
				int size = strlen(words[stroke]);
				if (size + 1 > ID_MAXSIZE)
					throw ERROR_THROW_IN(162, sn, stroke);

				ItEntr.iddatatype = (CMP(words[stroke - 2], "string") ? IT::STR : IT::INT);
				ItEntr.idtype = IT::F;
				ItEntr.idxfirstLE = lextable.size;

				LtEntr.idxTI = idtable.size;
				LtEntr.sn = sn;
				LtEntr.lexema = LEX_ID;

				
				strcpy(ItEntr.id, words[stroke]);
				strcpy(ItEntr.scope, words[stroke]);
				LT::Add(lextable, LtEntr);
				IT::Add(idtable, ItEntr);
				NameOfFunc = words[stroke];

				/*if (buff == NameOfFunc&&!Flag) {
					buff = NameOfFunc;
					NameOfFunc = words[stroke];
					Flag = true;
				}*/
				continue;
			}
			FST::FST FSTSt(words[stroke - 1], FST_STROKE);
			FST::FST FSTIn(words[stroke - 1], FST_NUMB);
			FST::FST FSTC(words[stroke - 2], FST_COMMA);
			FST::FST FSTLH(words[stroke - 2], FST_LEFTTHESIS);
			if (stroke >= 2 && (FST::execute(FSTSt) || FST::execute(FSTIn)) && (FST::execute(FSTC) || FST::execute(FSTLH))) {//(integer x, integer y) || (string a, string b) 
				ItEntr.iddatatype = (CMP(words[stroke - 1], "string") ? IT::STR : IT::INT);
				ItEntr.idtype = IT::P;
				ItEntr.idxfirstLE = lextable.size;

				LtEntr.idxTI = idtable.size;
				LtEntr.lexema = LEX_ID;
				LtEntr.sn = sn;

				int col = strlen(NameOfFunc) + strlen(words[stroke]);
				if (col + 1 > ID_MAXSIZE) //область функции+ param + \0
					throw ERROR_THROW(162);

				//strcpy(ItEntr.id, NameOfFunc);
				strcpy(ItEntr.id, words[stroke]);

				if (ItEntr.iddatatype == IT::INT)
				{
					ItEntr.value.vint = 0;
				}
				else
				{
					strcpy_s(ItEntr.value.vstr.str, "");
					ItEntr.value.vstr.len = 0;
				}
				LT::Add(lextable, LtEntr);
				IT::Add(idtable, ItEntr);
				continue;
			}
			FST::FST FSTDecl(words[stroke - 2], FST_NEW);
			FST::FST FSTSTR(words[stroke - 1], FST_STROKE);
			FST::FST FSTINT(words[stroke - 1], FST_NUMB);
			FST::FST FSTFunc(words[stroke], FST_FUNCTION);
			if (stroke >= 2 && FST::execute(FSTDecl) && (FST::execute(FSTSTR) || FST::execute(FSTINT)) && !FST::execute(FSTF)) {//declare integer x;
				ItEntr.iddatatype = (CMP(words[stroke - 1], "string") ? IT::STR : IT::INT);
				ItEntr.idxfirstLE = lextable.size;
				LtEntr.lexema = LEX_ID;
				LtEntr.idxTI = idtable.size;
				LtEntr.sn = sn;

				int col = strlen(NameOfFunc) + strlen(words[stroke]);
				if (col + 1 > ID_MAXSIZE) //область функции+ param + \0
					throw ERROR_THROW(162);

				//strcpy(ItEntr.id, NameOfFunc);
				strcpy(ItEntr.id, words[stroke]);
				if (ItEntr.iddatatype == IT::INT)
				{
					ItEntr.value.vint = 0;
				}
				else
				{
					strcpy_s(ItEntr.value.vstr.str, "");
					ItEntr.value.vstr.len = 0;
				}
				FST::FST fstrl(words[stroke], FST_STRLEN);
				if (FST::execute(fstrl)) {
					buff = NameOfFunc;
					NameOfFunc = words[stroke];
					LtEntr.lexema = LEX_ID;
					ItEntr.idtype = IT::F;

				}
				else {
					ItEntr.idtype = IT::V;
				}
				LT::Add(lextable, LtEntr);
				IT::Add(idtable, ItEntr);
				continue;
			}
			FST::FST FSTEQ1(words[stroke + 1], FST_EQUAL);
			if (FST::execute(FSTEQ1)) {
				//к виду : i = ; substr c (fsc)исправить scope(вроде как)
				getid(stroke, id, words, 0);
				int position = IT::IsId(idtable, id);
				LtEntr.idxTI = position;
				LtEntr.lexema = LEX_ID;
				LtEntr.sn = sn;
				LT::Add(lextable, LtEntr);

				stroke++;
				LtEntr.idxTI = TI_NULLIDX;
				LtEntr.lexema = LEX_EQUAL;
				LtEntr.sn = sn;
				LT::Add(lextable, LtEntr);
				stroke++;

				//строка?
				FST::FST FSTSL(words[stroke], FST_STRLIT);
				if (FST::execute(FSTSL)) {
					LtEntr.lexema = LEX_LITERAL;
					LtEntr.sn = sn;
					LtEntr.idxTI = idtable.size;
					LT::Add(lextable, LtEntr);
					int symbols = strlen(words[stroke]);
					if (symbols > TI_STR_MAXSIZE)
						throw ERROR_THROW_IN(164, sn + 1, stroke + 1);				//добавить исключение 

					ItEntr.idtype = IT::L;
					ItEntr.iddatatype = IT::STR;
					ItEntr.idxfirstLE = lextable.size;
					ItEntr.value.vstr.len = strlen(words[stroke]);
					char temporary[10] = "LSTR";
					char* temp = itoa(LitNumber, buff, 10);
					strcat(temporary, temp);
					strcpy(ItEntr.id, temporary);
					strcpy_s(ItEntr.value.vstr.str, words[stroke]);
					ItEntr.value.vstr.len = strlen(words[stroke]);
					IT::Add(idtable, ItEntr);									//TODO
					LitNumber++;
					continue;
				}
				//цифра или функция;
				else {
					FST::FST FSN(words[stroke], FST_INTLIT);
					if (FST::execute(FSN)) {
						LtEntr.lexema = LEX_LITERAL;
						LtEntr.sn = sn;
						LtEntr.idxTI = TI_NULLIDX;    //jghjghghgh
						LT::Add(lextable, LtEntr);
						ItEntr.iddatatype = IT::INT;
						ItEntr.idtype = IT::L;
						ItEntr.value.vint = stoi(words[stroke]);
						ItEntr.idxfirstLE = lextable.size;
						char temporary[10] = "LINT";
						char tmp[6];
						itoa(LitNumber, tmp, 10);
						strcat(temporary, tmp);
						strcpy(ItEntr.id, temporary);
						LitNumber++;
						IT::Add(idtable, ItEntr);
						continue;
					}
					else {//z=x*(x+y); или = функция
						int counter = 0;
						char* buff = new char[TI_MAXSIZE];
						while (!CMP(words[stroke], ";")) { //+,-,/,*
							FST::FST FSTSUB(words[stroke], FST_SUBSTR);
							if (FST::execute(FSTSUB)) {
								LtEntr.lexema = LEX_ID;
								LtEntr.sn = sn;
								getid(stroke, id, words, 0);

								int position = IT::IsId(idtable, (char*)"substr");			//хуйня переделывай
								LtEntr.idxTI = position;
								LT::Add(lextable, LtEntr);
								stroke++;
								continue;
							}
							else {//z=x*(x+y)
								FST::FST fstLH2(words[stroke], FST_LEFTTHESIS);
								if (FST::execute(fstLH2)) {
									LtEntr.priority = 1;
									LtEntr.lexema = LEX_LEFTHESIS;
									LtEntr.sn = sn;
									LtEntr.idxTI = LT_TI_NULLIDX;
									LT::Add(lextable, LtEntr);
									stroke++;
									continue;

								}
								FST::FST fstRH2(words[stroke], FST_RIGHTTHESIS);
								if (FST::execute(fstRH2)) {
									LtEntr.priority = 1;
									LtEntr.lexema = LEX_RIGHTHESIS;
									LtEntr.sn = sn;
									LtEntr.idxTI = LT_TI_NULLIDX;
									LT::Add(lextable, LtEntr);
									stroke++;
									continue;
								}
								FST::FST FSTPl(words[stroke], FST_PLUS);
								if (FST::execute(FSTPl)) {
									LtEntr.priority = 2;
									LtEntr.lexema = LEX_PLUS;
									LtEntr.sn = sn;
									LtEntr.idxTI = LT_TI_NULLIDX;
									LT::Add(lextable, LtEntr);
									stroke++;
									continue;
								}
								FST::FST FSTMin(words[stroke], FST_MINUS);
								if (FST::execute(FSTMin)) {
									LtEntr.priority = 2;
									LtEntr.lexema = LEX_MINUS;
									LtEntr.sn = sn;
									LtEntr.idxTI = LT_TI_NULLIDX;
									LT::Add(lextable, LtEntr);
									stroke++;
									continue;
								}
								FST::FST FSTSt(words[stroke], FST_STAR);
								if (FST::execute(FSTSt)) {
									LtEntr.priority = 3;
									LtEntr.lexema = LEX_STAR;
									LtEntr.sn = sn;
									LtEntr.idxTI = LT_TI_NULLIDX;
									LT::Add(lextable, LtEntr);
									stroke++;
									continue;
								}
								FST::FST FSTDS(words[stroke], FST_DIRSLASH);
								if (FST::execute(FSTDS)) {
									LtEntr.priority = 3;
									LtEntr.lexema = LEX_DIRSLASH;
									LtEntr.sn = sn;
									LtEntr.idxTI = TI_NULLIDX;
									LT::Add(lextable, LtEntr);
									stroke++;
									continue;
								}
								FST::FST FSTcomma(words[stroke], FST_COMMA);
								if (FST::execute(FSTcomma)) {
									LtEntr.lexema = LEX_COMMA;
									LtEntr.sn = sn;
									LtEntr.idxTI = LT_TI_NULLIDX;
									LT::Add(lextable, LtEntr);
									stroke++;
									continue;
								}
								FST::FST FSTD(words[stroke], FST_ID);
								if (FST::execute(FSTD)) {
									getid(stroke, id, words, 0);
									position = IT::IsId(idtable, id);
									LtEntr.idxTI = position;
									LtEntr.lexema = LEX_ID;
									LtEntr.sn = sn;
									LT::Add(lextable, LtEntr);
									stroke++;
									continue;
								}
								FST::FST fstlin(words[stroke], FST_INTLIT);
								if (FST::execute(fstlin)) {
									LtEntr.lexema = LEX_LITERAL;
									LtEntr.idxTI = idtable.size;
									LtEntr.sn = sn;
									LT::Add(lextable, LtEntr);
									stroke++;
									continue;
								}
							}
						}
						LtEntr.lexema = LEX_SEMICOLON;
						LtEntr.sn = sn;
						LtEntr.idxTI = TI_NULLIDX;
						LT::Add(lextable, LtEntr);
						stroke++;
						sn++;
						continue;
					}
				}
				throw ERROR_THROW_IN(163, sn+1, stroke+1);
			}
			
		}
		LT::showTable(lextable);
		LT::WriteTable(lextable,out);
		IT::showTable(idtable);
		IT::WriteTable(idtable,out);
		tables.idtable = idtable;
		tables.lextable = lextable;
		return tables;
	}
}

