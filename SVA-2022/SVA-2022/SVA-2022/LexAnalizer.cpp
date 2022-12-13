#include"stdafx.h"
// усечение , литералы('), параметр p('), таблица символов('),область видимости(')
#pragma warning(disable: 4996)
namespace Lex {
	char* buff = NULL;
	char* NameOfFunc = NULL;
	char* id = new char[TI_MAXSIZE];
	bool Flag = false;
	bool findFunc = false;
	int LitNumber = 0;
	int numberOfPar=0;
	int posOfFunction;
	bool CMP(char* str1, const char* str2) {
		int i = 0;
		while (str1[i] != '\0' && str2[i] != '\0') {
			if (str1[i] != str2[i]) {
				return false;
			}
			i++;
			if (str1[i] == '\0' && str2[i] != '\0' || str2[i] == '\0' && str1[i] != '\0') {
				return false;
			}

		}
		if (str1[i] == '\0' && str2[i] != '\0' || str2[i] == '\0' && str1[i] != '\0') {
			return false;
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
		bool FindMain = false;
		int countOfMain = 0;

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
			
			FST::FST fstState(words[stroke], FST_STATE);
			if (FST::execute(fstState)) {
				LtEntr.lexema = LEX_STATE;
				LtEntr.sn = sn;
				LtEntr.idxTI = LT_TI_NULLIDX;
				LT::Add(lextable, LtEntr);
				stroke++;
				while (!CMP(words[stroke] ,"$")) {

					FST::FST id(words[stroke], FST_ID);
 					if (FST::execute(id)) {
						LtEntr.lexema = LEX_ID;
						LtEntr.sn = sn;
						char* temp = new char[TI_MAXSIZE];
						getid(stroke, temp, words, 0);
						int tmp = IT::IsId(idtable, temp);
						//IT::Entry e = IT::GetEntry(tables.idtable, tmp);
						LtEntr.idxTI = tmp;
						LT::Add(lextable, LtEntr);
						stroke++;
						continue;
					}
					FST::FST fstcol(words[stroke], FST_COLON);
					if (FST::execute(fstcol)) {
						LtEntr.lexema = LEX_COLON;
						LtEntr.sn = sn;
						LtEntr.idxTI = TI_NULLIDX;
						LT::Add(lextable, LtEntr);
						stroke++;
						continue;
					}
					FST::FST fstG1(words[stroke], FST_GREATER);
					if (FST::execute(fstG1)) {
						LtEntr.lexema = LEX_GREATER;
						LtEntr.sn = sn;
						LtEntr.idxTI = LT_TI_NULLIDX;
						LT::Add(lextable, LtEntr);
						stroke++;
						continue;
					}

					FST::FST fstS1(words[stroke], FST_SMALLER);
					if (FST::execute(fstS1)) {
						LtEntr.lexema = LEX_SMALLER;
						LtEntr.sn = sn;
						LtEntr.idxTI = LT_TI_NULLIDX;
						LT::Add(lextable, LtEntr);
						stroke++;
						continue;
					}
				}
			}
			if (stroke >= 2) {
				FST::FST fstD(words[stroke], FST_DOL);
				if (FST::execute(fstD)) {
					LtEntr.lexema = LEX_DOL;
					LtEntr.sn = sn;
					LtEntr.idxTI = LT_TI_NULLIDX;
					LT::Add(lextable, LtEntr);
					stroke++;
					while (!CMP(words[stroke], "$")) {
						FST::FST fstCor(words[stroke], FST_CORRECTLY);
						if (FST::execute(fstCor)) {
							LtEntr.lexema = LEX_CORRECTLY;
							LtEntr.sn = sn;
							LtEntr.idxTI = LT_TI_NULLIDX;
							LT::Add(lextable, LtEntr);
							stroke++;
							continue;
						}
						FST::FST fstWr(words[stroke], FST_WRONG);
						if (FST::execute(fstWr)) {
							LtEntr.lexema = LEX_WRONG;
							LtEntr.sn = sn;
							LtEntr.idxTI = LT_TI_NULLIDX;
							LT::Add(lextable, LtEntr);
							stroke++;
							continue;
						}
						FST::FST FSTcol(words[stroke], FST_COLON);
						if (FST::execute(FSTcol)) {
							LtEntr.lexema = LEX_COLON;
							LtEntr.sn = sn;
							LtEntr.idxTI = TI_NULLIDX;
							LT::Add(lextable, LtEntr);
							stroke++;
							continue;
						}
						FST::FST fstLBrace(words[stroke], FST_LEFTBRACE);
						if (FST::execute(fstLBrace)) {
							LtEntr.lexema = LEX_LEFTBRACE;
							LtEntr.sn = sn;
							LtEntr.idxTI = LT_TI_NULLIDX;
							LT::Add(lextable, LtEntr);
							stroke++;
							continue;
						}
						FST::FST fstBrace(words[stroke], FST_BRACELET);
						if (FST::execute(fstBrace)) {
							LtEntr.lexema = LEX_BRACELET;
							LtEntr.sn = sn;
							LtEntr.idxTI = LT_TI_NULLIDX;
							LT::Add(lextable, LtEntr);
							stroke++;
							continue;
						}
						FST::FST fstEQ(words[stroke], FST_EQUAL);
						if (FST::execute(fstEQ)) {
							LtEntr.lexema = LEX_EQUAL;
							LtEntr.sn = sn;
							LtEntr.idxTI = LT_TI_NULLIDX;
							LT::Add(lextable, LtEntr);
							stroke++;
							continue;
						}
						FST::FST fstSe(words[stroke], FST_SEMICOLON);
						if (FST::execute(fstSe)) {
							LtEntr.lexema = LEX_SEMICOLON;
							LtEntr.sn = sn;
							LtEntr.idxTI = LT_TI_NULLIDX;
							LT::Add(lextable, LtEntr);
							stroke++;
							continue;
						}
						FST::FST fstLine(words[stroke], FST_NEWLINE);
						if (FST::execute(fstLine)) {
							sn++;
							stroke++;
							continue;
						}
						FST::FST FSTB(words[stroke], FST_BOOLEAN);
						if (FST::execute(FSTB)) {
							LtEntr.lexema = LEX_BOOL;
							LtEntr.sn = sn;
							LtEntr.idxTI = LT_TI_NULLIDX;
							LT::Add(lextable, LtEntr);
							stroke++;
							continue;
						}
						FST::FST id(words[stroke], FST_ID);
						if (FST::execute(id)) {
							LtEntr.lexema = LEX_ID;
							LtEntr.sn = sn;
							char* temp = new char[TI_MAXSIZE];
							getid(stroke, temp, words, 0);
							int tmp = IT::IsId(idtable, temp);
							//IT::Entry e = IT::GetEntry(tables.idtable, tmp);
							LtEntr.idxTI = tmp;
							LT::Add(lextable, LtEntr);
							stroke++;
							continue;
						}
					}
					LtEntr.lexema = LEX_DOL;
					LtEntr.sn = sn;
					LtEntr.idxTI = LT_TI_NULLIDX;
					LT::Add(lextable, LtEntr);
					continue;
				}
			}
			FST::FST FSTINP(words[stroke], FST_INPUT);
			FST::FST FSTSTRL(words[stroke], FST_STRLEN);
			FST::FST FSTRAND(words[stroke], FST_RAND);
			if (FST::execute(FSTINP) || FST::execute(FSTSTRL)||FST::execute(FSTRAND)) {
				LtEntr.idxTI = TI_NULLIDX;
				bool findRand=false,findInput=false,findStrlen=false;
				if (CMP(words[stroke], "input")) {
					findInput = true;
					LtEntr.lexema = LEX_INPUT;
				}	
				else if (CMP(words[stroke], "strlen")) {
					LtEntr.lexema = LEX_STRLEN;
					findStrlen = true;
				}
				else if (CMP(words[stroke], "rand")) {
					findRand = true;
					LtEntr.lexema = LEX_RAND;
				}	
				LtEntr.sn = sn;
				LtEntr.priority = 0;
				LT::Add(lextable, LtEntr);
				int counter = 0;
				while (!CMP(words[++stroke], ";")) {
					FST::FST fstLH1(words[stroke], FST_LEFTTHESIS);
					if (FST::execute(fstLH1)) {
						if (idtable.table[lextable.table[posOfFunction].idxTI].idtype == IT::F) {
							findFunc = true;
						}
						LtEntr.priority = 1;
						LtEntr.lexema = LEX_LEFTHESIS;
						LtEntr.sn = sn;
						LtEntr.idxTI = LT_TI_NULLIDX;
						LT::Add(lextable, LtEntr);
						counter++;
						continue;

					}
					FST::FST fstRH1(words[stroke], FST_RIGHTTHESIS);
					if (FST::execute(fstRH1)) {
						if (findFunc) {
							idtable.table[lextable.table[posOfFunction].idxTI].numberOfParam = numberOfPar;
							numberOfPar = 0;
							findFunc = false;
							posOfFunction = 0;
						}
						LtEntr.priority = 1;
						LtEntr.lexema = LEX_RIGHTHESIS;
						LtEntr.sn = sn;
						LtEntr.idxTI = LT_TI_NULLIDX;
						LT::Add(lextable, LtEntr);
						if (NameOfFunc != buff) {
							buff = NameOfFunc;
						}
						counter++;
						continue;
					}
					
					FST::FST FSTID(words[stroke], FST_ID);
					if (FST::execute(FSTID) &&!findRand) {
						getid(stroke, id, words, 0);
						int position = IT::IsId(idtable, id);
						LtEntr.idxTI = position;
						LtEntr.lexema = LEX_ID;
						LtEntr.sn = sn;
						LT::Add(lextable, LtEntr);
						continue;
					}
					FST::FST FSTIN1(words[stroke], FST_INTLIT);
					if (FST::execute(FSTIN1)&&findRand) {
						ItEntr.iddatatype = IT::INT;
						
						ItEntr.idxfirstLE = lextable.size;
						LtEntr.lexema = LEX_LITERAL;
						LtEntr.idxTI = idtable.size;
						LtEntr.sn = sn;
						int col =/* strlen(NameOfFunc)*/ +strlen(words[stroke]);
						if (col + 1 > ID_MAXSIZE) //область функции+ param + \0
							throw ERROR_THROW(162);
						//strcpy(ItEntr.id, NameOfFunc);
						char t[10];
						char lit[10] = "L";
						strcat(lit, itoa(LitNumber, t, 10));
						strcpy(ItEntr.id, lit);

						ItEntr.value.vint = stoi(words[stroke]);
						ItEntr.idtype = IT::L;
						LT::Add(lextable, LtEntr);
						IT::Add(idtable, ItEntr);
					}
					else {
						throw ERROR_THROW_IN(312,sn+1,stroke+1);
					}
				}
				if (counter % 2 != 0) {
					throw ERROR_THROW_IN(312, sn + 1, stroke + 1);
				}
				LtEntr.lexema = LEX_SEMICOLON;
				LtEntr.idxTI = TI_NULLIDX;
				LtEntr.sn = sn;
				LtEntr.priority = 0;
				LT::Add(lextable, LtEntr);
				continue;
			}
			


			FST::FST FSTB1(words[stroke], FST_BOOLEAN);
			if (FST::execute(FSTB1)) {
				LtEntr.lexema = LEX_BOOL;
				LtEntr.sn = sn;
				LtEntr.idxTI = LT_TI_NULLIDX;
				LT::Add(lextable, LtEntr);
				continue;
			}

			FST::FST fstG(words[stroke], FST_GREATER);
			if(FST::execute(fstG)){
				LtEntr.lexema = LEX_GREATER;
				LtEntr.sn = sn;
				LtEntr.idxTI = LT_TI_NULLIDX;
				LT::Add(lextable, LtEntr);
				continue;
			}

			FST::FST fstS(words[stroke], FST_SMALLER);
			if(FST::execute(fstS)){
				LtEntr.lexema = LEX_SMALLER;
				LtEntr.sn = sn;
				LtEntr.idxTI = LT_TI_NULLIDX;
				LT::Add(lextable, LtEntr);
				continue;
			}
			FST::FST fstSym(words[stroke], FST_SYMBOL);
			if (FST::execute(fstSym)) {
				LtEntr.lexema = LEX_SYMBOL;
				LtEntr.sn = sn;
				LtEntr.idxTI = LT_TI_NULLIDX;
				LT::Add(lextable, LtEntr);
				continue;
			}
			

			FST::FST fstInt(words[stroke], FST_NUMB);
			if (FST::execute(fstInt)) {

				LtEntr.lexema = LEX_NUMB;
				LtEntr.sn = sn;
				LtEntr.idxTI = LT_TI_NULLIDX;
				LT::Add(lextable, LtEntr);
				continue;
			}
			FST::FST fstCol(words[stroke], FST_COLON);
			if (FST::execute(fstCol)) {
				LtEntr.lexema = LEX_COLON;
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
				countOfMain++;
				if (countOfMain > 1)
					throw ERROR_THROW_IN(308, sn, stroke);
				LtEntr.lexema = LEX_MAIN;
				LtEntr.sn = sn;
				LtEntr.idxTI = LT_TI_NULLIDX;
				strcpy(ItEntr.scope, "main");
				NameOfFunc = (char*)"main";
				buff = (char*)"main";
				LT::Add(lextable, LtEntr);
				FindMain = true;
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
				if (idtable.table[lextable.table[posOfFunction].idxTI].idtype == IT::F) {
					findFunc = true;
				}
				LtEntr.priority = 1;
				LtEntr.lexema = LEX_LEFTHESIS;
				LtEntr.sn = sn;
				LtEntr.idxTI = LT_TI_NULLIDX;
				LT::Add(lextable, LtEntr);
				continue;

			}
			FST::FST fstRH(words[stroke], FST_RIGHTTHESIS);
			if (FST::execute(fstRH)) {
				if (findFunc) {
					idtable.table[lextable.table[posOfFunction].idxTI].numberOfParam = numberOfPar;
					numberOfPar = 0;
					findFunc = false;
					posOfFunction = 0;
				}
					
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
			if (stroke > 1) {
				FST::FST fstpr(words[stroke - 1], FST_PRINT);
				/*FST::FST fststrl(words[stroke - 2], FST_STRLEN);*/
				if (FST::execute(fstpr) /*|| FST::execute(fststrl)*/) {//print 'контрольный пример'; strlen(string p)
					FST::FST fstLit(words[stroke], FST_STRLIT);
					if (FST::execute(fstLit)) {
						LtEntr.lexema = LEX_LITERAL;
						LtEntr.sn = sn;
						LtEntr.idxTI = idtable.size;

						ItEntr.idtype = IT::L;
						ItEntr.iddatatype = IT::STR;
						ItEntr.idxfirstLE = lextable.size;
						ItEntr.value.vstr.len = strlen(words[stroke]);
						/*char temporary[10] = "LSTR";
						char t[10];
						itoa(LitNumber, t, 10);
						strcat(temporary, t);
						strcpy(ItEntr.id, temporary);*/
						/*strcpy(lit, (char*)LitNumber);*/
						char t[10];
						char lit[10] = "L";
						strcat(lit, itoa(LitNumber, t, 10));
						strcpy(ItEntr.id, lit);

						strcpy_s(ItEntr.value.vstr.str, words[stroke]);
						ItEntr.value.vstr.len = strlen(words[stroke]);
						LT::Add(lextable, LtEntr);
						IT::Add(idtable, ItEntr);
						ItEntr.iddatatype = IT::UNDEF;
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
			}
			


			FST::FST FSTI(words[stroke - 2], FST_NUMB);
			FST::FST FSTS(words[stroke - 2], FST_STROKE);
			FST::FST FSTF(words[stroke - 1], FST_FUNCTION);
			if (stroke >= 2 && (FST::execute(FSTI) || FST::execute(FSTS)) && FST::execute(FSTF)) { //integer function fi

				int size = strlen(words[stroke]);
				if (size + 1 > ID_MAXSIZE)
					throw ERROR_THROW_IN(162, sn, stroke);

				ItEntr.iddatatype = (CMP(words[stroke - 2], "stroke") ? IT::STR : IT::INT);
				ItEntr.idtype = IT::F;
				ItEntr.idxfirstLE = lextable.size;

				LtEntr.idxTI = idtable.size;
				LtEntr.sn = sn;
				LtEntr.lexema = LEX_ID;

				posOfFunction = lextable.size;
				strcpy(ItEntr.id, words[stroke]);
				strcpy(ItEntr.scope, words[stroke]);
				LT::Add(lextable, LtEntr);
				IT::Add(idtable, ItEntr);
				NameOfFunc = words[stroke];
				ItEntr.iddatatype = IT::UNDEF;
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
				ItEntr.iddatatype = (CMP(words[stroke - 1], "stroke") ? IT::STR : IT::INT);
				ItEntr.idtype = IT::P;
				ItEntr.idxfirstLE = lextable.size;
				LtEntr.idxTI = idtable.size;
				LtEntr.lexema = LEX_ID;
				LtEntr.sn = sn;
				numberOfPar++;
				int col = /*strlen(NameOfFunc)*/ + strlen(words[stroke]);
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
				ItEntr.iddatatype = IT::UNDEF;
				continue;
			}
			FST::FST FSTDecl(words[stroke - 2], FST_NEW);
			FST::FST FSTSTR(words[stroke - 1], FST_STROKE);
			FST::FST FSTINT(words[stroke - 1], FST_NUMB);
			FST::FST FSTSYMB(words[stroke - 1], FST_SYMBOL);
			FST::FST FSTBOL(words[stroke - 1], FST_BOOLEAN);
			FST::FST FSTFunc(words[stroke], FST_FUNCTION);
			if (stroke >= 2 && FST::execute(FSTDecl) && (FST::execute(FSTSTR) || FST::execute(FSTINT) || FST::execute(FSTSYMB)||FST::execute(FSTBOL)) && !FST::execute(FSTFunc)) {//declare integer x;
				/*ItEntr.iddatatype = (CMP(words[stroke - 1], "stroke") ? IT::STR : IT::INT);*/
				if (CMP(words[stroke - 1], "stroke")) {
					ItEntr.iddatatype = IT::STR;
				}
				else if (CMP(words[stroke - 1], "numb")) {
					ItEntr.iddatatype = IT::INT;
				}
				else if (CMP(words[stroke - 1], "symbol")) {
					ItEntr.iddatatype = IT::CHAR;
				}
				else if (CMP(words[stroke - 1], "boolean")) {
					ItEntr.iddatatype = IT::BOOL;
				}
				ItEntr.idxfirstLE = lextable.size;
				LtEntr.lexema = LEX_ID;
				LtEntr.idxTI = idtable.size;
				LtEntr.sn = sn;
				int col =/* strlen(NameOfFunc)*/ +strlen(words[stroke]);
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
				/*FST::FST fstrl(words[stroke], FST_STRLEN);
				if (FST::execute(fstrl)) {
					buff = NameOfFunc;
					NameOfFunc = words[stroke];
					LtEntr.lexema = LEX_ID;
					ItEntr.idtype = IT::F;
				}*/
				/*else {*/
					ItEntr.idtype = IT::V;
				/*}*/
				LT::Add(lextable, LtEntr);
				IT::Add(idtable, ItEntr);
				ItEntr.iddatatype = IT::UNDEF;
				FST::FST fstEQ(words[++stroke], FST_EQUAL);
				int pos;
				if (FST::execute(fstEQ)) {
					LtEntr.idxTI = TI_NULLIDX;
					LtEntr.lexema = LEX_EQUAL;
					LtEntr.priority = 0;
					LtEntr.sn = sn;
					LT::Add(lextable, LtEntr);
					FST::FST FSTTR(words[stroke + 1], FST_TRUE);
					FST::FST FSTFAL(words[stroke + 1], FST_FALSE);
					FST::FST LSR(words[stroke + 1], FST_STRLIT);
 					FST::FST LIT(words[stroke + 1], FST_INTLIT);
					FST::FST LCHR(words[stroke + 1], FST_SYMBLIT);
 					if (FST::execute(LSR) || FST::execute(LIT)||FST::execute(LCHR)||FST::execute(FSTTR)||FST::execute(FSTFAL)) {
						stroke++;
						bool here = false;
						for (int i = 0; i < idtable.size; i++)
						{
							if (CMP(idtable.table[i].value.vstr.str, words[stroke])) {
								here = true;
								pos = i;
								break;
							}
						}
						if (!here) {
							char tem[99] = "-";
							bool minus = false;
							if (words[stroke][0] == '-') {
								stroke++;
								char buff[99];
								strcpy_s(buff, words[stroke]);
								strcat_s(tem, buff);
								minus = true;
							}
							LtEntr.lexema = LEX_LITERAL;
							LtEntr.sn = sn;
							LtEntr.idxTI = idtable.size;
							LT::Add(lextable, LtEntr);
							int symbols = strlen(words[stroke]);
							if (symbols > TI_STR_MAXSIZE)
								throw ERROR_THROW_IN(164, sn + 1, stroke + 1);				//добавить исключени

							ItEntr.idtype = IT::L;
							if (words[stroke][0] == '\'') {
								if (ItEntr.iddatatype = IT::STR) {
									strcpy_s(ItEntr.value.vstr.str, words[stroke]);
									ItEntr.value.vstr.len = strlen(words[stroke]);
								}

							}
							else if (words[stroke][0] == '\"') {
								if (ItEntr.iddatatype = IT::CHAR) {
									if (strlen(words[stroke]) - 2 > 1) {
										throw ERROR_THROW_IN(310, sn + 1, stroke + 1);
									}
									strcpy_s(ItEntr.value.vstr.str, words[stroke]);
									ItEntr.value.vstr.len = strlen(words[stroke]);
								}
							}
							else if (CMP(words[stroke], "false") || CMP(words[stroke], "true")) {
								if (ItEntr.iddatatype = IT::BOOL) {
									strcpy_s(ItEntr.value.vstr.str, words[stroke]);
									ItEntr.value.vstr.len = strlen(words[stroke]);
								}
							
							}
							else{
								ItEntr.iddatatype = IT::INT;
								if (!minus)
									ItEntr.value.vint = stoi(words[stroke]);
								else
									ItEntr.value.vint = stoi(tem);
							}

							ItEntr.idxfirstLE = lextable.size;

							char t[10];
							char lit[10] = "L";
							strcat(lit, itoa(LitNumber, t, 10));
							strcpy(ItEntr.id, lit);

							IT::Add(idtable, ItEntr);									//TODO
							ItEntr.iddatatype = IT::UNDEF;
							LitNumber++;
							stroke++;
						}
						else {
							IT::Entry e = IT::GetEntry(idtable, pos);
							LT::Entry e1 = LT::GetEntry(lextable, e.idxfirstLE-1);
							e1.sn = sn;
							LT::Add(lextable,e1);
							stroke++;
						}
					}
					
				}
				LtEntr.lexema = LEX_SEMICOLON;
				LtEntr.idxTI = TI_NULLIDX;
				LtEntr.priority = 0;
				LtEntr.sn = sn;
				LT::Add(lextable, LtEntr);
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
				FST::FST LSR(words[stroke], FST_STRLIT);
				FST::FST LIT(words[stroke], FST_INTLIT);
				FST::FST LCHR(words[stroke], FST_SYMBLIT);
				int pos1 = 0;
				if (FST::execute(LSR) || FST::execute(LIT) || FST::execute(LCHR)) {
					bool here = false;
					for (int i = 0; i < idtable.size; i++)
					{
						if (CMP(idtable.table[i].value.vstr.str, words[stroke])) {
							here = true;
							pos1 = i;
							break;
						}
					}
					if (!here) {
						char tem[99] = "-";
						bool minus = false;
						if (words[stroke][0] == '-') {
							stroke++;
							char buff[99];
							strcpy_s(buff, words[stroke]);
							strcat_s(tem, buff);
							minus = true;
						}
						LtEntr.lexema = LEX_LITERAL;
						LtEntr.sn = sn;
						LtEntr.idxTI = idtable.size;
						LT::Add(lextable, LtEntr);
						int symbols = strlen(words[stroke]);
						if (symbols > TI_STR_MAXSIZE)
							throw ERROR_THROW_IN(164, sn + 1, stroke + 1);				//добавить исключени

						ItEntr.idtype = IT::L;
						if (words[stroke][0] == '\'') {
							if (ItEntr.iddatatype = IT::STR) {
								strcpy_s(ItEntr.value.vstr.str, words[stroke]);
								ItEntr.value.vstr.len = strlen(words[stroke]);
							}

						}
						else if (words[stroke][0] == '\"') {
							if (ItEntr.iddatatype = IT::CHAR) {
								if (strlen(words[stroke]) - 2 > 1) {
									throw ERROR_THROW_IN(310, sn + 1, stroke + 1);
								}
								strcpy_s(ItEntr.value.vstr.str, words[stroke]);
								ItEntr.value.vstr.len = strlen(words[stroke]);
							}
						}
						else {
							ItEntr.iddatatype = IT::INT;
							if (!minus)
								ItEntr.value.vint = stoi(words[stroke]);
							else
								ItEntr.value.vint = stoi(tem);
						}

						ItEntr.idxfirstLE = lextable.size;

						char t[10];
						char lit[10] = "L";
						strcat(lit, itoa(LitNumber, t, 10));
						strcpy(ItEntr.id, lit);

						IT::Add(idtable, ItEntr);									//TODO
						ItEntr.iddatatype = IT::UNDEF;
						LitNumber++;
						stroke++;
					}
					else {
						IT::Entry e = IT::GetEntry(idtable, pos1);
						LT::Entry e1 = LT::GetEntry(lextable, e.idxfirstLE - 1);
						e1.sn = sn;
						LT::Add(lextable, e1);
						stroke++;
					}
					if (CMP(words[stroke], ";")) {
						LtEntr.lexema = LEX_SEMICOLON;
						LtEntr.idxTI = TI_NULLIDX;
						LtEntr.priority = 0;
						LtEntr.sn = sn;
						LT::Add(lextable, LtEntr);
						continue;
					}
				}
				/*//строка?
				FST::FST FSTSL(words[stroke], FST_STRLIT);
 				FST::FST FSTsymb(words[stroke], FST_SYMBLIT);
				if (FST::execute(FSTSL)||FST::execute(FSTsymb)) {
					LtEntr.lexema = LEX_LITERAL;
					LtEntr.sn = sn;
					LtEntr.idxTI = idtable.size;
					LT::Add(lextable, LtEntr);
					int symbols = strlen(words[stroke]);
					if (symbols > TI_STR_MAXSIZE)
						throw ERROR_THROW_IN(164, sn + 1, stroke + 1);				//добавить исключение 

					ItEntr.idtype = IT::L;
					if (words[stroke][0] == '\'')
						ItEntr.iddatatype = IT::STR;
					else {
						if (strlen(words[stroke])-2 > 1)
							throw ERROR_THROW_IN(310, sn + 1, stroke + 1);
						ItEntr.iddatatype = IT::CHAR;
					}
						

					ItEntr.idxfirstLE = lextable.size;
					ItEntr.value.vstr.len = strlen(words[stroke]);				
					char t[10];
					char lit[10] = "L";
					strcat(lit, itoa(LitNumber, t, 10));
					strcpy(ItEntr.id, lit);
					strcpy_s(ItEntr.value.vstr.str, words[stroke]);
					ItEntr.value.vstr.len = strlen(words[stroke]);
					IT::Add(idtable, ItEntr);									//TODO
					ItEntr.iddatatype = IT::UNDEF;
					LitNumber++;
					continue;
				}*/
				//цифра или функция;
				else {
					FST::FST FSN(words[stroke], FST_INTLIT);
					if (FST::execute(FSN)) {
						while (!CMP(words[stroke],";")) {
							FST::FST FSTPl1(words[stroke], FST_PLUS);
							if (FST::execute(FSTPl1)) {
								LtEntr.priority = 5;
								LtEntr.lexema = LEX_PLUS;
								LtEntr.sn = sn;
								LtEntr.idxTI = LT_TI_NULLIDX;
								LT::Add(lextable, LtEntr);
								stroke++;
								continue;
							}
							FST::FST FSTMin1(words[stroke], FST_MINUS);
							if (FST::execute(FSTMin1)) {
								LtEntr.priority = 5;
								LtEntr.lexema = LEX_MINUS;
								LtEntr.sn = sn;
								LtEntr.idxTI = LT_TI_NULLIDX;
								LT::Add(lextable, LtEntr);
								stroke++;
								continue;
							}
							FST::FST FSTSt1(words[stroke], FST_STAR);
							if (FST::execute(FSTSt1)) {
								LtEntr.priority = 4;
								LtEntr.lexema = LEX_STAR;
								LtEntr.sn = sn;
								LtEntr.idxTI = LT_TI_NULLIDX;
								LT::Add(lextable, LtEntr);
								stroke++;
								continue;
							}
							FST::FST FSTDS1(words[stroke], FST_DIRSLASH);
							if (FST::execute(FSTDS1)) {
								LtEntr.priority = 4;
								LtEntr.lexema = LEX_DIRSLASH;
								LtEntr.sn = sn;
								LtEntr.idxTI = TI_NULLIDX;
								LT::Add(lextable, LtEntr);
								stroke++;
								continue;
							}
							FST::FST FSN1(words[stroke], FST_INTLIT);
							if (FST::execute(FSN1)) {
								LtEntr.lexema = LEX_LITERAL;
								LtEntr.sn = sn;
								LtEntr.idxTI = idtable.size;
								LT::Add(lextable, LtEntr);
								ItEntr.iddatatype = IT::INT;
								ItEntr.idtype = IT::L;
								ItEntr.value.vint = stoi(words[stroke]);
								ItEntr.idxfirstLE = lextable.size;
								char t[10];
								char lit[10] = "L";
								strcat(lit, itoa(LitNumber, t, 10));
								strcpy(ItEntr.id, lit);
								LitNumber++;
								IT::Add(idtable, ItEntr);
								ItEntr.iddatatype = IT::UNDEF;
								stroke++;
								continue;
							}
						}
						LtEntr.lexema = LEX_SEMICOLON;
						LtEntr.sn = sn;
						LtEntr.idxTI = TI_NULLIDX;
						LT::Add(lextable, LtEntr);
						stroke++;
						sn++;
						continue;
						
						/*LtEntr.lexema = LEX_LITERAL;
						LtEntr.sn = sn;
						LtEntr.idxTI = idtable.size;
						LT::Add(lextable, LtEntr);
						ItEntr.iddatatype = IT::INT;
						ItEntr.idtype = IT::L;
						ItEntr.value.vint = stoi(words[stroke]);
						ItEntr.idxfirstLE = lextable.size;
						/*char temporary[10] = "LINT";
						char tmp[6];
						itoa(LitNumber, tmp, 10);
						strcat(temporary, tmp);
						strcpy(ItEntr.id, temporary);*/

						/*char t[10];
						char lit[10] = "L";
						strcat(lit, itoa(LitNumber, t, 10));
						strcpy(ItEntr.id, lit);
						LitNumber++;
						IT::Add(idtable, ItEntr);
						ItEntr.iddatatype = IT::UNDEF;
						continue;*/
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
								FST::FST FSTR(words[stroke], FST_REMAINDER);
								if (FST::execute(FSTR)) {
									LtEntr.priority = 4;
									LtEntr.lexema = LEX_REMAINDER;
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
									LtEntr.priority = 5;
									LtEntr.lexema = LEX_PLUS;
									LtEntr.sn = sn;
									LtEntr.idxTI = LT_TI_NULLIDX;
									LT::Add(lextable, LtEntr);
									stroke++;
									continue;
								}
								FST::FST FSTMin(words[stroke], FST_MINUS);
								if (FST::execute(FSTMin)) {
									LtEntr.priority = 5;
									LtEntr.lexema = LEX_MINUS;
									LtEntr.sn = sn;
									LtEntr.idxTI = LT_TI_NULLIDX;
									LT::Add(lextable, LtEntr);
									stroke++;
									continue;
								}
								FST::FST FSTSt(words[stroke], FST_STAR);
								if (FST::execute(FSTSt)) {
									LtEntr.priority = 4;
									LtEntr.lexema = LEX_STAR;
									LtEntr.sn = sn;
									LtEntr.idxTI = LT_TI_NULLIDX;
									LT::Add(lextable, LtEntr);
									stroke++;
									continue;
								}
								FST::FST FSTDS(words[stroke], FST_DIRSLASH);
								if (FST::execute(FSTDS)) {
									LtEntr.priority = 4;
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
				throw ERROR_THROW_IN(163, sn + 1, stroke + 1);
			}
		}

		if (!FindMain)
			ERROR_THROW(300);
		for (int j = 0; j < idtable.size; j++)
		{
			if (idtable.table[j].iddatatype == IT::UNDEF && (idtable.table[j].idtype == IT::V || idtable.table[j].idtype == IT::P || idtable.table[j].idtype == IT::F)) {
				throw ERROR_THROW_IN(307, lextable.table[idtable.table[j].idxfirstLE].sn, -1);
			}
		}

		LT::showTable(lextable);
		LT::WriteTable(lextable, out);
		IT::showTable(idtable);
		IT::WriteTable(idtable, out);
		tables.idtable = idtable;
		tables.lextable = lextable;
		return tables;
	}
}

