#include"Gen.h"
#include<string>
#include<string.h>
static int counterOfStates = 0;
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
		string str = "\t\t" +/*string(temp.scope)+*/ string(temp.id);
		if (tables.idtable.table[i].idtype == IT::IDTYPE::L) {
			switch (temp.iddatatype)
			{
				case IT::IDDATATYPE::INT: {
					str = str + " SDWORD " + to_string(temp.value.vint);
					break;
				}
				case IT::IDDATATYPE::STR: {
					str = str + " byte " + string(temp.value.vstr.str) + ", 0";
					break;
				}
				case IT::IDDATATYPE::CHAR: {
					str = str + " byte " + string(temp.value.vstr.str) + ", 0";
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
				case IT::IDDATATYPE::CHAR:str = str + " dword ?"; break;				//Если символ
			}
			vData.push_back(str);
		}

	}
	v.insert(v.end(), vConst.begin(), vConst.end());
	v.insert(v.end(), vData.begin(), vData.end());
	v.push_back(CODE);
}

string footerOfFunc(Lex::Tables& tables, int i, string funcName, int numOfPar) {
	string temp = "\npop ebx\npop edx\n";
	if (LEXEMA(i + 1) != LEX_SEMICOLON)
		temp = temp + "mov eax, " + string(IT_ENTRY(i + 1).scope) + string(IT_ENTRY(i + 1).id) + "\n";
	temp += "ret\n";
	temp += funcName+" ENDP"+STR_SEPARATOR;
	return temp;
}

string headerOfFunc(Lex::Tables&tables,int i ,string name,int param) {	
	string temp="";
	IT::Entry e = IT_ENTRY(i);
	IT::IDDATATYPE type = e.iddatatype;

	temp = temp + FUNCTION_NAME(name) + string(e.id) + string(" PROC,\n\t");
	int number = e.numberOfParam;
	int j = i + 3;	//tfi(ti,ti) для того чтобы начать с і;
	while (number > 0) {
		temp = temp + string(IT_ENTRY(j).scope) + string(IT_ENTRY(j).id) +(IT_ENTRY(j).iddatatype == IT::INT ? " : sdword, " : " : dword, ");
		number--;
		j += 3;
	}
	int f = temp.rfind(',');
	if (f > 0)
		temp[f] = ' ';
	temp += "\npush ebx\npush edx\n";
	return temp;
}

string callFunc(Lex::Tables& tables, int pos) {	//Подготовка и вызов функции
	string str="";
	IT::Entry e = IT_ENTRY(pos+3);
	stack<IT::Entry> st;
	for (int j = pos; LEXEMA(j) != '@'; j++) {
		if (LEXEMA(j) == LEX_ID || LEXEMA(j) == LEX_LITERAL)
			st.push(IT_ENTRY(j));
	}
	while (!st.empty()) {
		if (st.top().iddatatype == (IT::IDDATATYPE::STR||IT::IDDATATYPE::CHAR)&& st.top().idtype == IT::L) {
			str = str + "push offset " /*+st.top().scope*/+st.top().id + "\n";
		}
		 else {
			str= str + "push " +st.top().scope+ st.top().id + "\n";//заполнение строки литералами
		 }
		 
		st.pop();
	}
	str = str + "call " + string(e.id) + IN_COD_ENDL;
	return str;
}

string genStateCode(Lex::Tables& tables, int i, string& cyclecode) {
	string str;
	counterOfStates++;
	cyclecode.clear();
	IT::Entry left = IT_ENTRY(i + 2);	//левый операнд
	IT::Entry right = IT_ENTRY(i + 4);	//правый операнд
	bool correctly=false, wrong = false;
	string correctlyStroke, WrongStroke;
	for (int j = i+6; LEXEMA(j)!=LEX_DOL ; j++)	//для того чтобы начать с первого символоа в $ $
	{
		if (LEXEMA(j) == LEX_CORRECTLY)
			correctly = true;
		if (LEXEMA(j) == LEX_WRONG)
			wrong = true;
	}
	str = str + "mov edx, " + left.scope + left.id + "\ncmp edx, " + right.scope + right.id + "\n";
	switch (LEXEMA(i+3))
	{
		case LEX_GREATER: {
			correctlyStroke = "jg";
			WrongStroke = "jl";
			break;
		}
		case LEX_SMALLER: {
			correctlyStroke = "jl";
			WrongStroke = "jg";
			break;
		}
		case LEX_GREATEROREQUAL: {
			correctlyStroke = "jae";
			WrongStroke = "jbe";
			break;
		}
		case LEX_SMALLEROREQUAL: {
			correctlyStroke = "jbe";
			WrongStroke = "jae";
			break;
		}
	}
	if (correctly) {
		str = str + "\n" + correctlyStroke + " right" + to_string(counterOfStates);
	}
	if (wrong) {
		str = str + "\n" + WrongStroke + " wrong" + to_string(counterOfStates);
	}
	else if (!correctly || !wrong)  str = str + "\njmp next" + to_string(counterOfStates);

	return str;
}


