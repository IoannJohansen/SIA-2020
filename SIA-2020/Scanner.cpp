#include "stdafx.h"
#include "Scanner.h"
#include <stack>
namespace Scanner
{
	stack<char*> block;
	bool flPar = false;
	bool libFoo = false;
	bool flMain = false;

	Words* TextDivision(In::IN in)
	{
		Words* words = new Words();
		Word entry;
		char buff[IN_MAX_LEN_TEXT];
		int buffPosition = 0;
		int line = 0;
		for (int i = 0, posInLine = 0; i < in.size; posInLine++)
		{
			switch (in.code[in.text[i]])
			{
			case In::IN::T:
			{
				while (in.code[in.text[i]] == In::IN::T)
				{
					buff[buffPosition++] = in.text[i++];
				}
				FILLWORD
				break;
			}

			case In::IN::S: {if (in.text[i++] == IN_CODE_ENDL) { line++; posInLine = 0; }break; }

			case In::IN::B:
			case In::IN::V:
			{
				buff[buffPosition++] = in.text[i++];
				FILLWORD
				break;
			}

			case In::IN::Q:
			{
				buff[buffPosition++] = in.text[i++];
				do
				{
					if (in.code[in.text[i]] == In::IN::E)throw ERROR_THROW_IN(128, line, -1);
					buff[buffPosition++] = in.text[i];
				} while (in.code[in.text[i++]] != In::IN::Q);
				FILLWORD
				break;
			}

			}
		}
		return words;
	}
	Tables GetTables(Words* words)
	{
		Tables table;
		IT::Entry tempIT;
		block.push((char*)TI_BLOCK_DEFAULT);
		table.idenTable = IT::Create(TI_MAXSIZE);
		table.lexTable = LT::Create(TI_MAXSIZE);
		char* lex = (char*)"";
		int arrSize = words->arr.size();
		for (int i = 0; i < arrSize; i++)
		{	
			lex = words->arr.front().token;
			char j = Analysis(lex, &table);
			if (j == '\0')
			{
				if (CheckForIntegerLiteral(words))
				{
					int refInID = IT::IsId(table.idenTable, block.top(), IT::IDDATATYPE::INT, lex);
					LT::Add(table.lexTable, AddLex(LEX_LITERAL, words, refInID, &table.idenTable));
					tempIT.idtype = IT::L;
					tempIT.iddatatype = IT::INT;
					if (refInID==TI_NULLIDX)
					{
						AddID(lex, &table, tempIT);
					}
				}
				else if (CheckForStringLiteral(words))
				{
					int refInID = IT::IsId(table.idenTable, block.top(), IT::IDDATATYPE::STR, lex);
					LT::Add(table.lexTable, AddLex(LEX_LITERAL, words, refInID, &table.idenTable));
					tempIT.idtype = IT::L;
					tempIT.iddatatype = IT::STR;
					if (refInID == TI_NULLIDX)
					{
						AddID(lex, &table, tempIT);
					}
				}
				else if (CheckId(words))
				{
					int refInID = IT::IsId(table.idenTable, lex, block.top());
					LT::Add(table.lexTable, AddLex(LEX_ID, words, refInID, &table.idenTable));
					if (refInID == TI_NULLIDX)
					{

						if (!(CHECKFORDECLARE) && !flPar && !(LIBFOO))throw ERROR_THROW_IN(126, LINE, SYM);		// using of undeclared id
						if (!strcmp(block.top(), TI_BLOCK_DEFAULT) && (tempIT.idtype != IT::F || table.lexTable.table[table.lexTable.size-4].lexema==LEX_CREATE))throw ERROR_THROW_IN(129, LINE, SYM);
						AddID(lex, &table, tempIT);
					}
				}
			}
			else
			{
				AnalysisItString(&tempIT, j, words);
				
				if ((strcmp(lex, "stringLen") == 0) || (strcmp(lex, "lexStrCmp") == 0))
				{
					if (IT::IsId(table.idenTable, lex) == TI_NULLIDX)AddID(lex, &table, tempIT);
				}
				LT::Add(table.lexTable, AddLex(j, words, -2, &table.idenTable));
			}
			words->arr.pop_front();
		}
		if (!flMain)throw ERROR_THROW(124);
		return table;
	}
	void AddID(char* token, Tables* tables, IT::Entry tempIT)
	{
		if (flPar)
		{
			if (!(CHECKPARM))throw ERROR_THROW_IN(127, LEXLINE, LEXPOS);		// bad declaration of parms
			tempIT.idtype = IT::P;
		}
		if (tempIT.idtype != IT::L)
			strcpy_s(tempIT.id, token);
		else
			strcpy_s(tempIT.id, "-");

		tempIT.idxfirstLE = tables->lexTable.size-1;
		strcpy_s(tempIT.parrentBlock, block.top());
		
		switch (tempIT.iddatatype)
		{

		case IT::INT:
		{
			if (tempIT.idtype!=IT::L)
			{
				tempIT.value.vint = TI_INT_DEFAULT;

			}
			else
			{
				tempIT.value.vint = atoi(token);
			}
			break;
		}
		case IT::STR:
		{
			if (tempIT.idtype != IT::L)
			{
				tempIT.value.vstr.str[0] = TI_STR_DEFAULT;
				tempIT.value.vstr.len = 0;
			}
			else
			{
				strcpy(tempIT.value.vstr.str, token);
				tempIT.value.vstr.len = strlen(token);
			}
			break;
		}

		}
		IT::Add(tables->idenTable, tempIT);
		if (tempIT.idtype == IT::F && (strcmp(tempIT.id, "stringLen") != 0) && (strcmp(tempIT.id, "lexStrCmp") != 0))
		{
			block.push(tables->idenTable.table[tables->idenTable.size-1].id);
		}
	}
	char CheckForArithmAndBrack(char* lexem, Tables* tables)
	{
		switch (lexem[0])
		{
		
		case LEX_OPEN_PROC:
		case LEX_CLOSE_PROC:
		case LEX_COMMA:
		case LEX_EQUAL_SIGN:
		case LEX_LEFTBRACE:
		case LEX_RIGHTBRACE:
			return lexem[0];
		case LEX_SEMICOLON:
		{
			if (tables->lexTable.table[tables->lexTable.size-1].lexema == LEX_CLOSE_PROC)
			{
				int brBalance = 1;
				for (int i = tables->lexTable.size-2; i != -1; i--)
				{
					switch (tables->lexTable.table[i].lexema)
					{
					case LEX_OPEN_PROC: {brBalance--; break; }
					case LEX_CLOSE_PROC: {brBalance++; break; }
					}
				}
				if (brBalance != 0)throw ERROR_THROW_IN(116, LEXLINE, LEXPOS);		// invalid bracket balance
				block.pop();
			}
			return LEX_SEMICOLON;
		}
		case LEX_LESS:
		case LEX_MORE:
		case LEX_MODULO:
		case LEX_PLUS:
		case LEX_MINUS:
		case LEX_STAR:
		case LEX_DIRSLASH:
		{
			IT::Entry tempIT;
			tempIT.id[0] = lexem[0];
			tempIT.id[1] = '\0';
			tempIT.idxfirstLE = tables->lexTable.size;
			IT::Add(tables->idenTable, tempIT);
			return LEX_ARITHMETIC;
		}

		case LEX_LEFTHESIS:
		{
			if (VARPARM)
			{
				flPar = true;
			}
			return LEX_LEFTHESIS;
		}

		case LEX_RIGHTHESIS:
		{
			if(flPar)flPar = false;
			return LEX_RIGHTHESIS;
		}

		default: return '\0';

		}

	}
	void AnalysisItString(IT::Entry* tempIT, char& lexem, Words* words)
	{
		switch (lexem)
		{
		
		case LEX_STRCMP:
		{
			tempIT->idtype = IT::IDTYPE::F;
			strcpy_s(tempIT->parrentBlock, TI_BLOCK_DEFAULT);
			tempIT->iddatatype = IT::IDDATATYPE::INT;
			break;
		}

		case LEX_STRLEN:
		{
			tempIT->idtype = IT::IDTYPE::F;
			strcpy_s(tempIT->parrentBlock, TI_BLOCK_DEFAULT);
			tempIT->iddatatype = IT::IDDATATYPE::INT;
			break;	
		}

		case LEX_CREATE:
		{
			tempIT->idtype = IT::IDTYPE::V;
			break;
		}

		case LEX_PROC:
		{
			tempIT->idtype = IT::IDTYPE::F;
			break;
		}

		case LEX_WORD:
		{
			tempIT->iddatatype = IT::STR;
			lexem = LEX_TYPE;
			break;
		}

		case LEX_NUM:
		{
			tempIT->iddatatype = IT::INT;
			lexem = LEX_TYPE;
			break;
		}

		case LEX_ENTRY:
		{
			if (flMain)throw ERROR_THROW_IN(125, LINE, SYM);		// check for multiply declaration of entry point
			flMain = true;
			block.push((char*)TI_BLOCK_MAIN);
			strcpy_s(tempIT->parrentBlock, block.top());
			break;
		}

		default:
			break;
		}


	}
	char Analysis(char* lex, Tables* tables)
	{
		char resLex[FST_COUNT] = { LEX_CREATE , LEX_NUM , LEX_WORD, LEX_PROC, LEX_ENTRY, LEX_OUTSTREAM , LEX_OUT, LEX_IF, LEX_ELSE, LEX_STRCMP, LEX_STRLEN};

		FST::FST tokens[FST_COUNT] = { FST::FST(lex, A_CREATE), FST::FST(lex, A_NUM), FST::FST(lex,A_WORD), FST::FST(lex, A_PROC), FST::FST(lex, A_ENTRY), FST::FST(lex, A_OUTSTREAM), FST::FST(lex, A_OUT), FST::FST(lex, A_IF), FST::FST(lex, A_ELSE), FST::FST(lex, A_STRCMP), FST::FST(lex, A_STRLEN) };

		for (int i = 0; i < FST_COUNT; i++)
		{
			if (FST::execute(tokens[i]))
			{
				return resLex[i];
			}
		}

		return CheckForArithmAndBrack(lex, tables);
	}
	bool CheckForStringLiteral(Words* words)
	{
		char* lex = words->arr.front().token;
		if (lex[0] == '\'')
		{
			if (strlen(lex) > TI_STR_MAXSIZE)throw ERROR_THROW_IN(120, LINE, SYM);		// too long len of literal
			return true;
		}
		return false;
	}
	bool CheckForIntegerLiteral(Words* words)
	{
		char* lex = words->arr.front().token;
		for (int i = 0; i < strlen(lex); i++)
		{
			if (lex[i] < '0' || lex[i] > '9')return false;			// TODO: написать error
		}
		if ((atoi(lex) > pow(2, 31)) || (atoi(lex) < pow(-2, 31)))throw ERROR_THROW_IN(123, LINE, SYM); // too big value int literal
		return true;
	}
	bool CheckId(Words* words)
	{
		char* lex = words->arr.front().token;
		int len = strlen(lex);
		if (len > ID_MAXSIZE)throw ERROR_THROW_IN(121, LINE, SYM);							// too long id len
		for (int i = 0; i < len; i++)
		{
			if (lex[i] < 'a' || lex[i] > 'z') 
			{
				if (lex[i] == 'S' || lex[i] == 'L' || lex[i] == 'C')continue;
				throw ERROR_THROW_IN(122, LINE, SYM);										// bad char in id
			}
		}

		return true;
	}
	LT::Entry AddLex(char lex, Words* words, int refID, IT::IdTable* idenTable)
	{
		LT::Entry temp;
		temp.lexema = lex;
		temp.sn = LINE;
		temp.posInStr = SYM;

		switch (refID)
		{

		case LT_TI_NULLXDX:
		{
			temp.idxTI = idenTable->size;
			break;
		}

		case -2:
		{
			temp.idxTI = LT_TI_NULLXDX;
			break;
		}

		default:
		{
			temp.idxTI = refID;
			break;
		}

		}
		
		if (temp.lexema == LEX_ARITHMETIC)temp.idxTI = idenTable->size - 1;
		return temp;
	}
}