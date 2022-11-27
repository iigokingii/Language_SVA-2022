#pragma once
#define GRB_ERROR_SERIES 600
#include"Greibach.h"
#include"MFST.h"
namespace GRB {
#define NS(n) Rule::Chain::N(n)
#define	TS(n) Rule::Chain::T(n)
	Greibach greibach(NS('S'), TS('$'),
		6,
		Rule(
			NS('S'), GRB_ERROR_SERIES + 0, //структура программы
			4, //S→ m[NrE;];|tfi(F)[NrE;];S|m[NrE;];S|tfi(F)[NrE;];
			Rule::Chain(8, TS('m'), TS('['), NS('N'), TS('r'), NS('E'), TS(';'), TS(']'), TS(';')),
			Rule::Chain(14, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('['), NS('N'), TS('r'), NS('E'), TS(';'), TS(']'), TS(';'), NS('S')),
			Rule::Chain(9, TS('m'), TS('['), NS('N'), TS('r'), NS('E'), TS(';'), TS(']'), TS(';'), NS('S')),
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('['), NS('N'), TS('r'), NS('E'), TS(';'), TS(']'), TS(';'))
		),
		Rule(
			NS('N'), GRB_ERROR_SERIES + 1, //выражения
			12, // N→ dti;|rE;|i=E;|dtfi(F);|dti;N|i=E;N|dtfi(F);N|dti(F);N|dti(F);|pE;|pE;N
			Rule::Chain(4, TS('n'), TS('t'), TS('i'), TS(';')),
			Rule::Chain(5, TS('n'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(3, TS('r'), NS('E'), TS(';')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(8, TS('n'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(9, TS('n'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(8, TS('n'), TS('t'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(7, TS('n'), TS('t'), TS('i'), TS('('), NS('F'), TS(')'), TS(';')),
			Rule::Chain(3, TS('p'), NS('E'), TS(';')),
			Rule::Chain(4, TS('p'), NS('E'), TS(';'), NS('N'))
		),
		Rule(
			NS('E'), GRB_ERROR_SERIES + 2, //выражения
			8, // E -> i|l|(E)|i(W)|iM|lM|(E)M|i(W)M
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M'))
		),
		Rule(
			NS('M'), GRB_ERROR_SERIES + 3,
			8,//M→vE|vEM(v->+-/*)
			Rule::Chain(2, TS('+'), NS('E')),
			Rule::Chain(3, TS('+'), NS('E'), NS('M')),
			Rule::Chain(2, TS('-'), NS('E')),
			Rule::Chain(3, TS('-'), NS('E'), NS('M')),
			Rule::Chain(2, TS('*'), NS('E')),
			Rule::Chain(3, TS('*'), NS('E'), NS('M')),
			Rule::Chain(2, TS('/'), NS('E')),
			Rule::Chain(3, TS('/'), NS('E'), NS('M'))
		),

		Rule(
			NS('F'), GRB_ERROR_SERIES + 4, //параметры
			2, // F -> ti | ti,F
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))

		),
		Rule(
			NS('W'), GRB_ERROR_SERIES + 5, //параметры в передаваемую функцию
			4, // W -> i | l | i,W | l,W |
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		)
		//Rule(
		//	NS('v'), GRB_ERROR_SERIES + 5, //операторы
		//	4,				// v -> * | / | - | +
		//	Rule::Chain(1, TS('+')),
		//	Rule::Chain(1, TS('+')),
		//	Rule::Chain(1, TS('*')),
		//	Rule::Chain(1, TS('/'))
		//)
	);
}