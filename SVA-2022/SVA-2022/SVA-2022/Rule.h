#pragma once
#define GRB_ERROR_SERIES 600
#include"Greibach.h"
#include"MFST.h"
namespace GRB {
#define NS(n) Rule::Chain::N(n)
#define	TS(n) Rule::Chain::T(n)
	Greibach greibach(NS('S'), TS('$'),
		10,
		Rule(NS('S'), GRB_ERROR_SERIES + 0,			//неверная структура программы
			4, //s-> tfiGT;S | tfiGTS | mT	
			Rule::Chain(7, TS('t'), TS('f'), TS('i'), NS('G'), NS('T'), TS(';'), NS('S')),
			Rule::Chain(6, TS('t'), TS('f'), TS('i'), NS('G'), NS('T'), NS('S')),
			Rule::Chain(2, TS('m'), NS('T')),
			Rule::Chain(3, TS('m'), NS('T'), TS(';'))
		),
		Rule(NS('G'), GRB_ERROR_SERIES + 3,		//ошибка в параметрах функции
			5,//G->ti | ti,G | (G) |() | (E)
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('G')),
			Rule::Chain(3, TS('('), NS('G'), TS(')')),
			Rule::Chain(2, TS('('), TS(')')),
			Rule::Chain(3, TS('('), NS('E'), TS(')'))
		),
		Rule(NS('T'), GRB_ERROR_SERIES + 6,		//ошибка в теле функции
			3,//T->[NrE] | [rE] | [N;rE]
			Rule::Chain(5, TS('['), NS('N'), TS('r'), NS('E'), TS(']')),
			Rule::Chain(4, TS('['), TS('r'), NS('E'), TS(']')),
			Rule::Chain(5, TS('['), NS('N'), TS(';'), TS('r'), NS('E'), TS(']'))
		),
		Rule(NS('N'), GRB_ERROR_SERIES + 1,		//ошибка в объявлении переменной	
			22,//N->nti;N | nti; | ?:M$A$ | ntfiG;N |  ntfiG | iC;N | iC; | ntiG;N | i=E; | i=E;N | iC; | iC;N | nti=E;N | nti=E; | i=M; | i=M;N | U(i); | U(i);N | S(i); | S(i);N | S(l); | S(l);N
			Rule::Chain(5, TS('n'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('n'), TS('t'), TS('i'), TS(';')),
			Rule::Chain(6, TS('?'), TS(':'), NS('M'), TS('$'), NS('A'), TS('$')),
			Rule::Chain(7, TS('n'), TS('t'), TS('f'), TS('i'), NS('G'), TS(';'), NS('N')),
			Rule::Chain(5, TS('n'), TS('t'), TS('f'), TS('i'), NS('G')),
			Rule::Chain(4, TS('i'), NS('C'), TS(';'), NS('N')),
			Rule::Chain(3, TS('i'), NS('C'), TS(';')),
			Rule::Chain(6, TS('n'), TS('t'), TS('i'), NS('G'), TS(';'), NS('N')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('p'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(3, TS('p'), NS('E'), TS(';')),
			Rule::Chain(4, TS('p'), NS('E'), NS('G'), TS(';')),
			Rule::Chain(5, TS('p'), NS('E'), NS('G'), TS(';'), NS('N')),
			Rule::Chain(7, TS('n'), TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(6, TS('n'), TS('t'), TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(5, TS('U'), TS('('), TS('i'), TS(')'), TS(';')),
			Rule::Chain(6, TS('U'), TS('('), TS('i'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(5, TS('S'), TS('('), TS('i'), TS(')'), TS(';')),
			Rule::Chain(6, TS('S'), TS('('), TS('i'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(5, TS('R'), TS('('), TS('l'), TS(')'), TS(';')),
			Rule::Chain(6, TS('R'), TS('('), TS('l'), TS(')'), TS(';'), NS('N'))
		),
		Rule(NS('C'), GRB_ERROR_SERIES + 10,			//ошибка в вызове функции;
			5,//C-> =E(E)VE | =E(E) | =M | =M(M)VM | =(M)VM |
			Rule::Chain(7, TS('='), NS('E'), TS('('), NS('E'), TS(')'), NS('V'), NS('E')),
			Rule::Chain(5, TS('='), NS('E'), TS('('), NS('E'), TS(')')),
			Rule::Chain(2, TS('='), NS('M')),
			Rule::Chain(7, TS('='), NS('M'), TS('('), NS('M'), TS(')'), NS('V'), NS('M')),
			Rule::Chain(6, TS('='), TS('('), NS('M'), TS(')'), NS('V'), NS('M'))
		),
		Rule(NS('M'), GRB_ERROR_SERIES + 2,			//ошибка в выражении
			6,	//M-> =M; | iVM | lVM | i | l | (M) 
			Rule::Chain(2, TS('='), NS('M')),
			Rule::Chain(3, TS('i'), NS('V'), NS('M')),
			Rule::Chain(3, TS('l'), NS('V'), NS('M')),
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('M'), TS(')'))
		),
		Rule(NS('V'), GRB_ERROR_SERIES + 11,		//ошибка в арифметической операции
			9,//V-> { | } | < | >|+-*/
			Rule::Chain(1, TS('>')),
			Rule::Chain(1, TS('<')),
			Rule::Chain(1, TS('}')),
			Rule::Chain(1, TS('{')),
			Rule::Chain(1, TS('+')),
			Rule::Chain(1, TS('-')),
			Rule::Chain(1, TS('*')),
			Rule::Chain(1, TS('/')),
			Rule::Chain(1, TS('%'))
		),
		Rule(NS('A'), GRB_ERROR_SERIES + 7,			//Ошибка при констуировании условного выражения
			4,//A->c:X | w:X | c:XA | w:XA
			Rule::Chain(3, TS('c'), TS(':'), NS('X')),
			Rule::Chain(3, TS('w'), TS(':'), NS('X')),
			Rule::Chain(4, TS('c'), TS(':'), NS('X'), NS('A')),
			Rule::Chain(4, TS('w'), TS(':'), NS('X'), NS('A'))
		),
		Rule(NS('X'), GRB_ERROR_SERIES + 8,			//Ошибка в теле условного выражения
			1,	//X->[i=M;]
			Rule::Chain(6, TS('['), TS('i'), TS('='), NS('M'), TS(';'), TS(']'))
		),
		Rule(NS('E'), GRB_ERROR_SERIES + 12, //ожидаются только литералы и идентификаторы
			6,//E-> i; | l; | i,E | l,E | i | l
			Rule::Chain(2, TS('i'), TS(';')),
			Rule::Chain(2, TS('l'), TS(';')),
			Rule::Chain(3, TS('i'), TS(','), NS('E')),
			Rule::Chain(3, TS('l'), TS(','), NS('E')),
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l'))
		)



	);
	 
	 
	
	//Greibach greibach(NS('S'), TS('$'),
	//	10,
	//	Rule(NS('S'), GRB_ERROR_SERIES+0,			//неверная структура программы
	//		4, //s-> tfiGT;S | tfiGTS | mT	
	//		Rule::Chain(7, TS('t'), TS('f'), TS('i'), NS('G'), NS('T'), TS(';'), NS('S')),
	//		Rule::Chain(3, TS('m'), NS('T'), TS(';')),
	//		Rule::Chain(6, TS('t'), TS('f'), TS('i'), NS('G'), NS('T'), NS('S')),
	//		Rule::Chain(2, TS('m'), NS('T'))
	//	),
	//	Rule(NS('G'), GRB_ERROR_SERIES + 3,		//ошибка в параметрах функции
	//		5,//G->ti | ti,G | (G) |() | (E)
	//		Rule::Chain(2, TS('t'), TS('i')),
	//		Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('G')),
	//		Rule::Chain(3, TS('('), NS('G'), TS(')')),
	//		Rule::Chain(2, TS('('), TS(')')),
	//		Rule::Chain(3, TS('('), NS('E'), TS(')'))
	//	),
	//	Rule(NS('T'), GRB_ERROR_SERIES + 6,		//ошибка в теле функции
	//		3,//T->[NrE] | [rE] | [N;rE]
	//		Rule::Chain(5, TS('['), NS('N'), TS('r'), NS('E'), TS(']')),
	//		Rule::Chain(4, TS('['), TS('r'), NS('E'), TS(']')),
	//		Rule::Chain(5, TS('['), NS('N'), TS(';'), TS('r'), NS('E'), TS(']'))
	//	),
	//	Rule(NS('N'), GRB_ERROR_SERIES + 1,		//ошибка в объявлении переменной	
	//		16,//N->nti;N | nti; | ?:M$A$ | ntfiG;N |  ntfiG | iC;N | iC; | ntiG;N | i=E; | i=E;N | iC; | iC;N | nti=E;N | nti=E;
	//		Rule::Chain(5, TS('n'), TS('t'), TS('i'), TS(';'), NS('N')),
	//		Rule::Chain(4, TS('n'), TS('t'), TS('i'), TS(';')),
	//		Rule::Chain(6, TS('?'), TS(':'), NS('M'), TS('$'), NS('A'), TS('$')),
	//		Rule::Chain(7, TS('n'), TS('t'), TS('f'), TS('i'), NS('G'), TS(';'), NS('N')),
	//		Rule::Chain(5, TS('n'), TS('t'), TS('f'), TS('i'), NS('G')),
	//		Rule::Chain(4, TS('i'),NS('C'),TS(';'), NS('N')),
	//		Rule::Chain(3, TS('i'),NS('C'),TS(';')),
	//		Rule::Chain(6, TS('n'), TS('t'), TS('i'), NS('G'), TS(';'), NS('N')),
	//		Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
	//		Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
	//		Rule::Chain(4, TS('p'), NS('E'), TS(';'), NS('N')),
	//		Rule::Chain(3, TS('p'), NS('E'), TS(';')),
	//		Rule::Chain(4, TS('p'), NS('E'), NS('G'), TS(';')),
	//		Rule::Chain(5, TS('p'), NS('E'), NS('G'), TS(';'), NS('N')),
	//		Rule::Chain(7, TS('n'), TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
	//		Rule::Chain(6, TS('n'), TS('t'), TS('i'), TS('='), NS('E'), TS(';'))
	//	),
	//	Rule(NS('C'),GRB_ERROR_SERIES+10,			//ошибка в вызове функции;
	//		2,//C-> =E(E)VE | =E(E)
	//		Rule::Chain(7,TS('='),NS('E'),TS('('),NS('E'),TS(')'),NS('V'),NS('E')),
	//		Rule::Chain(5,TS('='),NS('E'),TS('('),NS('E'),TS(')'))
	//		),
	//	Rule(NS('M'), GRB_ERROR_SERIES + 2,			//ошибка в выражении
	//		2,	//M->iVi; | i
	//		Rule::Chain(3, TS('i'), NS('V'), TS('i')),
	//		Rule::Chain(1, TS('i'))
	//	),
	//	Rule(NS('V'), GRB_ERROR_SERIES + 11,		//ошибка в арифметической операции
	//		8,//V-> { | } | < | >|+-*/
	//		Rule::Chain(1, TS('>')),
	//		Rule::Chain(1, TS('<')),
	//		Rule::Chain(1, TS('}')),
	//		Rule::Chain(1, TS('{')),
	//		Rule::Chain(1, TS('+')),
	//		Rule::Chain(1, TS('-')),
	//		Rule::Chain(1, TS('*')),
	//		Rule::Chain(1, TS('/'))
	//	),
	//	Rule(NS('A'), GRB_ERROR_SERIES + 7,			//Ошибка при констуировании условного выражения
	//		4,//A->c:X | w:X | c:XA | w:XA
	//		Rule::Chain(3, TS('c'), TS(':'), NS('X')),
	//		Rule::Chain(3, TS('w'), TS(':'), NS('X')),
	//		Rule::Chain(4, TS('c'), TS(':'), NS('X'), NS('A')),
	//		Rule::Chain(4, TS('w'), TS(':'), NS('X'), NS('A'))
	//	),
	//	Rule(NS('X'), GRB_ERROR_SERIES + 8,			//Ошибка в теле условного выражения
	//		1,	//X->[i=M;]
	//		Rule::Chain(6, TS('['), TS('i'), TS('='), NS('M'), TS(';'), TS(']'))
	//	),
	//	Rule(NS('E'), GRB_ERROR_SERIES+12, //ожидаются только литералы и идентификаторы
	//		6,//E-> i; | l; | i,E | l,E | i | l
	//		Rule::Chain(2, TS('i'), TS(';')),
	//		Rule::Chain(2, TS('l'), TS(';')),
	//		Rule::Chain(3, TS('i'), TS(','), NS('E')),
	//		Rule::Chain(3, TS('l'), TS(','), NS('E')),
	//		Rule::Chain(1, TS('i')),
	//		Rule::Chain(1, TS('l'))
	//		)
	//	);





	//Greibach greibach(NS('S'), TS('$'),
	//	6,
	//	Rule(
	//		NS('S'), GRB_ERROR_SERIES + 0, //структура программы
	//		4, //S→ m[NrE;];|tfi(F)[NrE;];S|m[NrE;];S|tfi(F)[NrE;];
	//		Rule::Chain(8, TS('m'), TS('['), NS('N'), TS('r'), NS('E'), TS(';'), TS(']'), TS(';')),
	//		Rule::Chain(14, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('['), NS('N'), TS('r'), NS('E'), TS(';'), TS(']'), TS(';'), NS('S')),
	//		Rule::Chain(9, TS('m'), TS('['), NS('N'), TS('r'), NS('E'), TS(';'), TS(']'), TS(';'), NS('S')),
	//		Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('['), NS('N'), TS('r'), NS('E'), TS(';'), TS(']'), TS(';'))
	//	),
	//	Rule(
	//		NS('N'), GRB_ERROR_SERIES + 1, //выражения
	//		12, // N→ dti;|rE;|i=E;|dtfi(F);|dti;N|i=E;N|dtfi(F);N|dti(F);N|dti(F);|pE;|pE;N|?:S
	//		Rule::Chain(4, TS('n'), TS('t'), TS('i'), TS(';')),
	//		Rule::Chain(5, TS('n'), TS('t'), TS('i'), TS(';'), NS('N')),
	//		Rule::Chain(3, TS('r'), NS('E'), TS(';')),
	//		Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
	//		Rule::Chain(8, TS('n'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';')),
	//		Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
	//		Rule::Chain(9, TS('n'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),
	//		Rule::Chain(8, TS('n'), TS('t'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),
	//		Rule::Chain(7, TS('n'), TS('t'), TS('i'), TS('('), NS('F'), TS(')'), TS(';')),
	//		Rule::Chain(3, TS('p'), NS('E'), TS(';')),
	//		Rule::Chain(4, TS('p'), NS('E'), TS(';'), NS('N')),
	//		Rule::Chain(4, TS('?'), TS(':'), NS('S'))
	//	),
	//	Rule(
	//		NS('E'), GRB_ERROR_SERIES + 2, //выражения
	//		8, // E -> i|l|(E)|i(W)|iM|lM|(E)M|i(W)M
	//		Rule::Chain(1, TS('i')),
	//		Rule::Chain(1, TS('l')),
	//		Rule::Chain(3, TS('('), NS('E'), TS(')')),
	//		Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
	//		Rule::Chain(2, TS('i'), NS('M')),
	//		Rule::Chain(2, TS('l'), NS('M')),
	//		Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
	//		Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M'))
	//	),
	//	Rule(
	//		NS('M'), GRB_ERROR_SERIES + 3,
	//		8,//M→vE|vEM(v->+-/*)
	//		Rule::Chain(2, TS('+'), NS('E')),
	//		Rule::Chain(3, TS('+'), NS('E'), NS('M')),
	//		Rule::Chain(2, TS('-'), NS('E')),
	//		Rule::Chain(3, TS('-'), NS('E'), NS('M')),
	//		Rule::Chain(2, TS('*'), NS('E')),
	//		Rule::Chain(3, TS('*'), NS('E'), NS('M')),
	//		Rule::Chain(2, TS('/'), NS('E')),
	//		Rule::Chain(3, TS('/'), NS('E'), NS('M'))
	//	),

	//	Rule(
	//		NS('F'), GRB_ERROR_SERIES + 4, //параметры
	//		2, // F -> ti | ti,F
	//		Rule::Chain(2, TS('t'), TS('i')),
	//		Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))

	//	),
	//	Rule(
	//		NS('W'), GRB_ERROR_SERIES + 5, //параметры в передаваемую функцию
	//		4, // W -> i | l | i,W | l,W |
	//		Rule::Chain(1, TS('i')),
	//		Rule::Chain(1, TS('l')),
	//		Rule::Chain(3, TS('i'), TS(','), NS('W')),
	//		Rule::Chain(3, TS('l'), TS(','), NS('W'))
	//	)
	//	//Rule(
	//	//	NS('v'), GRB_ERROR_SERIES + 5, //операторы
	//	//	4,				// v -> * | / | - | +
	//	//	Rule::Chain(1, TS('+')),
	//	//	Rule::Chain(1, TS('+')),
	//	//	Rule::Chain(1, TS('*')),
	//	//	Rule::Chain(1, TS('/'))
	//	//)
	//);
}