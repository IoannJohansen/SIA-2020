#pragma once
#include <iostream>

namespace FST {
	struct RELATION
	{
		char symbol;
		short nnode;			// номер смежной вершины
		RELATION(
			char c = 0x00,
			short ns = NULL
		);
	};

	struct NODE					// вершина графа
	{
		short n_relation;		// кол-во интцидентных ребер
		RELATION* relations;	// ребра
		NODE();					// констр.
		NODE(					// констр с парам.
			short n,
			RELATION rel, ...
		);
	};

	struct FST
	{
		char* string;			// цепочка
		short position;			// текущая позиция в цепочке
		short nstates;			// кол-во состояний автомата
		NODE* nodes;			// граф переходов [0] - начальное состояние [nstate-1] - конечное
		short* rstates;			// возможно состояние автомата на данной позиции
		FST(					// констурктор
			char* s,			// цепочка
			short ns,			// кол-во состояний автомата
			NODE  n, ...		// список состояний
		);
	};

	bool step(FST& fst, short*& rstates);
	bool execute(FST& fst);

}
