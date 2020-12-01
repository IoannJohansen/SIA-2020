#pragma once
#include "stdafx.h"
#include "LT.h"
#include "IT.h"
#include <list>

#define FILLWORD buff[buffPosition] = '\0';\
				 buffPosition = 0;\
				 strcpy_s(entry.token, buff); \
				 entry.line = line; \
				 entry.symInLine = posInLine;\
				 words->Add(entry);
				
#define VARPARM tables->lexTable.table[tables->lexTable.size-1].lexema==LEX_ID &&\
				tables->idenTable.table[tables->lexTable.table[tables->lexTable.size-1].idxTI].idtype==IT::F &&\
				tables->lexTable.table[tables->lexTable.size-2].lexema==LEX_PROC

#define LIBFOO table.lexTable.table[table.lexTable.size-3].lexema == LEX_STRLEN || table.lexTable.table[table.lexTable.size-3].lexema == LEX_STRCMP || table.lexTable.table[table.lexTable.size-5].lexema == LEX_STRCMP


#define CHECKFORDECLARE (table.lexTable.table[table.lexTable.size-3].lexema==LEX_TYPE && table.lexTable.table[table.lexTable.size-2].lexema==LEX_PROC ) ||\
	(table.lexTable.table[table.lexTable.size-2].lexema==LEX_TYPE && table.lexTable.table[table.lexTable.size-3].lexema==LEX_CREATE ) || \
	(table.lexTable.table[table.lexTable.size-2].lexema==LEX_PROC && table.lexTable.table[table.lexTable.size-3].lexema==LEX_TYPE &&\
 table.lexTable.table[table.lexTable.size-4].lexema==LEX_CREATE)

#define CHECKPARM (tables->lexTable.table[tables->lexTable.size-2].lexema==LEX_TYPE) &&\
 (tables->lexTable.table[tables->lexTable.size-3].lexema==LEX_COMMA || tables->lexTable.table[tables->lexTable.size-3].lexema==LEX_LEFTHESIS)

#define LINE words->arr.front().line

#define SYM words->arr.front().symInLine

#define LEXLINE tables->lexTable.table[tables->lexTable.size-1].sn

#define LEXPOS tables->lexTable.table[tables->lexTable.size-1].posInStr

namespace Scanner 
{


	struct Tables
	{
		LT::LexTable lexTable;
		IT::IdTable idenTable;
	};

	struct Word
	{
		char token[257];
		int line;
		int symInLine;
	};

	class Words
	{
	public:
		list<Word> arr;
		void Add(Word entry) 
		{
			arr.push_back(entry);
		}
		void Delete()
		{
			arr.pop_front();
		}
	};

