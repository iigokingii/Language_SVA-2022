#include"stdafx.h"
#include<iomanip>
namespace LT {
	LexTable Create(int size) {
		LexTable* Table = new LexTable;
		if (size > LT_MAXSIZE)
			throw ERROR_THROW(120);
		Table->maxsize = size;
		Table->size = 0;
		Table->table = new Entry[size];

		return *Table;
	}

	void Add(LexTable& lextable, Entry entry) {
		if (lextable.size + 1 > lextable.maxsize)
			throw ERROR_THROW(121);
		lextable.table[lextable.size] = entry;
		lextable.size++;
	}

	Entry GetEntry(LexTable& lextable, int n) {
		return lextable.table[n];
	}

	void Delete(LexTable& lextable) {
		delete[] lextable.table;
	}
	void showTable(LexTable lextable)		// ����� ������� ������
	{
		cout << "--------------------------������� ������-----------------------" << endl;
		int stroke = 0;
		int From = 0;
		int To = 0;
		bool flag = false;
		cout << std::setfill('0') << std::setw(4) << std::right << stroke++ << " | ";

		char* arr = new char[TI_STR_MAXSIZE];
		for (int i = 0, j = 0; i < lextable.size; i++)
		{
			if (lextable.table[i].sn > lextable.table[i - 1].sn) {
				cout << std::setfill('0') << std::setw(4) << std::right << stroke++ << " | ";
			}
			if (lextable.table[i].lexema == LEX_SEMICOLON || lextable.table[i + 1].sn > lextable.table[i].sn)
			{
				arr[j] = lextable.table[i].lexema;
				flag = true;
			}
			else
				arr[j] = lextable.table[i].lexema;
			j++;
			if (flag) {
				arr[j] = '\0';
				cout << std::setw(20) << std::setfill(' ') << std::left << arr << " | " << setfill('0') << setw(3) << right << From << " - " << setfill('0') << setw(3) << right << To << endl;
				j = 0;
				From = To;
				flag = !flag;
			}
			To++;

		}
		cout << "---------------------------------------------------------------" << endl;
	}
	void WriteTable(LexTable lextable, Out::OUT out) {
		*out.stream << "\n--------------------------������� ������-----------------------" << endl;
		int stroke = 0;
		int From = 0;
		int To = 0;
		bool flag = false;
		*out.stream << std::setfill('0') << std::setw(4) << std::right << stroke++ << " | ";
		char* arr = new char[TI_STR_MAXSIZE];
		for (int i = 0, j = 0; i < lextable.size; i++)
		{
			if (lextable.table[i].sn > lextable.table[i - 1].sn) {
				*out.stream << std::setfill('0') << std::setw(4) << std::right << stroke++ << " | ";
			}
			if (lextable.table[i].lexema == LEX_SEMICOLON || lextable.table[i + 1].sn > lextable.table[i].sn)
			{
				arr[j] = lextable.table[i].lexema;
				flag = true;
			}
			else
				arr[j] = lextable.table[i].lexema;
			j++;
			if (flag) {
				arr[j] = '\0';
				*out.stream << std::setw(20) << std::setfill(' ') << std::left << arr << " | " << setfill('0') << setw(3) << right << From << " - " << setfill('0') << setw(3) << right << To << endl;
				j = 0;
				From = To;
				flag = !flag;
			}
			To++;

		}
		*out.stream << "---------------------------------------------------------------" << endl;
	}


}