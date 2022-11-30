#include"stdafx.h"
#include"SemAn.h"
#include"Gen.h"
int _tmain(int argc, TCHAR* argv[]) {
	setlocale(LC_CTYPE, "ru");
	Out::OUT out = Out::INITOUT;
	Log::LOG log = Log::INITLOG;
	try {
		Parm::PARM parm = Parm::getparm(argc, argv);
		In::IN in = In::getin(parm.in);
		out = Out::getOut(parm.out);
		Out::WriteOut(out, in);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, (char*)"Текст:", (char*)" без ошибок\n", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		Log::WriteIn(log, in);
		cout << "Cтарт лексического анализа...\n";
		Lex::Tables tables = Lex::LexAnalizer(in, out);
		cout << "Лексический анализ завершен успешно.\n";
		cout << "Старт синтаксического анализа...\n";
		MFST::Mfst mfs();
		MFST::Mfst mfst(tables.lextable, GRB::getGreibach(), parm.greibach);
		bool checkSynt = mfst.start();
		mfst.savededucation();
		mfst.printRules();
		if (!checkSynt) {
			cout << "Ошибка в ходе синтаксического анализа. Подробную информацию можно увидеть в greibach файле.\n";
			return 0;
		}
		cout << "Синтаксический анализ прошел успешно.\n";
		cout << "Старт семантического анализа...\n";
		bool SemanticOk = Semantic::semanticsCheck(tables, log);
		if (!SemanticOk) {
			cout << "Ошибка в ходе семантического анализа.Подробную информацию можно увидеть в log файле.\n";
		}
		cout << "Семантический анализ завершен успешно.\n";
		cout << "Генерация польской записи...\n";
		PN::PolishStart(tables);
		LT::showTable(tables.lextable);
		IT::showTable(tables.idtable);
		cout << "Генерация польской записи завершена...\n";
		cout << "Старт генерации кода..." << endl;
		Generator::CodeGeneration(tables);
		cout << "Генерация кода завершена.\n";


		Out::Close(out);
		/*cout << in.text << endl;
		cout << "Всего символов: " << in.size << endl;
		cout << "Всего строк: " << in.lines << endl;
		cout << "Пропущено: " << in.ignor << endl;*/

		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		std::cout << "\nОшибка " << e.id
			<< ": " << e.message
			<< "\nСтрока " << e.inext.line
			<< " позиция " << e.inext.column << std::endl;
		Log::WriteError(log, e);
	}
}