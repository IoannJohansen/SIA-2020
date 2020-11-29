#include "FST.h"
#include "stdafx.h"

namespace FST {
	RELATION::RELATION(char c, short ns) {
		symbol = c;
		nnode = ns;
	}

	NODE::NODE() {			
		n_relation = 0;
		relations = NULL;
	}
	NODE::NODE(short n, RELATION rel, ...) {
		n_relation = n;
		RELATION* p = &rel;
		relations = new RELATION[n];
		for (short i = 0; i < n; i++) relations[i] = p[i];
	}

	FST::FST(char* s, short ns, NODE  n, ...) {
		string = s;
		nstates = ns;
		nodes = new NODE[ns];		// выделение памяти под массив состояний
		NODE* p = &n;				// указатель на начало массива состояний
		for (int k = 0; k < ns; k++) nodes[k] = p[k];	// заполнение масс сост
		rstates = new short[nstates];					// выделение памяти под массив
		memset(rstates, 0xff, sizeof(short) * nstates); // заполнение массива -1
		rstates[0] = 0;									// 0-й эл масс = 0
		position = -1;									// позиция цепочки = -1
	}

	bool step(FST& fst, short*& rstates)	// шаг автомата
	{
		bool rc = false;
		std::swap(rstates, fst.rstates);				// смена массивов
		for (short i = 0; i < fst.nstates; i++)
		{
			if (rstates[i] == fst.position)
				for (short j = 0; j < fst.nodes[i].n_relation; j++)
				{
					if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])
					{
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
						rc = true;
					}
				}
		}
		return rc;
	}

	bool execute(FST& fst) {					// разбор цепочки
		short* rstates = new short[fst.nstates];				// выделение памяти под массив
		memset(rstates, 0xff, sizeof(short) * fst.nstates);		// заполнение его -1
		short lstring = strlen(fst.string);
		bool rc = true;
		for (short i = 0; i < lstring && rc; i++)
		{
			fst.position++;
			rc = step(fst, rstates);			// следующий шаг
		}
		delete[] rstates;
		return (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
	}
	
}