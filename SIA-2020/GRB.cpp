#include "stdafx.h"
#include <cstring>
#define GRB_ERROR_SERIES 600

namespace GRB
{
	/*
		S -> m{NrE;}; | tfi(F){NrE;};S | m{NrE;};S
		N -> dti; | rE; | i=E; | dtfi(F); | dti;N | re;N | i=E;N | dtfi(F);N
		E -> i | l | (E) | i(W) | iM | lM | (E)M | i(W)M
		M -> vE | vEM
		F -> ti | ti,F
		W -> i | l | i,W | l,W
	*/

	Greibach greibach(NS('S'), TS('$')				// стартовый символ / дно стека
		, 8											
		, Rule(NS('S'), GRB_ERROR_SERIES + 0, 4,		// структура программы
			Rule::Chain(5, TS('e'), TS('['), NS('N'), TS(']'), TS(';')),
			Rule::Chain(6, TS('e'), TS('['), NS('N'), TS(']'), TS(';'), NS('S')),
			Rule::Chain(11, TS('t'), TS('p'), TS('i'), TS('('), NS('F'), TS(')'), TS('['), NS('N'), TS(']'), TS(';'), NS('S')),
			Rule::Chain(10, TS('t'), TS('p'), TS('i'), TS('('), NS('F'), TS(')'), TS('['), NS('N'), TS(']'), TS(';')))


		, Rule(NS('N'), GRB_ERROR_SERIES + 1, 18		// конструкции в функциях
			, Rule::Chain(5, TS('c'), TS('t'), TS('i'), TS(';'), NS('N'))
			, Rule::Chain(4, TS('c'), TS('t'), TS('i'), TS(';'))
			, Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';'))
			, Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N'))
			, Rule::Chain(4, TS('r'), NS('L'), TS(';'), NS('N'))
			, Rule::Chain(3, TS('r'), NS('L'), TS(';'))
			, Rule::Chain(5, TS('s'), TS('('), NS('W'), TS(')'), NS('N'))
			, Rule::Chain(4, TS('s'), TS('('), NS('W'), TS(')'))
			, Rule::Chain(5, TS('x'), TS('('), NS('W'), TS(')'), NS('N'))
			, Rule::Chain(4, TS('x'), TS('('), NS('W'), TS(')'))
			, Rule::Chain(6, TS('i'), TS('('), NS('W'), TS(')'), TS(';'), NS('N'))
			, Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), TS(';'))
			, Rule::Chain(6, TS('m'), NS('Q'), TS('{'), NS('N'), TS('}'), NS('N'))
			, Rule::Chain(5, TS('m'), NS('Q'), TS('{'), NS('N'), TS('}'))
			, Rule::Chain(9, TS('m'), NS('Q'), TS('{'), NS('N'), TS('}'), TS('a'), TS('{'), NS('N'), TS('}'))
			, Rule::Chain(10, TS('m'), NS('Q'), TS('{'), NS('N'), TS('}'), TS('a'), TS('{'), NS('N'), TS('}'), NS('N'))
			, Rule::Chain(4, TS('o'), NS('E'), TS(';'), NS('N'))
			, Rule::Chain(3, TS('o'), NS('E'), TS(';')))

			
		, Rule(NS('E'), GRB_ERROR_SERIES + 2, 12		// выражения
			, Rule::Chain(1, TS('i'))
			, Rule::Chain(1, TS('l'))
			, Rule::Chain(3, TS('('), NS('E'), TS(')'))
			, Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')'))
			, Rule::Chain(2, TS('i'), NS('M'))
			, Rule::Chain(2, TS('l'), NS('M'))
			, Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M'))
			, Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M'))
			, Rule::Chain(4, TS('s'), TS('('), NS('W'), TS(')'))
			, Rule::Chain(5, TS('s'), TS('('), NS('W'), TS(')'), NS('N'))
			, Rule::Chain(4, TS('x'), TS('('), NS('W'), TS(')'))
			, Rule::Chain(5, TS('x'), TS('('), NS('W'), TS(')'), NS('N')))


		, Rule(NS('M'), GRB_ERROR_SERIES + 3, 3		// знаки
			, Rule::Chain(2, TS('v'), NS('E'))
			, Rule::Chain(3, TS('v'), NS('E'), NS('M'))
			, Rule::Chain(2, TS('v'), NS('L')))

		, Rule(NS('F'), GRB_ERROR_SERIES + 4, 2		// параметры функции
			, Rule::Chain(2, TS('t'), TS('i'))
			, Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F')))

		, Rule(NS('W'), GRB_ERROR_SERIES + 5, 4		//	фактические параметры
			, Rule::Chain(1, TS('i'))
			, Rule::Chain(1, TS('l'))
			, Rule::Chain(3, TS('i'), TS(','), NS('W'))
			, Rule::Chain(3, TS('l'), TS(','), NS('W')))

		, Rule(NS('Q'), GRB_ERROR_SERIES + 6, 2		// Q->  (L<L)  |  (L>L)
			, Rule::Chain(5, TS('('), NS('L'), TS('v'), NS('L'), TS(')'))
			, Rule::Chain(5, TS('('), NS('L'), TS('v'), NS('L'), TS(')')))
		,
		  Rule(NS('L'),	GRB_ERROR_SERIES + 7,	2			// Литералы и идентификаторы // L->  (l)  |  (i)
		    ,  Rule::Chain(1, TS('i'))
			,  Rule::Chain(1, TS('l')))
	);

	Rule::Chain::Chain(short psize, GRBALPHABET s, ...) // конструктор цепочки - праыой части правила(кол - во символов в цепочке, терминал или нетерминал...)
	{
		nt = new GRBALPHABET[size = psize];		//цепочка терминалов
		int* p = (int*)&s;						 //присваиваем символ указателю п
		for (short i = 0; i < psize; ++i)
			nt[i] = (GRBALPHABET)p[i];			//заполняем цепочку терминалов
	}

	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...)		//конструктор правила
	{				//(нетерминал, идентификатор диагностического сообщения, количество цепочек(правых частей правила), множество цепочек (правых частей правила)
		nn = pnn;				//нетерминал
		iderror = piderror;		//идентификатор
		chains = new Chain[size = psize];	//место для цепочки
		Chain* p = &c;						
		for (int i = 0; i < size; ++i)
			chains[i] = p[i];			//заполняем множество цепочек
	}

	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottom, short psize, Rule r, ...)
	{				//конструктор гграматики Грейбаха(стартовый символ, дно стека, количество правил, правила...)
		startN = pstartN;		//стартовый символ
		stbottomT = pstbottom;	//дно стека
		rules = new Rule[size = psize];	//выделяем память
		Rule* p = &r;					
		for (int i = 0; i < size; ++i)	//заполняем правила
			rules[i] = p[i];	
	}

	Greibach getGreibach()			//получить грамматику
	{
		return greibach;
	}

	short Greibach::getRule(GRBALPHABET pnn, Rule& prule)	//получить правило (левый символ правила, возвращаемое правило грамматики)
	{
		short rc = -1;
		short k = 0;
		while (k < size && rules[k].nn != pnn)
			++k;			//пока К меньше количества правил и пока левый символ правила не равен парметру ф-ции
		if (k < size)
			prule = rules[rc = k];		//возвращаемое правило граматики равно правилу с индексом К
		_ASSERT(rc != -1);
		return rc;						//возвращается номер правила или -1
	}

	Rule Greibach::getRule(short n)		//получить правило по номеру
	{
		Rule rc;						//создаём правило рц
		if (n < size)					
			rc = rules[n];				 //присваиваем правилу рц правило н
		return rc;						 //возвращаем созданное правило
	}

	char* Rule::getCRule(char* b, short nchain)	  //получить правило в виде N->цепочка (буфер, номер цепочки(правой части) в правиле)
	{
		char bchain[200];						   //строка
		b[0] = Chain::alphabet_to_char(nn);			//терминал -> 
		b[1] = '-';
		b[2] = '>';
		b[3] = 0x00;
		chains[nchain].getCChain(bchain);			//получает правую сторонц правила
		strcat_s(b, sizeof(bchain) + 5, bchain);	//добавляем строку (куда, с какого элемента, строку)
		return b;
	}

	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j)  //получить следующую за j подходящую цепочку, вернуть её номер или -1 
	{												  //(первый символ цепочки, возвращаемая цепочка, номер цепочки)
		short rc = -1;
		while (j < size && chains[j].nt[0] != t)
			++j;
		rc = (j < size ? j : -1);
		if (rc >= 0)
			pchain = chains[rc];
		return rc;
	}

	char* Rule::Chain::getCChain(char* b)				 //получить правую сторону правила
	{
		for (int i = 0; i < size; ++i)
			b[i] = Chain::alphabet_to_char(nt[i]);
		b[size] = 0x00;
		return b;
	}
}