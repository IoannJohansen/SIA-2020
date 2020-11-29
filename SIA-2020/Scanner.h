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
				tables->lexTable.table[tables->lexTable.size-2].lexema==LEX_FUNCTION

#define LIBFOO tables->lexTable.table[tables->lexTable.size-1].lexema == LEX_ID && tables->lexTable.table[tables->lexTable.size-2].lexema == LEX_FUNCTION &&\
			   tables->lexTable.table[tables->lexTable.size-3].lexema == LEX_TYPE && tables->lexTable.table[tables->lexTable.size-4].lexema == LEX_DECLARE

#define CHECKFORDECLARE (table.lexTable.table[table.lexTable.size-3].lexema==LEX_TYPE && table.lexTable.table[table.lexTable.size-2].lexema==LEX_FUNCTION ) ||\
	(table.lexTable.table[table.lexTable.size-2].lexema==LEX_TYPE && table.lexTable.table[table.lexTable.size-3].lexema==LEX_DECLARE ) || \
	(table.lexTable.table[table.lexTable.size-2].lexema==LEX_FUNCTION && table.lexTable.table[table.lexTable.size-3].lexema==LEX_TYPE &&\
 table.lexTable.table[table.lexTable.size-4].lexema==LEX_DECLARE)

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

#define FST_COUNT 7

#define A_FUNCTION 9,			  \
			FST::NODE(1, FST::RELATION('f', 1)),  \
			FST::NODE(1, FST::RELATION('u', 2)),  \
			FST::NODE(1, FST::RELATION('n', 3)),  \
			FST::NODE(1, FST::RELATION('c', 4)),  \
			FST::NODE(1, FST::RELATION('t', 5)),  \
			FST::NODE(1, FST::RELATION('i', 6)),  \
			FST::NODE(1, FST::RELATION('o', 7)),  \
			FST::NODE(1, FST::RELATION('n', 8)),  \
			FST::NODE()		

#define A_INTEGER 8,\
			FST::NODE(1, FST::RELATION('i', 1)),\
			FST::NODE(1, FST::RELATION('n', 2)),\
			FST::NODE(1, FST::RELATION('t', 3)),\
			FST::NODE(1, FST::RELATION('e', 4)),\
			FST::NODE(1, FST::RELATION('g', 5)),\
			FST::NODE(1, FST::RELATION('e', 6)),\
			FST::NODE(1, FST::RELATION('r', 7)),\
			FST::NODE()

#define A_DECLARE 8,\
			FST::NODE(1, FST::RELATION('d', 1)),\
			FST::NODE(1, FST::RELATION('e', 2)),\
			FST::NODE(1, FST::RELATION('c', 3)),\
			FST::NODE(1, FST::RELATION('l', 4)),\
			FST::NODE(1, FST::RELATION('a', 5)),\
		    FST::NODE(1, FST::RELATION('r', 6)),\
			FST::NODE(1, FST::RELATION('e', 7)),\
			FST::NODE()

#define A_RETURN 7,\
			FST::NODE(1, FST::RELATION('r', 1)),\
			FST::NODE(1, FST::RELATION('e', 2)),\
			FST::NODE(1, FST::RELATION('t', 3)),\
			FST::NODE(1, FST::RELATION('u', 4)),\
			FST::NODE(1, FST::RELATION('r', 5)),\
			FST::NODE(1, FST::RELATION('n', 6)),\
			FST::NODE()


#define A_STRING 7,				  \
			FST::NODE(1, FST::RELATION('s', 1)),  \
			FST::NODE(1, FST::RELATION('t', 2)),  \
			FST::NODE(1, FST::RELATION('r', 3)),  \
			FST::NODE(1, FST::RELATION('i', 4)),  \
			FST::NODE(1, FST::RELATION('n', 5)),  \
			FST::NODE(1, FST::RELATION('g', 6)),  \
			FST::NODE()	

#define A_PRINT 6,				  \
			FST::NODE(1, FST::RELATION('p', 1)),  \
			FST::NODE(1, FST::RELATION('r', 2)),  \
			FST::NODE(1, FST::RELATION('i', 3)),  \
			FST::NODE(1, FST::RELATION('n', 4)),  \
			FST::NODE(1, FST::RELATION('t', 5)),  \
			FST::NODE()

#define A_MAIN 5,\
	FST::NODE(1, FST::RELATION('m', 1)),\
	FST::NODE(1, FST::RELATION('a', 2)),\
	FST::NODE(1, FST::RELATION('i', 3)),\
	FST::NODE(1, FST::RELATION('n', 4)),\
	FST::NODE()

#pragma endregion

	
}