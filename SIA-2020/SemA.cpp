#include "SemA.h"

namespace Semantic
{
	void SemanticAnalysis(Scanner::Tables* tables)
	{
		Functions functions = Create(255);
		CheckTypesMapping(tables);
		CheckCondAndStreams(tables->lexTable, tables->idenTable);
		FillFunction(functions, tables->idenTable);
		CheckFuncitionParams(functions, *tables);
		CheckBuiltInFunParam(tables->lexTable, tables->idenTable);
		CheckForReturnType(tables->lexTable, tables->idenTable);
		cout << "Semantic analysis done" << endl;
	}

	void CheckTypesMapping(Scanner::Tables* tables)
	{	

		for (int i = 0; i < tables->lexTable.size; i++)
		{
			if (tables->lexTable.table[i].lexema==LEX_EQUAL_SIGN)
			{
				if (tables->idenTable.table[tables->lexTable.table[i - 1].idxTI].idtype != IT::V && tables->idenTable.table[tables->lexTable.table[i - 1].idxTI].idtype != IT::P)throw ERROR_THROW_IN(SEM_ERROR_SIRES + 0, tables->lexTable.table[i - 1].sn, 0);		// bad lvalue

				IT::IDDATATYPE type = tables->idenTable.table[tables->lexTable.table[i - 1].idxTI].iddatatype;

				switch (type)
				{

				case IT::STR:
				{
					for (int j = 0; tables->lexTable.table[i + j].lexema != LEX_SEMICOLON; j++)
					{
						if (tables->lexTable.table[i + j].lexema == LEX_ARITHMETIC)	// sign in expr with str
						{
							throw ERROR_THROW_IN(SEM_ERROR_SIRES + 1, tables->lexTable.table[i + j].sn, 0);
						}

						if (tables->lexTable.table[i + j].lexema == LEX_ID || tables->lexTable.table[i + j].lexema == LEX_LITERAL || tables->lexTable.table[i + j].lexema == LEX_STRCMP || tables->lexTable.table[i + j].lexema == LEX_STRLEN)//!
						{
							if (tables->idenTable.table[tables->lexTable.table[i + j].idxTI].idtype == IT::F)
							{
								if (tables->idenTable.table[tables->lexTable.table[i + j].idxTI].iddatatype != type)
								{
									throw ERROR_THROW_IN(SEM_ERROR_SIRES + 3, tables->lexTable.table[i + j].sn, 0);
								}
								if (tables->lexTable.table[i + j + 1].lexema != LEX_LEFTHESIS)
								{
									throw ERROR_THROW_IN(SEM_ERROR_SIRES + 2, tables->lexTable.table[i + j].sn, 0);									// bad call of func
								}

								int countOfHesis = 0;
								do
								{
									j++;
									if (tables->lexTable.table[i + j].lexema == LEX_LEFTHESIS)
										countOfHesis++;
									if (tables->lexTable.table[i + j].lexema == LEX_RIGHTHESIS)
										countOfHesis--;
								} while (countOfHesis != 0);

							}
							else if (tables->idenTable.table[tables->lexTable.table[i + j].idxTI].iddatatype != type)
							{
								throw ERROR_THROW_IN(SEM_ERROR_SIRES + 3, tables->lexTable.table[i + j].sn, 0);
							}			// Unaccording types in expr
						}
					}
					break;
				}

				case IT::INT:
				{
					int index = 0;
					while (tables->lexTable.table[i + index].lexema != LEX_SEMICOLON)
					{
						if (tables->lexTable.table[i + index].lexema == LEX_LESS || tables->lexTable.table[i + index].lexema == LEX_MORE)
						{
							throw ERROR_THROW_IN(SEM_ERROR_SIRES + 4, tables->lexTable.table[i + index].sn, 0);
						}					// using >< in expr without if

						if (tables->lexTable.table[i + index].lexema == LEX_LITERAL || tables->lexTable.table[i + index].lexema == LEX_ID || tables->lexTable.table[i + index].lexema == LEX_STRCMP || tables->lexTable.table[i + index].lexema == LEX_STRLEN)
						{
							if (tables->idenTable.table[tables->lexTable.table[i + index].idxTI].idtype == IT::IDTYPE::F)
							{
								if (tables->idenTable.table[tables->lexTable.table[i + index].idxTI].iddatatype != type)
								{
									throw ERROR_THROW_IN(SEM_ERROR_SIRES + 3, tables->lexTable.table[i + index].sn, 0);	   // unAccordong of types in express
								}
								if (tables->lexTable.table[i + index + 1].lexema != LEX_LEFTHESIS)
									throw ERROR_THROW_IN(SEM_ERROR_SIRES + 2, tables->lexTable.table[i + index].sn, 0);	// call withou ()

								int countOfHesis = 0;
								do
								{
									index++;
									if (tables->lexTable.table[i + index].lexema == LEX_LEFTHESIS)
										countOfHesis++;
									if (tables->lexTable.table[i + index].lexema == LEX_RIGHTHESIS)
										countOfHesis--;

								} while (countOfHesis != 0);

							}
							else if (tables->lexTable.table[i + index].lexema == LEX_STRCMP || tables->lexTable.table[i + index].lexema == LEX_STRLEN)
							{
								if (type != IT::IDDATATYPE::INT)
									throw ERROR_THROW_IN(SEM_ERROR_SIRES + 3, tables->lexTable.table[i + index].sn, 0);	 	// unAccordong of types in express
								int countOfHesis = 0;
								do
								{
									index++;
									if (tables->lexTable.table[i + index].lexema == LEX_LEFTHESIS)
										countOfHesis++;
									if (tables->lexTable.table[i + index].lexema == LEX_RIGHTHESIS)
										countOfHesis--;

								} while (countOfHesis != 0);
							}
							else
							{
								if (tables->idenTable.table[tables->lexTable.table[i + index].idxTI].iddatatype != type)
									throw ERROR_THROW_IN(SEM_ERROR_SIRES + 3, tables->lexTable.table[i + index].sn, 0);
							}							     // unAccordong of types in express
						}
						index++;
						continue;
					}
					break;
				}

				}
			}
		}
	}