	Words* TextDivision(In::IN in);
	Tables GetTables(Words* words);
	char Analysis(char* lex, Tables* tables);
	bool CheckForStringLiteral(Words* words);
	bool CheckForIntegerLiteral(Words* words);
	bool CheckId(Words* words);
	LT::Entry AddLex(char lex, Words* words, int refID, IT::IdTable* idenTable);
	void AnalysisItString(IT::Entry* tempIT, char& lexem,Words* words);
	char CheckForArithmAndBrack(char* lexem, Tables* table);
	void AddID(char* token, Tables* tables, IT::Entry tempIT);



#pragma region FSTs

#define FST_COUNT 11

#define A_PROC 5,			  \
			FST::NODE(1, FST::RELATION('p', 1)),  \
			FST::NODE(1, FST::RELATION('r', 2)),  \
			FST::NODE(1, FST::RELATION('o', 3)),  \
			FST::NODE(1, FST::RELATION('c', 4)),  \
			FST::NODE()		

#define A_NUM 4,\
			FST::NODE(1, FST::RELATION('n', 1)),\
			FST::NODE(1, FST::RELATION('u', 2)),\
			FST::NODE(1, FST::RELATION('m', 3)),\
			FST::NODE()

#define A_CREATE 7,\
			FST::NODE(1, FST::RELATION('c', 1)),\
			FST::NODE(1, FST::RELATION('r', 2)),\
			FST::NODE(1, FST::RELATION('e', 3)),\
			FST::NODE(1, FST::RELATION('a', 4)),\
			FST::NODE(1, FST::RELATION('t', 5)),\
		    FST::NODE(1, FST::RELATION('e', 6)),\
			FST::NODE()

#define A_OUT 4,\
			FST::NODE(1, FST::RELATION('o', 1)),\
			FST::NODE(1, FST::RELATION('u', 2)),\
			FST::NODE(1, FST::RELATION('t', 3)),\
			FST::NODE()


#define A_WORD 5,				  \
			FST::NODE(1, FST::RELATION('w', 1)),  \
			FST::NODE(1, FST::RELATION('o', 2)),  \
			FST::NODE(1, FST::RELATION('r', 3)),  \
			FST::NODE(1, FST::RELATION('d', 4)),  \
			FST::NODE()	

#define A_OUTSTREAM 10,				  \
			FST::NODE(1, FST::RELATION('o', 1)),  \
			FST::NODE(1, FST::RELATION('u', 2)),  \
			FST::NODE(1, FST::RELATION('t', 3)),  \
			FST::NODE(1, FST::RELATION('S', 4)),  \
			FST::NODE(1, FST::RELATION('t', 5)),  \
			FST::NODE(1, FST::RELATION('r', 6)),  \
			FST::NODE(1, FST::RELATION('e', 7)),  \
			FST::NODE(1, FST::RELATION('a', 8)),  \
			FST::NODE(1, FST::RELATION('m', 9)),  \
			FST::NODE()

#define A_ENTRY 6,					\
			FST::NODE(1, FST::RELATION('e', 1)),\
			FST::NODE(1, FST::RELATION('n', 2)),\
			FST::NODE(1, FST::RELATION('t', 3)),\
			FST::NODE(1, FST::RELATION('r', 4)),\
			FST::NODE(1, FST::RELATION('y', 5)),\
			FST::NODE()

#define A_IF 3,\
			FST::NODE(1, FST::RELATION('i', 1)),\
			FST::NODE(1, FST::RELATION('f', 2)),\
			FST::NODE()

#define A_ELSE 5,\
			FST::NODE(1, FST::RELATION('e', 1)),\
			FST::NODE(1, FST::RELATION('l', 2)),\
			FST::NODE(1, FST::RELATION('s', 3)),\
			FST::NODE(1, FST::RELATION('e', 4)),\
			FST::NODE()

	
#define A_STRCMP 10,\
			FST::NODE(1, FST::RELATION('l', 1)),\
			FST::NODE(1, FST::RELATION('e', 2)),\
			FST::NODE(1, FST::RELATION('x', 3)),\
			FST::NODE(1, FST::RELATION('S', 4)),\
			FST::NODE(1, FST::RELATION('t', 5)),\
			FST::NODE(1, FST::RELATION('r', 6)),\
			FST::NODE(1, FST::RELATION('C', 7)),\
			FST::NODE(1, FST::RELATION('m', 8)),\
			FST::NODE(1, FST::RELATION('p', 9)),\
			FST::NODE()

#define A_STRLEN 10,\
			FST::NODE(1, FST::RELATION('s', 1)),\
			FST::NODE(1, FST::RELATION('t', 2)),\
			FST::NODE(1, FST::RELATION('r', 3)),\
			FST::NODE(1, FST::RELATION('i', 4)),\
			FST::NODE(1, FST::RELATION('n', 5)),\
			FST::NODE(1, FST::RELATION('g', 6)),\
			FST::NODE(1, FST::RELATION('L', 7)),\
			FST::NODE(1, FST::RELATION('e', 8)),\
			FST::NODE(1, FST::RELATION('n', 9)),\
			FST::NODE()

#pragma endregion

	
}