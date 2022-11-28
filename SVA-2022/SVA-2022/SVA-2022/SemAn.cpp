#include"stdafx.h"
namespace Semantic{
	bool semanticsCheck(Lex::Tables& tables, Log::LOG& log) {
		bool sem_ok = true;
		for (int i = 0; i < tables.lextable.size; i++)
		{
			switch (tables.lextable.table[i].lexema) {
				case LEX_NEW: {
					if (tables.lextable.table[i + 1].lexema != LEX_TYPE) {
						sem_ok = false;
						throw ERROR_THROW_IN(301, tables.lextable.table[i].sn, -1);
						break;
					}
				}
				case LEX_TYPE: {
					if (tables.lextable.table[i + 1].lexema == LEX_ID && tables.lextable.table[i - 1].lexema != LEX_NEW && tables.idtable.table[tables.lextable.table[i+1].idxTI].idtype != IT::P) {
						sem_ok = false;
						throw ERROR_THROW_IN(302, tables.lextable.table[i].sn, -1);
						break;
					}
				}
				case LEX_ID: {
					if (tables.lextable.table[i].lexema == LEX_FUNCTION) {
						IT::IDDATATYPE temp = tables.idtable.table[tables.lextable.table[i-1].idxTI].iddatatype;
						int j = i;
						while (tables.lextable.table[j].lexema != LEX_RETURN)
							j++;
						if (temp != tables.idtable.table[tables.lextable.table[i + 1].idxTI].iddatatype) {
							sem_ok = false;
							throw ERROR_THROW_IN(303, tables.lextable.table[i + 1].sn, -1);
							break;
						}
					}
				}
				case LEX_GREATER:
				case LEX_SMALLER:
				case LEX_GREATEROREQUAL:
				case LEX_SMALLEROREQUAL: {
					bool flag = true;
					if (i > 1 && tables.lextable.table[i - 1].idxTI != LT_TI_NULLIDX) {
						if (tables.idtable.table[tables.lextable.table[i - 1].idxTI].iddatatype != IT::INT) {
							flag = false;
						}
					}
					if (i > 1 && tables.lextable.table[i + 1].idxTI != LT_TI_NULLIDX) {
						if (tables.idtable.table[tables.lextable.table[i + 1].idxTI].iddatatype != IT::INT) {
							flag = false;
						}
					}
					if (!flag) {
						throw ERROR_THROW_IN(304, tables.lextable.table[i].sn, -1);
						sem_ok = false;
					}
					break;
				}
				/*case LEX_EQUAL: {
					IT::IDDATATYPE temp = tables.idtable.table[tables.lextable.table[i-1].idxTI].iddatatype;
					int j = i+1;
					while (tables.lextable.table[j].lexema!=LEX_SEMICOLON) {
						if (tables.lextable.table[j].lexema == LEX_LEFTHESIS) {
							while (tables.lextable.table[j].lexema != LEX_RIGHTHESIS)
								j++;
						}
						if (tables.lextable.table[j].lexema == LEX_ID || tables.lextable.table[j].lexema == LEX_LITERAL) {
							if (temp != tables.idtable.table[tables.lextable.table[j].idxTI].iddatatype) {
								sem_ok = false;
								throw ERROR_THROW_IN(305, tables.lextable.table[i].sn, i);
							}
						}
						j++;
					}
					break;
				}*/
				case LEX_DIRSLASH: {
					if (tables.idtable.table[tables.lextable.table[i].idxTI].value.vint == 0) {
						sem_ok = false;
						throw ERROR_THROW_IN(306, tables.lextable.table[i].sn, -1);
					}
					break;
				}


			}






		}
		return sem_ok;
	}	
}