	void FillFunction(Functions& functions, IT::IdTable& idenTables)
	{
		for (int i = 0; i < idenTables.size; i++)
		{
			if (idenTables.table[i].idtype == IT::IDTYPE::F && (strcmp(idenTables.table[i].id, "stringLen")!=0) && (strcmp(idenTables.table[i].id, "lexStrCmp") != 0))
			{
				Entry temp = {};
				temp.index = i;
				while (idenTables.table[i+1].idtype==IT::IDTYPE::P)
				{
					if (temp.countOfParam > 8)
						throw ERROR_THROW_IN(SEM_ERROR_SIRES + 5, idenTables.table[i + 1].idxfirstLE, 0);
					temp.types[temp.countOfParam++] = idenTables.table[i + 1].iddatatype;
					i++;
				}
				AddFunc(functions, temp);
			}
		}
	}

	void AddFunc(Functions& functions, Entry entry)
	{
		if (functions.size > functions.maxsize)throw ERROR_THROW(SEM_ERROR_SIRES+6);
		functions.table[functions.size++] = entry;
	}

	void CheckFuncitionParams(Functions& functions, Scanner::Tables& tables)
	{
		//bool isOk = false;
		for (int i = 0; i < functions.size; i++)
		{
			for (int j = 0; j < tables.lexTable.size; j++)
			{
				if (tables.lexTable.table[j].idxTI == functions.table[i].index)
				{
					Entry temp = {};
					for (int k = 1; tables.lexTable.table[j+k].lexema != LEX_RIGHTHESIS ; k++)
					{
						if (tables.lexTable.table[j + k].lexema == LEX_ID || tables.lexTable.table[j + k].lexema == LEX_LITERAL)
						{
							if (temp.countOfParam > 8)
								throw ERROR_THROW_IN(SEM_ERROR_SIRES+5, tables.lexTable.table[j].sn, 0);
							temp.types[temp.countOfParam++] = tables.idenTable.table[tables.lexTable.table[j + k].idxTI].iddatatype;
						}
					}
					if (!isEqual(temp, functions.table[i]))
						throw ERROR_THROW_IN(SEM_ERROR_SIRES+7, tables.lexTable.table[j].sn, 0);
				}
			}
		}
	}

	void CheckBuiltInFunParam(LT::LexTable& lextable, IT::IdTable& idtable)
	{
		for (int i = 0; i < lextable.size; i++)
		{
			if (lextable.table[i].lexema == LEX_STRCMP || lextable.table[i].lexema == LEX_STRLEN)
			{
				int countOfParam = 0;
				int index = i;
				while (lextable.table[i + 1].lexema != LEX_RIGHTHESIS)
				{
					if (idtable.table[lextable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::INT)
						throw ERROR_THROW_IN(SEM_ERROR_SIRES+8, lextable.table[i].sn, 0);
					if (lextable.table[i + 1].lexema == LEX_ID || lextable.table[i + 1].lexema == LEX_LITERAL)
						countOfParam++;
					i++;
				}

				switch (lextable.table[index].lexema)
				{
				case LEX_STRCMP:
					if (countOfParam != 2)
						throw ERROR_THROW_IN(SEM_ERROR_SIRES + 8, lextable.table[i].sn, 0);
					continue;
				case LEX_STRLEN:
					if (countOfParam != 1)
						throw ERROR_THROW_IN(SEM_ERROR_SIRES + 8, lextable.table[i].sn, 0);
					continue;
				default:
					break;
				}
			}
		}
	}

	void CheckForReturnType(LT::LexTable& lextable, IT::IdTable& idtable)
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if ((idtable.table[i].idtype == IT::IDTYPE::F)&&(lextable.table[idtable.table[i].idxfirstLE-1].lexema==LEX_PROC))
			{
				bool isReturn = false;
				for (int j = 1; j + idtable.table[i].idxfirstLE < lextable.size; j++)
				{
					if (lextable.table[idtable.table[i].idxfirstLE + j].lexema == LEX_OUT)
					{
						if (idtable.table[lextable.table[idtable.table[i].idxfirstLE + j + 1].idxTI].iddatatype != idtable.table[i].iddatatype)
							throw ERROR_THROW_IN(SEM_ERROR_SIRES+9, lextable.table[idtable.table[i].idxfirstLE + j].sn, 0);
						isReturn = true;
					}
					if (lextable.table[idtable.table[i].idxfirstLE + j].lexema == LEX_PROC || lextable.table[idtable.table[i].idxfirstLE + j].lexema == LEX_ENTRY)
						break;
				}
				if (!isReturn)
					throw ERROR_THROW_IN(SEM_ERROR_SIRES+10, lextable.table[idtable.table[i].idxfirstLE].sn, 0);
			}
		}

