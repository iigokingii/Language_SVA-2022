#include "FST.h"
#include <vector>

namespace FST
{
	RELATION::RELATION(
		char c,
		short nn
	)
	{
		symbol = c;
		nnode = nn;
	};

	NODE::NODE()
	{
		n_relation = 0;
		relations = NULL;
	};

	NODE::NODE(
		short n,
		RELATION rel,
		...
	)
	{
		n_relation = n;
		RELATION* p = &rel;		relations = new RELATION[n];
		for (short i = 0; i < n; i++)
		{
			relations[i] = p[i];
		}
	};

	FST::FST(
		char* s,
		short ns,
		NODE n,
		...)
	{
		string = s;
		nstates = ns;
		nodes = new NODE[ns];

		NODE* p = &n;

		for (int k = 0; k < ns; k++)
		{
			nodes[k] = p[k];
		}

		position = -1;
	};

	bool execute(FST& fst)
	{
		char* str = fst.string;
		char symb;
		short nRStates = 1;

		fst.rstates = new short[1]; //// возможные состо€ни€ автомата на данной позиции
		fst.rstates[0] = 0;

		for (short i = 0; i < strlen(str); i++)
		{
			symb = str[i];
			fst.position++; // текуща€ позици€ в цепочке

			if (isAllowed(symb, fst.rstates, nRStates, fst))//проверил что сивол пожходи какому-то сиволу из задан сост, доб нов сост
			{
				fst.rstates = setRelState(symb, fst, &nRStates, fst.rstates);  //rstates возможные состо€ни€ автомата на данной позиции

				if (i + 1 == strlen(str) && isLastState(fst.rstates, nRStates, fst.nstates))
				{
					return true;
				}
			}
			else
			{
				return false;
			}
		}
		return false;
	}

	bool isLastState(short* rstates, short length, short countStates)
	{
		for (short i = 0; i < length; i++)
		{
			if (rstates[i] == countStates - 1)
			{
				return true;
			}
		}

		return false;
	}

	bool isAllowed(
		char symb,
		short*& rstates,
		short length,
		FST& fst
	)
	{
		for (short i = 0; i < length; i++)
		{
			for (short j = 0; j < fst.nodes[rstates[i]].n_relation; j++) //nodes-гра‘ ѕ≈–≈ходов.n_relation колич индентичн реб
			{
				if (symb == fst.nodes[rstates[i]].relations[j].symbol) //прозодимс€ по массиву сивмолов на сост если символ совпад с каким симвл ntru
				{
					return true;
				}
			}
		}
		return false;
	}

	short* setRelState(
		char symb,
		FST& fst,
		short* pNRStates,// количество возможных состо€ний
		short* rstates)// массив возможных состо€ний
	{
		vector<short> vrstates;
		short nRStates = *pNRStates;

		for (short i = 0; i < nRStates; i++) //идем по всем сост
		{
			for (short j = 0; j < fst.nodes[rstates[i]].n_relation; j++) //идем по всем комбинац сост
			{
				if (fst.nodes[rstates[i]].relations[j].symbol == symb)
				{
					vrstates.push_back(fst.nodes[rstates[i]].relations[j].nnode);  //  nnode;номер смежной вершины
				}
			}
		}

		delete[] rstates;

		auto result = new short[vrstates.size()];
		*pNRStates = vrstates.size();

		for (short i = 0; i < vrstates.size(); i++)
		{
			result[i] = vrstates[i];
		}

		return result;
	}
}