string generateEqual(Lex::Tables&tables,int pos) {
	string str;
	IT::Entry e = IT_ENTRY(pos - 1);	//левый операнд в выражении;
	switch (e.iddatatype) {
		case IT::INT: {
			for (int j = pos+1; LEXEMA(j)!=LEX_SEMICOLON; j++)	//начиная с первого правого операнда
			{
				switch (LEXEMA(j))
				{
					case LEX_LITERAL: {
						str = str + "push " /*+ IT_ENTRY(j).scope */+ IT_ENTRY(j).id + "\n";
						break;
					}
					case LEX_ID: {
						if (IT_ENTRY(j).iddatatype == IT::F) {
							str = str + callFunc(tables, j);
							str = str + "push eax\n";
							while (LEXEMA(j) != LEX_RIGHTHESIS)
								j++;
							break;
						}
						else {
							str = str + "push " +IT_ENTRY(j).scope+IT_ENTRY(j).id + "\n";
						}
						break;
					}
					case LEX_PLUS:
						str = str + "pop ebx\npop eax\nadd eax, ebx\npush eax\n"; break;
					case LEX_MINUS:
						str = str + "pop ebx\npop eax\nsub eax, ebx\npush eax\n"; break;
					case LEX_STAR:
						str = str + "pop ebx\npop eax\nimul eax, ebx\npush eax\n"; break;
					case LEX_DIRSLASH:
						str = str + "pop ebx\npop eax\ncdq\nidiv ebx\npush eax\n"; break;
				}
			}	//цикл для вычисления выражения
			str = str + "pop ebx\nmov " + e.scope + e.id + ", ebx\n";	//результат в регистр ebx;
			break;
		}
		case IT::STR: {
			IT::Entry e1 = IT_ENTRY(pos + 1);//первый правый операнд 
			if (LEXEMA(pos + 1) == LEX_ID && e1.idtype == IT::F) {	//вызов функции
				str = str + callFunc(tables, pos + 1);
				str = str + "mov " + e.scope + e.id + ", eax";
			}
			else if (LEXEMA(pos + 1) == LEX_LITERAL) {		//литерал
				str = str + "mov " /*+ e.scope*/ + e.id + ", offset " + e1.scope + e1.id;
			}
			else {	//идентификатор
				str = str + "mov ecx, " + e1.scope + e1.id + "\nmov " + e.scope + e.id + ", ecx";
			}
			break;
		}
		case IT::CHAR: {
			IT::Entry e1 = IT_ENTRY(pos + 1);//первый правый операнд 
			if (LEXEMA(pos + 1) == LEX_ID && e1.idtype == IT::F) {	//вызов функции
				str = str + callFunc(tables, pos + 1);
				str = str + "mov " + e.scope + e.id + ", eax";
			}
			else if (LEXEMA(pos + 1) == LEX_LITERAL) {		//литерал
				str = str + "mov " + e.scope + e.id + ", offset " +/*e1.scope*/ + e1.id;
			}
			else {	//идентификатор
				str = str + "mov ecx, " + e1.scope + e1.id + "\nmov " + e.scope + e.id + ", ecx";
			}
			break;
		}
	}
	return str;
}

