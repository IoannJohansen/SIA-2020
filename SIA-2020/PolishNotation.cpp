#include "stdafx.h"

namespace PN
{
	void PolishNotation(Scanner::Tables& tables)
	{
		Pos pos;
		for (int i = 0; i < tables.lexTable.size; i++)
		{
			if (SEARCHEXPR)
			{
				cout << "Expr finded" << endl;
				pos.startEx = ++i;
				GetExrp(tables.lexTable, pos);
				ShiftAndWriteLT(tables, &pos, Convertation(pos, &tables.idenTable));
			}
		}
	}

	void GetExrp(LT::LexTable lexTable, Pos& pos)
	{
		LT::Entry* expr = nullptr;
		for (pos.endEx = pos.startEx; lexTable.table[pos.endEx].lexema != LEX_SEMICOLON; pos.endEx++);
		expr = new LT::Entry[pos.endEx - pos.startEx];
		for (int i = pos.startEx, j = 0; i < pos.endEx; i++, j++)
		{
			expr[j] = lexTable.table[i];
		}
		pos.express = expr;
	}

	int Convertation(Pos& pos, IT::IdTable* idenTable)
	{
		stack<LT::Entry> stack;
		int len = pos.endEx - pos.startEx;
		LT::Entry* arr = new LT::Entry[len];
		int countComma = 0;
		int brBalance = 0;
		int j = 0;
		for (int i = 0; i < len; i++)
		{
			switch (pos.express[i].lexema)
			{
				case LEX_ID:
				case LEX_LITERAL:
				{
					arr[j++] = pos.express[i];
					break;
				}

				case LEX_ARITHMETIC:
				{
					if (stack.empty() || stack.top().lexema==LEX_LEFTHESIS)
					{
						stack.push(pos.express[i]);
						break;
					}

					if (ArithmPrioritys(pos.express[i], idenTable)<= ArithmPrioritys(stack.top(), idenTable))
					{
						while(!stack.empty()&&ArithmPrioritys(pos.express[i], idenTable) <= ArithmPrioritys(stack.top(), idenTable))
						{
							arr[j++] = stack.top();
							stack.pop();
						}
					}
					stack.push(pos.express[i]);

					break;
				}

				case LEX_COMMA:
				{
					countComma++;
					if (ArithmPrioritys(pos.express[i], idenTable) < ArithmPrioritys(stack.top(), idenTable))
					{
						do
						{
							arr[j++] = stack.top();
							stack.pop();
						} while (ArithmPrioritys(pos.express[i], idenTable) < ArithmPrioritys(stack.top(), idenTable));
					}
					break;
				}

				case LEX_LEFTHESIS:
				{
					stack.push(pos.express[i]);
					break;
				}

				case LEX_RIGHTHESIS:
				{
					int k = i;
					for (; k != 0; k--)
					{
						if (pos.express[k].lexema == LEX_LEFTHESIS)
						{
							brBalance--;
							if (idenTable->table[pos.express[k - 1].idxTI].idtype == IT::F && brBalance==0)
							{
								arr[j].lexema = '@';
								arr[j].sn = pos.express[k].sn;
								arr[j++].idxTI = ++countComma;
								countComma = 0;
							}
						
						}
						else if (pos.express[k].lexema == LEX_RIGHTHESIS)brBalance++;

					}
					brBalance = 0;
					while(stack.top().lexema!=LEX_LEFTHESIS)
					{
						arr[j++] = stack.top();
						stack.pop();
					}
					stack.pop();
					break;
				}
			}

		}
		while (!stack.empty())
		{
			arr[j++] = stack.top();
			stack.pop();
		}
		LT::Entry* resStr = new LT::Entry[j];
		for (int i = 0; i < j; i++)
		{
			resStr[i] = arr[i];
		}
		delete[] arr;
		delete[] pos.express;
		pos.express = resStr;
		return j;
	}

	short ArithmPrioritys(LT::Entry str, IT::IdTable* idenTable)
	{
		switch (str.lexema)
		{

			case LEX_LEFTHESIS:
			case LEX_RIGHTHESIS:
			{
				return 1;
			}

			case LEX_COMMA:
			{
				return 2;
			}

			case LEX_ARITHMETIC:
			{
				if (idenTable->table[str.idxTI].id[0] == LEX_PLUS || idenTable->table[str.idxTI].id[0] == LEX_MINUS)
					return 3;
				else if (idenTable->table[str.idxTI].id[0] == LEX_STAR || idenTable->table[str.idxTI].id[0] == LEX_DIRSLASH)
					return 4;
			}
		
		
		}
		return 0;
	}

	void ShiftAndWriteLT(Scanner::Tables& tables, Pos* pos, int newLen)
	{
		for (int i = pos->startEx, j = 0; j < newLen; i++, j++)
		{
			tables.lexTable.table[i] = pos->express[j];
			if (tables.lexTable.table[i].lexema == LEX_ID || tables.lexTable.table[i].lexema == LEX_LITERAL)
			{
				tables.idenTable.table[tables.lexTable.table[i].idxTI].idxfirstLE = i;
			}
		}


		for (int i = pos->endEx - (pos->startEx + newLen), j = 0; j < i; j++)
		{
			for (int k = pos->startEx+newLen; k < tables.lexTable.size; k++)
			{
				tables.lexTable.table[k] = tables.lexTable.table[k + 1];
				if (tables.lexTable.table[k].lexema == LEX_ID || tables.lexTable.table[k].lexema == LEX_LITERAL)
				{
					tables.idenTable.table[tables.lexTable.table[k].idxTI].idxfirstLE = k;
				}
			}
			tables.lexTable.size--;
		}



	}

}