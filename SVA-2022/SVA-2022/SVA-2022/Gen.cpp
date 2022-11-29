#include"Gen.h"
#include<string>
#include<string.h>
void header(Lex::Tables& tables, vector<string>& v) {
	v.push_back(BEGIN);
	v.push_back(EXTRN);
	vector <string> vConst;
	vector <string> vData;
	vConst.push_back(CONST);
	vData.push_back(DATA);
	for (int i = 0; i < tables.idtable.size; i++)
	{
		IT::Entry temp = tables.idtable.table[i];
		string str = "\t\t" + string(temp.id);
		if (tables.idtable.table[i].idtype == IT::IDTYPE::L) {
			switch (temp.iddatatype)
			{
			case IT::IDDATATYPE::INT: {
				str = str + " SDWORD " + to_string(temp.value.vint);
				break;
			}
			case IT::IDDATATYPE::STR: {
				str = str + " byte '" + string(temp.value.vstr.str) + "', 0";
				break;
			}
			}
			vConst.push_back(str);
		}
		if (tables.idtable.table[i].iddatatype == IT::IDTYPE::V) {
			IT::Entry temp = tables.idtable.table[i];
			string str = "\t\t" + string(temp.id);
			switch (temp.iddatatype)
			{
			case IT::IDDATATYPE::INT: {
				str = str + " SDWORD " + to_string(temp.value.vint);
				break;
			}
			case IT::IDDATATYPE::STR: {
				str = str + " byte '" + string(temp.value.vstr.str) + "', 0";
				break;
			}
			}
			vData.push_back(str);
		}

	}
	v.insert(v.end(), vConst.begin(), vConst.end());
	v.insert(v.end(), vData.begin(), vData.end());
	v.push_back(CODE);
}


namespace Generator {
	void CodeGeneration(Lex::Tables& tables) {
		vector<string> v;
		header(tables, v);








	}
}