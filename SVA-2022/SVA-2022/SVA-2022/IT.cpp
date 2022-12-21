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
		cout << "   �" << " | " << setfill(' ') << setw(10) << left << "Scope" << " | " << "�������������" << " | " << "��� ������" << " | " << "��� ��������������" << " | " << "������ � ��" << " | " << "��������    " << std::endl;
		cout << setfill('-') << std::setw(107) << '-' << std::endl;
		for (int i = 0, j = 0; i < idtable.size; i++, j++)
		{

			cout << std::setfill('0') << std::setw(4) << std::right << j << " | ";
			cout << std::setfill(' ') << setw(10) << left << idtable.table[i].scope << " | ";
			cout << std::setfill(' ') << std::setw(13) << std::left << idtable.table[i].id << " | ";

			switch (idtable.table[i].iddatatype)
			{
			case INT: cout << std::setw(10) << std::left;
				cout << "integer" << " | "; break;
			case STR: cout << std::setw(10) << std::left;
				cout << "string" << " | "; break;
			case CHAR: cout << setw(10) << left;
				cout << "Char" << " | "; break;
			case BOOL:cout << setw(10) << left;
				cout << "Boolean" << " | "; break;
			default: cout << std::setw(10) << std::left << "unknown" << " | "; break;
			}
			switch (idtable.table[i].idtype)
			{
			case V: cout << std::setw(18) << std::left << "����������" << " | "; break;
			case F: cout << std::setw(18) << std::left << "�������" << " | "; break;
			case P: cout << std::setw(18) << std::left << "��������" << " | "; break;
			case L: cout << std::setw(18) << std::left << "�������" << " | "; break;
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
			else if (idtable.table[i].iddatatype == CHAR && idtable.table[i].idtype != IT::F) {
				if (idtable.table[i].value.vstr.str[0] != '\"')
					cout << "\"" << idtable.table[i].value.vstr.str << "\"";
				else
					cout << idtable.table[i].value.vstr.str;
			}
			else if (idtable.table[i].iddatatype == BOOL && idtable.table[i].idtype != IT::F) {
				if (idtable.table[i].value.vstr.str[0] == 'f' || idtable.table[i].value.vstr.str[0] == 't')
					cout << idtable.table[i].value.vstr.str;
				else
					cout << '-';
			}
			else
				cout << "-";
			cout << std::endl;
		}
		cout << std::setfill('-') << std::setw(107) << '-' << std::endl;
	}
	void WriteTable(IdTable& idtable, wchar_t*name) {
		ofstream fout;
		fout.open(name);
		
		fout << std::setfill('-') << std::setw(107) << '-' << std::endl;
		fout << "   �" << " | " << setfill(' ') << setw(10) << left << "Scope" << " | " << "�������������" << " | " << "��� ������" << " | " << "��� ��������������" << " | " << "������ � ��" << " | " << "��������    " << std::endl;
		fout << setfill('-') << std::setw(107) << '-' << std::endl;
		for (int i = 0, j = 0; i < idtable.size; i++, j++)
		{

			fout << std::setfill('0') << std::setw(4) << std::right << j << " | ";
			fout << std::setfill(' ') << setw(10) << left << idtable.table[i].scope << " | ";
			fout << std::setfill(' ') << std::setw(13) << std::left << idtable.table[i].id << " | ";

			switch (idtable.table[i].iddatatype)
			{
			case INT: fout << std::setw(10) << std::left;
				fout << "integer" << " | "; break;
			case STR: fout << std::setw(10) << std::left;
				fout << "string" << " | "; break;
			case CHAR: fout << setw(10) << left;
				fout << "Char" << " | "; break;
			case BOOL:fout << setw(10) << left;
				fout << "Boolean" << " | "; break;
			default: fout << std::setw(10) << std::left << "unknown" << " | "; break;
			}
			switch (idtable.table[i].idtype)
			{
			case V: fout << std::setw(18) << std::left << "����������" << " | "; break;
			case F: fout << std::setw(18) << std::left << "�������" << " | "; break;
			case P: fout << std::setw(18) << std::left << "��������" << " | "; break;
			case L: fout << std::setw(18) << std::left << "�������" << " | "; break;
			default: fout << std::setw(18) << std::left << "unknown" << " | "; break;
			}
			fout << std::setw(11) << std::left << idtable.table[i].idxfirstLE << " | ";
			if (idtable.table[i].iddatatype == INT && idtable.table[i].idtype != IT::F)
				fout << std::setw(18) << std::left << idtable.table[i].value.vint;
			else if (idtable.table[i].iddatatype == STR && idtable.table[i].idtype != IT::F) {
				if (idtable.table[i].value.vstr.str[0] != '\'')
					fout << "\"" << idtable.table[i].value.vstr.str << "\"";
				else
					fout << idtable.table[i].value.vstr.str;
			}
			else if (idtable.table[i].iddatatype == CHAR && idtable.table[i].idtype != IT::F) {
				if (idtable.table[i].value.vstr.str[0] != '\"')
					fout << "\"" << idtable.table[i].value.vstr.str << "\"";
				else
					fout << idtable.table[i].value.vstr.str;
			}
			else if (idtable.table[i].iddatatype == BOOL && idtable.table[i].idtype != IT::F) {
				if (idtable.table[i].value.vstr.str[0] == 'f' || idtable.table[i].value.vstr.str[0] == 't')
					fout << idtable.table[i].value.vstr.str;
				else
					fout << '-';
			}
			else
				fout << "-";
			fout << std::endl;
		}
		fout << std::setfill('-') << std::setw(107) << '-' << std::endl;
		fout.close();
	}



}
