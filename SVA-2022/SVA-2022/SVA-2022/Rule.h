#pragma once
#define GRB_ERROR_SERIES 600
#include"Greibach.h"
#include"MFST.h"
namespace GRB {
#define NS(n) Rule::Chain::N(n)
#define	TS(n) Rule::Chain::T(n)
	Greibach greibach(NS('S'), TS('$'),
		12,
		Rule(NS('S'), GRB_ERROR_SERIES + 0,			//неверная структура программы
			4, //s-> tfiGT;S | tfiGTS | mT	
			Rule::Chain(7, TS('t'), TS('f'), TS('i'), NS('G'), NS('T'), TS(';'), NS('S')),
			Rule::Chain(6, TS('t'), TS('f'), TS('i'), NS('G'), NS('T'), NS('S')),
			Rule::Chain(2, TS('m'), NS('T')),
			Rule::Chain(3, TS('m'), NS('T'), TS(';'))
		),

		Rule(NS('T'), GRB_ERROR_SERIES + 6,		//ошибка в теле функции
			3,//T->[NrE] | [rE] | [N;rE]
			Rule::Chain(5, TS('['), NS('N'), TS('r'), NS('E'), TS(']')),
			Rule::Chain(4, TS('['), TS('r'), NS('E'), TS(']')),
			Rule::Chain(5, TS('['), NS('N'), TS(';'), TS('r'), NS('E'), TS(']'))
		),
		Rule(NS('G'), GRB_ERROR_SERIES + 3,		//ошибка в параметрах функции
			5,//G->ti | ti,G | (G) |() | (E)
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('G')),
			Rule::Chain(3, TS('('), NS('G'), TS(')')),
			Rule::Chain(2, TS('('), TS(')')),
			Rule::Chain(3, TS('('), NS('E'), TS(')'))
		),
		Rule(NS('N'), GRB_ERROR_SERIES + 1,		//ошибка в объявлении переменной	
			25,//N->nti;N | nti; | ?K | i=E; | i=E;N | iC; | iC;N | nti=E;N | nti=E; | i=M; | i=M;N | U(i); | U(i);N | S(i); | S(i);N | R(l); | R(l);N | ntiC; |ntiC;N | nti=L; | nti=L;N | i=L; | i=L;N
			Rule::Chain(5, TS('n'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('n'), TS('t'), TS('i'), TS(';')),
			Rule::Chain(2, TS('?'), NS('K')),
			Rule::Chain(4, TS('i'), NS('C'), TS(';'), NS('N')),
			Rule::Chain(3, TS('i'), NS('C'), TS(';')),
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
			Rule::Chain(6, TS('R'), TS('('), TS('l'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(7, TS('n'), TS('t'), TS('i'), TS('='), NS('L'), TS(';'), NS('N')),
			Rule::Chain(6, TS('n'), TS('t'), TS('i'), TS('='), NS('L'), TS(';')),
			Rule::Chain(4, TS('i'), TS('='), NS('L'), TS(';')),
			Rule::Chain(5, TS('i'), TS('='), NS('L'), TS(';'), NS('N')),
			Rule::Chain(5, TS('n'), TS('t'), TS('i'), NS('C'), TS(';')),
			Rule::Chain(6, TS('n'), TS('t'), TS('i'), NS('C'), TS(';'), NS('N'))
		),
		Rule(NS('K'), GRB_ERROR_SERIES + 12,//ошибка в структуре условного выражения
			4,//K-> :M$A$ | :M$A$N | :M$$ | :M$$N
			Rule::Chain(5, TS(':'), NS('M'), TS('$'), NS('A'), TS('$')),
			Rule::Chain(6, TS(':'), NS('M'), TS('$'), NS('A'), TS('$'), NS('N')),
			Rule::Chain(4, TS(':'), NS('M'), TS('$'), TS('$')),
			Rule::Chain(5, TS(':'), NS('M'), TS('$'), TS('$'), NS('N'))
		),

		Rule(NS('L'), GRB_ERROR_SERIES + 11, //ошибка в вызове стандартной функции
			12,
			Rule::Chain(4, TS('R'), TS('('), TS('i'), TS(')')),
			Rule::Chain(4, TS('R'), TS('('), TS('l'), TS(')')),
			Rule::Chain(6, TS('R'), TS('('), TS('i'), TS(')'), NS('V'), NS('M')),
			Rule::Chain(6, TS('R'), TS('('), TS('l'), TS(')'), NS('V'), NS('M')),
			Rule::Chain(4, TS('S'), TS('('), TS('i'), TS(')')),
			Rule::Chain(4, TS('S'), TS('('), TS('l'), TS(')')),
			Rule::Chain(6, TS('S'), TS('('), TS('l'), TS(')'), NS('V'), NS('M')),
			Rule::Chain(6, TS('S'), TS('('), TS('i'), TS(')'), NS('V'), NS('M')),
			Rule::Chain(4, TS('U'), TS('('), TS('i'), TS(')')),
			Rule::Chain(4, TS('U'), TS('('), TS('l'), TS(')')),
			Rule::Chain(6, TS('U'), TS('('), TS('l'), TS(')'), NS('V'), NS('M')),
			Rule::Chain(6, TS('U'), TS('('), TS('i'), TS(')'), NS('V'), NS('M'))
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
			10,	//M-> =M; | iVM | lVM | i | l | (M) 
			Rule::Chain(2, TS('='), NS('M')),
			Rule::Chain(3, TS('i'), NS('V'), NS('M')),
			Rule::Chain(3, TS('l'), NS('V'), NS('M')),
			Rule::Chain(4, TS('!'), TS('i'), NS('V'), NS('M')),
			Rule::Chain(4, TS('!'), TS('l'), NS('V'), NS('M')),
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(2, TS('!'), TS('i')),
			Rule::Chain(2, TS('!'), TS('l')),
			Rule::Chain(3, TS('('), NS('M'), TS(')'))
		),
		Rule(NS('V'), GRB_ERROR_SERIES + 11,		//ошибка в арифметической операции
			12,//V-> { | } | < | >|+-*/
			Rule::Chain(1, TS('>')),
			Rule::Chain(1, TS('<')),
			Rule::Chain(1, TS('}')),
			Rule::Chain(1, TS('{')),
			Rule::Chain(1, TS('+')),
			Rule::Chain(1, TS('-')),
			Rule::Chain(1, TS('*')),
			Rule::Chain(1, TS('/')),
			Rule::Chain(1, TS('%')),
			Rule::Chain(1, TS('|')),
			Rule::Chain(1, TS('&')),
			Rule::Chain(1, TS('!'))
		),
		Rule(NS('A'), GRB_ERROR_SERIES + 7,			//Ошибка в теле условного выражения
			7,//A->c:[X] | w:[X] | c:[X]A | w:[X]A |  w:XAN | c:XAN | v[N]
			Rule::Chain(5, TS('c'), TS(':'), TS('['), NS('X'), TS(']')),
			Rule::Chain(5, TS('w'), TS(':'), TS('['), NS('X'), TS(']')),
			Rule::Chain(6, TS('c'), TS(':'), TS('['), NS('X'), TS(']'), NS('A')),
			Rule::Chain(6, TS('w'), TS(':'), TS('['), NS('X'), TS(']'), NS('A')),
			Rule::Chain(7, TS('c'), TS(':'), TS('['), NS('X'), TS(']'), NS('A'), NS('N')),
			Rule::Chain(7, TS('w'), TS(':'), TS('['), NS('X'), TS(']'), NS('A'), NS('N')),
			Rule::Chain(4, TS('v'), TS('['), NS('N'), TS(']'))
		),
		Rule(NS('X'), GRB_ERROR_SERIES + 8,			//Ошибка в теле условного выражения
			3,	//X->i=M; | i=M;X | ?K
			Rule::Chain(4, TS('i'), TS('='), NS('M'), TS(';')),
			Rule::Chain(5, TS('i'), TS('='), NS('M'), TS(';'), NS('X')),
			Rule::Chain(2, TS('?'), NS('K'))
		),
		Rule(NS('E'), GRB_ERROR_SERIES + 12, //ожидаются только литералы и идентификаторы
			12,//E-> i; | l; | i,E | l,E | i | l | iVE | lVE | (E) | (E)VE
			Rule::Chain(2, TS('i'), TS(';')),
			Rule::Chain(2, TS('l'), TS(';')),
			Rule::Chain(3, TS('i'), TS(','), NS('E')),
			Rule::Chain(3, TS('l'), TS(','), NS('E')),
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3,TS('i'),NS('V'),NS('E')),
			Rule::Chain(3, TS('l'), NS('V'), NS('E')),
			Rule::Chain(2, TS('i'), NS('V')),
			Rule::Chain(2, TS('l'), NS('V')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(5, TS('('), NS('E'), TS(')'),NS('V'),NS('E'))
		)
	);
}