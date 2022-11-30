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
		Log::WriteLine(log, (char*)"�����:", (char*)" ��� ������\n", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		Log::WriteIn(log, in);
		cout << "C���� ������������ �������...\n";
		Lex::Tables tables = Lex::LexAnalizer(in, out);
		cout << "����������� ������ �������� �������.\n";
		cout << "����� ��������������� �������...\n";
		MFST::Mfst mfs();
		MFST::Mfst mfst(tables.lextable, GRB::getGreibach(), parm.greibach);
		bool checkSynt = mfst.start();
		mfst.savededucation();
		mfst.printRules();
		if (!checkSynt) {
			cout << "������ � ���� ��������������� �������. ��������� ���������� ����� ������� � greibach �����.\n";
			return 0;
		}
		cout << "�������������� ������ ������ �������.\n";
		cout << "����� �������������� �������...\n";
		bool SemanticOk = Semantic::semanticsCheck(tables, log);
		if (!SemanticOk) {
			cout << "������ � ���� �������������� �������.��������� ���������� ����� ������� � log �����.\n";
		}
		cout << "������������� ������ �������� �������.\n";
		cout << "��������� �������� ������...\n";
		PN::PolishStart(tables);
		LT::showTable(tables.lextable);
		IT::showTable(tables.idtable);
		cout << "��������� �������� ������ ���������...\n";
		cout << "����� ��������� ����..." << endl;
		Generator::CodeGeneration(tables);
		cout << "��������� ���� ���������.\n";


		Out::Close(out);
		/*cout << in.text << endl;
		cout << "����� ��������: " << in.size << endl;
		cout << "����� �����: " << in.lines << endl;
		cout << "���������: " << in.ignor << endl;*/

		Log::Close(log);
	}
	catch (Error::ERROR e)
	{
		std::cout << "\n������ " << e.id
			<< ": " << e.message
			<< "\n������ " << e.inext.line
			<< " ������� " << e.inext.column << std::endl;
		Log::WriteError(log, e);
	}
}