namespace Generator {
	void CodeGeneration(Lex::Tables& tables) {
		ofstream asmFile("D:\\courseProject\\SVA-2022\\SVA-2022\\Generated\\Generated.asm");
		vector<string> v;
		header(tables, v);
		string cyclecode;
		string buff="";	//буфер для строк
		string buffForFuncName="";	//буфер для имени функции
		int numberOfParam;
		bool findmain = false;
		for (int i = 0; i < tables.lextable.size; i++) {
			switch (LEXEMA(i))
			{
				case LEX_MAIN:{
					buff = buff + FUNCTION_NAME("MAIN") + "main PROC";
					buffForFuncName = "main";
					numberOfParam = 0;
					findmain = true;
					break;	
				}
				case LEX_FUNCTION:
				{
					buffForFuncName = IT_ENTRY(i + 1).id;
					numberOfParam= tables.idtable.table[tables.lextable.table[i + 1].idxTI].numberOfParam;
					buff = headerOfFunc(tables, i+1, buffForFuncName, numberOfParam);
					break;
				}
				case LEX_STATE: {
					buff = genStateCode(tables, i, cyclecode);
					break;
				}
				case LEX_CORRECTLY: {
					buff = buff + "right" + to_string(counterOfStates) + ":";
					break;
				}
				case LEX_WRONG: {
					buff = buff + "wrong" + to_string(counterOfStates) + ":";
					break;
				}
				case LEX_BRACELET: {
					if (LEXEMA(i + 1) == LEX_CORRECTLY || LEXEMA(i + 1) == LEX_WRONG)
						buff = buff + "jmp next" + to_string(counterOfStates);
					break;
				}
				case LEX_RETURN: {
					if (!findmain) {
						buff = footerOfFunc(tables, i, buffForFuncName, numberOfParam);
						break;
					}
					else {
						buff = buff + STR_SEPARATOR;
						break;
					}
				}
				case LEX_EQUAL: {
					buff = generateEqual(tables, i);
					while (LEXEMA(++i) != LEX_SEMICOLON);
					break;
				}
				case LEX_PRINT: {
					IT::Entry e = IT_ENTRY(i + 1);
					if (findmain) {
						char* t = (char*)data(buffForFuncName);   //string->char
						char buff[10];
						for (int j = 0; j < tables.idtable.size;j++) {
							if (Lex::CMP(IT_ENTRY_IN_TABLE(j).scope, t) && Lex::CMP(e.id, IT_ENTRY_IN_TABLE(j).id)) {
								e = IT_ENTRY_IN_TABLE(j);
								break;
							}
						}
					}
					switch (e.iddatatype)
					{
						case IT::IDDATATYPE::INT: {
							buff = buff + "\npush " + e.scope + e.id + "\ncall PrintNumb\n";
							break;
							}
							
						case IT::IDDATATYPE::STR: {
							if (e.idtype == IT::IDTYPE::L)  buff = buff + "\npush offset " /*+ e.scope*/ + e.id + "\ncall PrintStroke\n";
							else  buff = buff + "\npush " + e.scope + e.id + "\ncall PrintStroke\n";
							break;
							}
						case IT::IDDATATYPE::CHAR: {
							if (e.idtype == IT::IDTYPE::L)  buff = buff + "\npush offset " /*+ e.scope*/ + e.id + "\ncall PrintStroke\n";
							else  buff = buff + "\npush " + e.scope + e.id + "\ncall PrintStroke\n";
							break;
						}
					}
					buff = buff + "\n";
					break;
				}
				case LEX_DOL: {
					if (LEXEMA(i - 1) == LEX_BRACELET) {
						buff += "next" + to_string(counterOfStates)+":";
					}
				}
				case LEX_ID: {
					if (LEXEMA(i + 4) == '@' && tables.idtable.table[tables.lextable.table[i + 4].idxTI].idtype == IT::F) {   //вызов функции i = ii@2;
						buff = callFunc(tables, i + 2); //первый параметр
						buff = buff + "\nmov " + IT_ENTRY(i).scope + IT_ENTRY(i).id + ",eax\n";
						while (LEXEMA(++i) != LEX_SEMICOLON);
					}
					break;
				}
			}
			if (!buff.empty()) {
				v.push_back(buff);
			}
			buff.clear();
		}
		v.push_back(END);
		for (string x : v)
			asmFile << x << endl;
	}
}