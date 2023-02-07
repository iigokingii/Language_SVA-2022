#include"stdafx.h"
#pragma warning(disable: 4996)
namespace Semantic {
	bool semanticsCheck(Lex::Tables& tables, Log::LOG& log) {
		bool sem_ok = true;
		char temp [7];
		IT::Entry e;
		for (int i = 0; i <tables.idtable.size; i++)
		{
			e=tables.idtable.table[i];
			for (int  j = 0; j < tables.idtable.size; j++)
			{
				if(j!=i)
				if (Lex::CMP(e.id, tables.idtable.table[j].id) && tables.idtable.table[j].idtype!=IT::F && Lex::CMP(e.scope,tables.idtable.table[j].scope)) {
					sem_ok = false;
					throw ERROR_THROW_IN(311, tables.lextable.table[tables.idtable.table[j].idxfirstLE].sn+1, e.idxfirstLE+1);
				}
			}
		}
		for (int i = 0; i < tables.lextable.size; i++)
		{
			switch (tables.lextable.table[i].lexema) {
				case LEX_NEW: {
					if (tables.lextable.table[i + 1].lexema != LEX_TYPE) {
						sem_ok = false;
						throw ERROR_THROW_IN(301, tables.lextable.table[i].sn, -1);
					}
					break;
				}
				case LEX_TYPE: {
					if (tables.lextable.table[i + 1].lexema == LEX_ID && tables.lextable.table[i - 1].lexema != LEX_NEW && tables.idtable.table[tables.lextable.table[i + 1].idxTI].idtype != IT::P) {
						sem_ok = false;
						throw ERROR_THROW_IN(302, tables.lextable.table[i].sn, -1);
					}
					break;
				}
				case LEX_ID: {
					if (tables.lextable.table[i-1].lexema == LEX_FUNCTION) {
						IT::IDDATATYPE temp = tables.idtable.table[tables.lextable.table[i].idxTI].iddatatype;
						int j = i;
						while (tables.lextable.table[j].lexema != LEX_RETURN)
							j++;
						if (temp != tables.idtable.table[tables.lextable.table[j+1].idxTI].iddatatype) {
							sem_ok = false;
							throw ERROR_THROW_IN(303, tables.lextable.table[j].sn, j);
						}
					}
					break;
				}
				case LEX_GREATER:
				case LEX_SMALLER:
				case LEX_GREATEROREQUAL:
				case LEX_SMALLEROREQUAL: {
					int pos = 0;
					bool flag = true;
					if (i > 1 && tables.lextable.table[i - 1].idxTI != LT_TI_NULLIDX) {
						if (tables.idtable.table[tables.lextable.table[i - 1].idxTI].iddatatype != IT::INT) {
							pos = tables.idtable.table[tables.lextable.table[i - 1].idxTI].idxfirstLE;
							flag = false;
						}
					}
					if (i > 1 && tables.lextable.table[i + 1].idxTI != LT_TI_NULLIDX) {
						if (tables.idtable.table[tables.lextable.table[i + 1].idxTI].iddatatype != IT::INT) {
							pos = tables.idtable.table[tables.lextable.table[i + 1].idxTI].idxfirstLE;
							flag = false;
						}
					}
					if (!flag) {
						throw ERROR_THROW_IN(304, tables.lextable.table[i].sn, pos);
						sem_ok = false;
					}
					break;
				}
				case LEX_EQUAL: {
					IT::IDDATATYPE temp = tables.idtable.table[tables.lextable.table[i - 1].idxTI].iddatatype;
					int j = i + 1;
					while (tables.lextable.table[j].lexema != LEX_SEMICOLON) {
						if (tables.lextable.table[j].lexema == LEX_LEFTHESIS) {
							while (tables.lextable.table[j].lexema != LEX_RIGHTHESIS)
								j++;
						}
						if ((tables.lextable.table[j].lexema == LEX_ID || tables.lextable.table[j].lexema == LEX_LITERAL)
							&&
							(tables.lextable.table[j].lexema!=LEX_STRLEN|| tables.lextable.table[j].lexema!=LEX_RAND || tables.lextable.table[j].lexema!=LEX_INPUT)){
							if (tables.lextable.table[i - 1].idxTI == TI_NULLIDX) {
								sem_ok = false;
								throw ERROR_THROW_IN(307,tables.lextable.table[i - 1].sn+1,i-1);
							}
							else if (tables.lextable.table[j].idxTI==TI_NULLIDX) {
								sem_ok = false;
								throw ERROR_THROW_IN(307, tables.lextable.table[j].sn + 1, j-1);
							}
							else if (temp != tables.idtable.table[tables.lextable.table[j].idxTI].iddatatype) {
								sem_ok = false;
								throw ERROR_THROW_IN(305, tables.lextable.table[i].sn+1, i-1);
							}
						}
						j++;
					}
					break;
				}
				case LEX_DIRSLASH: {
					if (tables.idtable.table[tables.lextable.table[i].idxTI].value.vint == 0) {
						sem_ok = false;
						throw ERROR_THROW_IN(306, tables.lextable.table[i].sn, -1);
					}
					break;
				}
				case LEX_REMAINDER: {
					IT::IDDATATYPE temp1 = tables.idtable.table[tables.lextable.table[i - 1].idxTI].iddatatype;
					IT::IDDATATYPE temp2 = tables.idtable.table[tables.lextable.table[i + 1].idxTI].iddatatype;
					if (temp1 == IT::STR || temp1 == IT::CHAR || temp2 == IT::STR || temp2 == IT::CHAR || temp2 == IT::BOOL || temp2 == IT::BOOL) {
						sem_ok = false;
						throw ERROR_THROW(313);
					}
					break;
				}
				
				case LEX_STRLEN: {
					IT::Entry e = tables.idtable.table[tables.lextable.table[i + 2].idxTI];
					int p = tables.lextable.table[i + 2].idxTI;
					LT::Entry e1 = tables.lextable.table[i];
					if (p == TI_NULLIDX) {
						throw ERROR_THROW_IN(314, e1.sn+1, i+1);
					}
					else if (e.iddatatype == IT::BOOL) {
						throw ERROR_THROW_IN(315, e1.sn+1, i+1);
					}
					else if (e.iddatatype == IT::INT) {
						throw ERROR_THROW_IN(315, e1.sn+1, i+1);
					}
					else if (tables.idtable.table[tables.lextable.table[i - 2].idxTI].iddatatype != IT::INT) {
						throw ERROR_THROW_IN(303, tables.lextable.table[i - 2].sn, i - 1);
					}
					break;
				}
				case LEX_RAND: {
					IT::Entry e = tables.idtable.table[tables.lextable.table[i + 2].idxTI];
					if (e.iddatatype != IT::INT)
						throw ERROR_THROW_IN(312,tables.lextable.table[i].sn+1,i+1);
					break;
				}
			}
		}
		return sem_ok;
	}
}