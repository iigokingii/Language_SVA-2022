#include"stdafx.h"
#include<map>
#include<queue>
#pragma warning(disable: 4996)
namespace PN {
	bool PolishStart(Lex::Tables& table) {
		bool result;
		for (int i = 0; i < table.lextable.size; i++)
		{
			if (table.lextable.table[i].lexema == '=' || table.idtable.table[table.lextable.table[i].idxTI].idtype == IT::F && table.lextable.table[i - 1].lexema == LEX_PRINT) {
				result=PolishNotation(i + 1, table);
			}
		}
		return result;
	}

	bool PolishNotation(int i, Lex::Tables& table) {
		LT::LexTable lex = table.lextable;
		stack<LT::Entry> st;
		queue<LT::Entry> q;
		LT::Entry temp;
		temp.lexema = ' ';
		temp.sn = -1;
		temp.idxTI = -1;
		LT::Entry func;
		func.lexema = '@';
		int countOfLex = 0;
		int position = i;
		bool funcFlag = false;
		int param = 0;
		int hesises = 0;
		int comma = 0;
		for (i; lex.table[i-1].lexema != LEX_SEMICOLON; i++, countOfLex++)
		{
			switch (lex.table[i].lexema)
			{
			case LEX_ID: {				//i
				if (funcFlag) {
					param++;
					q.push(lex.table[i]);
				}
				else if (table.idtable.table[lex.table[i].idxTI].idtype != IT::F) {
					q.push(lex.table[i]);
				}
				else if (table.lextable.table[i - 2].lexema == LEX_PRINT) {
					countOfLex += 2;//так как начинаем с лексемы +2;
					position -= 2;
					q.push(lex.table[i - 2]);
				}
				continue;
			}

			case LEX_LITERAL: {			//l
				if (funcFlag) {
					param++;
					q.push(lex.table[i]);
				}
				else if (table.idtable.table[lex.table[i].idxTI].idtype != IT::F) {
					q.push(lex.table[i]);
				}
				else if (table.lextable.table[i - 2].lexema == LEX_PRINT) {
					countOfLex += 2;//так как начинаем с лексемы +2;
					position -= 2;
					q.push(lex.table[i - 2]);
				}
				continue;
			}
			case LEX_COMMA: {			//,
				comma++;
				continue;
			}
			case LEX_LEFTHESIS: {		//(
				hesises++;
				if (lex.table[i - 1].lexema == LEX_ID) {
					if (table.idtable.table[lex.table[i - 1].idxTI].idtype == IT::F) {
						funcFlag = true;
					}
				}
				if (funcFlag) {
					func.idxTI = lex.table[i - 1].idxTI;
					func.sn = lex.table[i - 1].sn;

				}
				else
					st.push(lex.table[i]);
				if (lex.table[i - 2].lexema == LEX_PRINT) {
					countOfLex += 2;//так как начинаем с лексемы +2;
					position -= 2;
					q.push(lex.table[i - 2]);
					continue;
				}
				continue;
			}
			case LEX_RIGHTHESIS: {		//)
				hesises++;
				if (funcFlag) {
					q.push(func);
					char buf[10];
					itoa(comma + 1, buf, 10);
					func.lexema = buf[0];
					q.push(func);
					funcFlag = false;
				}

				else {
					while (st.top().lexema != LEX_LEFTHESIS) {			//пока не дойдем до (
						q.push(st.top());
						st.pop();
						if (st.empty())
							return false;
					}
					st.pop();										//удаление (
				}
				continue;
			}
			case LEX_PLUS:				//+-*/
			case LEX_MINUS:
			case LEX_DIRSLASH:
			case LEX_STAR: {
				while (!st.empty() && lex.table[i].priority <= st.top().priority)	//пока приоритет текущего операторатора меньше или равен и стек не пуст;
				{
					q.push(st.top());
					st.pop();
				}
				st.push(lex.table[i]);
				continue;
			}
			case LEX_SEMICOLON: {
				temp.lexema = lex.table[i].lexema;
				temp.sn = lex.table[i].sn;
				temp.idxTI = TI_NULLIDX;
				continue;
			}
			}
		}
		while (!st.empty()) {
			if (st.top().lexema == LEX_LEFTHESIS || st.top().lexema == LEX_RIGHTHESIS)
				return false;
			q.push(st.top());
			st.pop();
		}
		q.push(temp);
		int size = q.size();
		int t = countOfLex - size;			//количество игнорированных лексем
		while (countOfLex != 0) {
			if (!q.empty()) {
				lex.table[position++] = q.front();
				q.pop();
			}
			else {
				countOfLex--;
			}
		}
		for (int i = 0; i < position; i++)	// восстановление индексов первого вхождения в таблицу лексем у операторов из таблицы идентификаторов
		{
			if (lex.table[i].lexema == LEX_PLUS || lex.table[i].lexema == LEX_MINUS || lex.table[i].lexema == LEX_STAR || lex.table[i].lexema == LEX_DIRSLASH||lex.table[i].lexema==LEX_LITERAL) {
				table.idtable.table[lex.table[i].idxTI].idxfirstLE = i;
			}
		}
		for (int i = position + t; i < table.lextable.size; i++)
		{
			lex.table[position++] = lex.table[i];
		}
		lex.size = lex.size - t;
		table.lextable = lex;
		return true;
	}
}
