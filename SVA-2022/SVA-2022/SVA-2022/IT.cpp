#include"stdafx.h"
#include<iomanip>

namespace IT {
	IdTable Create(int size) {
		IdTable* tabl = new IdTable;
		if (size > TI_MAXSIZE)
			throw ERROR_THROW(160);
		tabl->maxsize = size;
		tabl->size = 0;
		tabl->table = new Entry[size];
		return*tabl;
	}

	void Add(IdTable& idtable, Entry entry) {
		if (idtable.size + 1 > idtable.maxsize)
			throw ERROR_THROW(161);
		idtable.table[idtable.size] = entry;
		idtable.size++;
	}
	Entry GetEntry(IdTable& idtable, int n) {
		return idtable.table[n];
	}
	int IsId(IdTable& idtable, char id[ID_MAXSIZE]) {
		for (int i = 0; i < idtable.size; i++)
		{
			if (strcmp(idtable.table[i].id, id) == 0)
				return i;
		}
		return LT_TI_NULLIDX;
	}
	void Delete(IdTable& idtable) {
		delete[] idtable.table;
	}
	void showTable(IdTable& idtable) {
		cout << std::setfill('-') << std::setw(107) << '-' << std::endl;
		cout << "   №" << " | " << setfill(' ') << setw(10) << left << "Scope" << " | " << "Идентификатор" << " | " << "Тип данных" << " | " << "Тип идентификатора" << " | " << "Индекс в ТЛ" << " | " << "Значение    " << std::endl;
		cout << setfill('-') << std::setw(107) << '-' << std::endl;
		for (int i = 0, j = 0; i < idtable.size; i++, j++)
		{

			cout << std::setfill('0') << std::setw(4) << std::right << j << " | ";
			if (!Lex::CMP(idtable.table[i-1].scope ,idtable.table[i].scope))
				cout << std::setfill(' ') << setw(10) << left << idtable.table[i].scope << " | ";
			else {
				cout << std::setfill(' ') << setw(13) << right << " | ";
			}
			cout << std::setfill(' ') << std::setw(13) << std::left << idtable.table[i].id << " | ";

			switch (idtable.table[i].iddatatype)
			{
			case INT: cout << std::setw(10) << std::left;
				cout << "integer" << " | "; break;
			case STR: cout << std::setw(10) << std::left;
				cout << "string" << " | "; break;
			default: cout << std::setw(10) << std::left << "unknown" << " | "; break;
			}
			switch (idtable.table[i].idtype)
			{
			case V: cout << std::setw(18) << std::left << "переменная" << " | "; break;
			case F: cout << std::setw(18) << std::left << "функция" << " | "; break;
			case P: cout << std::setw(18) << std::left << "параметр" << " | "; break;
			case L: cout << std::setw(18) << std::left << "литерал" << " | "; break;
			default: cout << std::setw(18) << std::left << "unknown" << " | "; break;
			}
			cout << std::setw(11) << std::left << idtable.table[i].idxfirstLE << " | ";
			if (idtable.table[i].iddatatype == INT && idtable.table[i].idtype != IT::F)
				cout << std::setw(18) << std::left << idtable.table[i].value.vint;
			else if (idtable.table[i].iddatatype == STR && idtable.table[i].idtype != IT::F) {
				if (idtable.table[i].value.vstr.str[0] != '\'')
					cout << "\"" << idtable.table[i].value.vstr.str << "\"";
				else
					cout << idtable.table[i].value.vstr.str;
			}
			else
				cout << "-";
			cout << std::endl;
		}
		cout << std::setfill('-') << std::setw(107) << '-' << std::endl;
	}
	void WriteTable(IdTable& idtable, Out::OUT out) {
		*out.stream << std::setfill('-') << std::setw(87) << '-' << std::endl;
		*out.stream << "   №" << " | " << setfill(' ') << setw(10) << left << "Scope" << " | " << "Идентификатор" << " | " << "Тип данных" << " | " << "Тип идентификатора" << " | " << "Индекс в ТЛ" << " | " << "Значение    " << std::endl;
		*out.stream << std::setw(87) << '-' << std::endl;
		*out.stream << endl;
		for (int i = 0, j = 0; i < idtable.size; i++, j++)
		{
			*out.stream << std::setfill('0') << std::setw(4) << std::right << j << " | ";
			if (idtable.table[i].scope != idtable.table[i + 1].scope)
				*out.stream << std::setfill(' ') << setw(10) << left << idtable.table[i].scope << " | ";
			*out.stream << std::setfill(' ') << std::setw(13) << std::left << idtable.table[i].id << " | ";
			switch (idtable.table[i].iddatatype)
			{
			case INT: *out.stream << std::setw(10) << std::left;
				*out.stream << "integer" << " | "; break;
			case STR: *out.stream << std::setw(10) << std::left;
				*out.stream << "string" << " | "; break;
			default: *out.stream << std::setw(10) << std::left << "unknown" << " | "; break;
			}
			switch (idtable.table[i].idtype)
			{
			case V: *out.stream << std::setw(18) << std::left << "переменная" << " | "; break;
			case F: *out.stream << std::setw(18) << std::left << "функция" << " | "; break;
			case P: *out.stream << std::setw(18) << std::left << "параметр" << " | "; break;
			case L: *out.stream << std::setw(18) << std::left << "литерал" << " | "; break;
			default: *out.stream << std::setw(18) << std::left << "unknown" << " | "; break;
			}
			*out.stream << std::setw(11) << std::left << idtable.table[i].idxfirstLE << " | ";
			if (idtable.table[i].iddatatype == INT && idtable.table[i].idtype != IT::F)
				*out.stream << std::setw(18) << std::left << idtable.table[i].value.vint;
			else if (idtable.table[i].iddatatype == STR && idtable.table[i].idtype != IT::F) {
				if (idtable.table[i].value.vstr.str[0] != '\'')
					*out.stream << "\"" << idtable.table[i].value.vstr.str << "\"";
				else
					*out.stream << idtable.table[i].value.vstr.str;
			}
			else
				*out.stream << "-";
			*out.stream << std::endl;
		}
		*out.stream << std::setfill('-') << std::setw(87) << '-' << std::endl;
	}



}
