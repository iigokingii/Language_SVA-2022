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
		string str = "\t\t" +string(temp.scope)+ string(temp.id);
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
		if (tables.idtable.table[i].idtype == IT::IDTYPE::V) {
			IT::Entry temp = tables.idtable.table[i];
			string str = "\t\t" + string(temp.scope)+string(temp.id);
			switch (temp.iddatatype)
			{
			case IT::IDDATATYPE::INT: str = str + " sdword 0";  break;				//Если целочисл
			case IT::IDDATATYPE::STR: str = str + " dword ?";  break;				//Если строка
			}
			vData.push_back(str);
		}

	}
	v.insert(v.end(), vConst.begin(), vConst.end());
	v.insert(v.end(), vData.begin(), vData.end());
	v.push_back(CODE);
}

string footer(Lex::Tables& tables, int i, string funcName, int numOfPar) {
	

	
	
	return "";
}

string genFunction(Lex::Tables&tables,int i ,string name,int param) {
	string temp="";
	IT::Entry e = IT_ENTRY(i);
	IT::IDDATATYPE type = e.iddatatype;

	temp = temp + FUNCTION_NAME(name) + string(e.id) + string("PROC,\n\t");
	//int number = atoi((char*)tables.lextable.table[i + 1].lexema);
	/*for (int i = 0; i < number; i++) {

	}*/
	return temp;
}







namespace Generator {
	void CodeGeneration(Lex::Tables& tables) {
		vector<string> v;
		header(tables, v);
		string buff="";	//буфер для строк
		string buffForFuncName="";	//буфер для имени функции
		int numberOfParam;
		for (int i = 0; i < tables.idtable.size; i++) {
			switch (LEXEMA(i))
			{
				case LEX_MAIN:{
					buff = buff + FUNCTION_NAME("MAIN") + "main PROC";
					break;
				}
				case LEX_FUNCTION:
				{
					buffForFuncName = IT_ENTRY(i + 1).id;
					numberOfParam= tables.idtable.table[tables.lextable.table[i + 1].idxTI].numberOfParam;
					buff = genFunction(tables, i+1, buffForFuncName, numberOfParam);
					break;
				}
				case '@': {

				}
				case LEX_RETURN: {
					//str = footer(tables, i, buffForFuncName, numberOfParam);
				}


			}
			if (!buff.empty()) {
				v.push_back(buff);
			}
			buff.clear();




		}
		v.push_back(END);



	}
}