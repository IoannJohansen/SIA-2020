#include "stdafx.h"
#include "LT.h"
#include "Error.h"
#include <fstream>

namespace LT {
	LexTable Create(int size)
	{
		LexTable* New = new LexTable;
		New->maxsize = size;
		New->size = 0;
		New->table = new Entry[size];
		memset(New->table, 0xff, sizeof(Entry) * size);
		return *New;
	}

	void Add(LexTable& lextable, Entry entry)
	{
		if (lextable.size == lextable.maxsize) throw ERROR_THROW(117);		// lextable overflow
		lextable.table[lextable.size++] = entry;
	}

	Entry GetEntry(LexTable& lextable, int n)
	{
		return lextable.table[n];
	}

	void LT::LexTable::writeLT(const wchar_t* in) 
	{
		int i = 0;
		wchar_t Scanner[300];
		for (; in[i] != '\0'; i++)
			Scanner[i] = in[i];
		Scanner[i] = '\0';
		wcscat_s(Scanner, PARM_LEX_DEFAULT_EXT);
		std::ofstream* lexStream = new std::ofstream;
		lexStream->open(Scanner);
		if (!lexStream->is_open())
		{
			throw ERROR_THROW(119);		// error of creating lt file
		}
		//----------------------------------------------------

		cout << "№\t" << "Scanner\t" << endl;
		for (int i = 0; i < this->size ; i++)
		{
			cout << i << '\t' << this->table[i].lexema << "		|		" << this->table[i].idxTI << "		|		"  << endl;
		}

		//----------------------------------------------------
		*lexStream << "\tТаблица лексем" << endl;
		*lexStream << "---------------------" << endl;
		if (lexStream->is_open())
		{
			int currentString = 0;
			(*lexStream) << '\n' << currentString + 1 << '\t';
			for (int i = 0; i < this->size;)
			{
				if (currentString == this->table[i].sn)
				{
					(*lexStream) << this->table[i++].lexema;
					
				}
				else
				{
					(*lexStream) << '\n' << currentString++ + 2 << '\t';

					//if (currentString == this->table[i].sn)
					//{
					//	(*lexStream) << this->table[i].lexema;
					//	if (this->table[i - 1].idxTI != -1)(*lexStream) << '<' << this->table[i-1].idxTI << '>';
					//}
					//i++;
				}
			}
		}
		else
			throw ERROR_THROW(125);
		lexStream->close();
		delete lexStream;
	}

	void Delete(LexTable& lextable)
	{
		delete[] lextable.table;
		lextable = {};
	}
}