		for (int i = 0; i < lextable.size; i++)
		{
			if (lextable.table[i].lexema == LEX_ENTRY)
			{
				int index = 1;
				while (lextable.table[i+index].lexema != LEX_CLOSE_PROC)
				{
					if (lextable.table[i + index].lexema == LEX_OUT)
					{
						if (idtable.table[lextable.table[i+index+1].idxTI].iddatatype != IT::INT)throw ERROR_THROW_IN(SEM_ERROR_SIRES + 14, lextable.table[i].sn, 0);
					}
					index++;
				}
			}
		}
	}

	void CheckCondAndStreams(LT::LexTable& lextable, IT::IdTable& idtable)
	{
		for (int i = 0; i < lextable.size; i++)
		{
			if (lextable.table[i].lexema == LEX_OUTSTREAM)				// check for sense of chain with outStream token
			{
				if (lextable.table[i + 1].lexema == LEX_LEFTHESIS)
				{
					int countOps = 0;
					int brBalance = 0;
					while (lextable.table[i].lexema != LEX_SEMICOLON)
					{
						i++;
						switch (lextable.table[i].lexema)
						{

						case LEX_LITERAL:
						case LEX_ID:
						{
							if (countOps == 1)throw ERROR_THROW_IN(SEM_ERROR_SIRES + 12, lextable.table[i].sn, 0);
							countOps++;
							break;
						}

						case LEX_LEFTHESIS:
						{
							brBalance++;
							break;
						}

						case LEX_RIGHTHESIS:
						{
							brBalance--;
							if (lextable.table[i + 1].lexema == LEX_SEMICOLON && brBalance != 0)throw ERROR_THROW_IN(SEM_ERROR_SIRES + 12, lextable.table[i].sn, 0);
							break;
						}

						default:
						{
							if (lextable.table[i].lexema == LEX_SEMICOLON)break;
							throw ERROR_THROW_IN(SEM_ERROR_SIRES + 12, lextable.table[i].sn, 0);
						}

						}
					}
				}
				else
					throw ERROR_THROW_IN(SEM_ERROR_SIRES + 12, lextable.table[i].sn, 0);

			}
		
			if (lextable.table[i].lexema == LEX_IF)	// check for right sense of chain with if-else block
			{
				int countOps=0,countBr=0;
				while (lextable.table[i].lexema != LEX_SEMICOLON && lextable.table[i].lexema != LEX_LEFTBRACE)
				{
					i++;
					switch (lextable.table[i].lexema)
					{

					case LEX_RIGHTHESIS:
					case LEX_LEFTHESIS:
					{
						if (countBr > 2)throw ERROR_THROW_IN(SEM_ERROR_SIRES + 13, lextable.table[i].sn, 0);
						countBr++;
						break;
					}

					case LEX_ID:
					case LEX_LITERAL:
					{
						if ((countOps > 2)||(idtable.table[lextable.table[i].idxTI].iddatatype!=IT::INT))throw ERROR_THROW_IN(SEM_ERROR_SIRES + 13, lextable.table[i].sn, 0);
						countOps++;
						break;
					}

					}
				}
			}
		}
	}

	Functions Create(int size)
	{
		if (size > 255)
			throw ERROR_THROW(1);
		Functions functions;
		functions.maxsize = size;
		functions.size = 0;
		functions.table = new Entry[functions.maxsize];

		return functions;
	}

	bool isEqual(Entry& entry1, Entry& entry2)
	{
		if (entry1.countOfParam == entry2.countOfParam)
		{
			for (int i = 0; i < entry1.countOfParam; i++)
			{
				if (entry1.types[i] != entry2.types[i])
					return false;
			}
			return true;
		}
		else
			return false;
	}


}