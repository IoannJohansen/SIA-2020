#include "CodeGeneration.h"

void Generation::CodeGeneration(Scanner::Tables& tables)
{
	ofstream fout;
	string funcName = "";
	stack<int> stk;
	stack<int> ifI;
	int numOfret = 0, numOfIf = 0;
	bool flagFunc = false, flEntry = false, flret = false, flOut = false, flElse = false, flIf = false;
	fout.open("../SIA_ASM/SIA_Asm.asm");
	if (!fout.is_open())throw ERROR_THROW(1);
	fout << HEAD;
	fout << LIBPROTOS;
	fout << CONST;
	for (int i = 0; i < tables.idenTable.size; i++)
	{
		if (tables.idenTable.table[i].idtype == IT::L)
		{
			fout << '\t' << tables.idenTable.table[i].id;

			switch (tables.idenTable.table[i].iddatatype)
			{

			case IT::IDDATATYPE::STR:
			{
				fout << " BYTE " << tables.idenTable.table[i].value.vstr.str << ", 0\n";
				break;
			}

			case IT::IDDATATYPE::INT:
			{
				fout << " SDWORD " << tables.idenTable.table[i].value.vint << endl;
				break;
			}

			}
		}

	}
	fout << ".DATA\n";

	for (int i = 0; i < tables.idenTable.size; i++)
	{
		if (tables.idenTable.table[i].idtype == IT::IDTYPE::V)
		{
			fout << "\t" << tables.idenTable.table[i].id;
			if (tables.idenTable.table[i].iddatatype == IT::STR)
			{
				fout << " DWORD ?\n";
			}
			if (tables.idenTable.table[i].iddatatype == IT::INT)
			{
				fout << " SDWORD 0\n";
			}
		}
	}

	fout << ".CODE\n";

	for (int i = 0; i < tables.lexTable.size; i++)
	{
		switch (tables.lexTable.table[i].lexema)
		{


			case LEX_PROC:			//+++
			{
				fout << '\t' << (funcName = tables.idenTable.table[tables.lexTable.table[++i].idxTI].id) << " PROC ";
				int indexF = i;
				for (; tables.lexTable.table[indexF].lexema != LEX_RIGHTHESIS; indexF++);
				i = indexF;
				while (tables.lexTable.table[indexF].lexema != LEX_LEFTHESIS)
				{
					if (tables.idenTable.table[tables.lexTable.table[indexF].idxTI].idtype == IT::P)
					{
						fout << tables.idenTable.table[tables.lexTable.table[indexF].idxTI].id << ':';

						if (tables.idenTable.table[tables.lexTable.table[indexF].idxTI].iddatatype == IT::INT)
						{
							fout << "SDWORD";
						}
						else
						{
							fout << "DWORD";
						}
					}
					if (tables.lexTable.table[indexF].lexema == LEX_COMMA)
					{
						fout << ", ";
					}
					indexF--;
				}
				flagFunc = true;
				fout << endl;
				break;
			}
			case LEX_ENTRY:			//+++
			{
				flEntry = true;
				fout << "main PROC\n";
				break;
			}

			case LEX_OUT:			//+++
			{
				fout << "\tpush ";
				i++;
				if (tables.idenTable.table[tables.lexTable.table[i].idxTI].idtype == IT::L)
				{
					fout << tables.idenTable.table[tables.lexTable.table[i++].idxTI].value.vint << endl;
				}
				else
				{
					fout << tables.idenTable.table[tables.lexTable.table[i++].idxTI].id << endl;
				}
				if (flagFunc)
				{
					fout << "\t\tjmp local" << numOfret << endl;
					flret = true;
				}
				if (flEntry)
				{
					fout << "\t\tjmp theend\n";
					flret = true;
				}
				break;
			}

			case LEX_EQUAL_SIGN:	//+++
			{
				int resPosition = i - 1;
				while (tables.lexTable.table[i].lexema != LEX_SEMICOLON)
				{
					switch (tables.lexTable.table[i].lexema)
					{
						case LEX_STRLEN:
						{
							fout << "\t\tcall stringLen\n\tpush eax\n";
							break;
						}

						case LEX_STRCMP:
						{
							fout << "\t\tcall lexStrCmp\n\tpush eax\n";
							break;
						}

						case LEX_LITERAL:
						{
							if (tables.idenTable.table[tables.lexTable.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
							{
								fout << "\tpush offset " << tables.idenTable.table[tables.lexTable.table[i].idxTI].id << endl;
								break;
							}
							else
							{
								fout << "\tpush " << tables.idenTable.table[tables.lexTable.table[i].idxTI].id << endl;
								break;
							}
						}

						case LEX_ID:
						{
							if (tables.idenTable.table[tables.lexTable.table[i].idxTI].idtype /*==*/!= IT::IDTYPE::F)
							{
								/*fout << "\t\tcall " << tables.idenTable.table[tables.lexTable.table[i].idxTI].id << "\n\tpush eax\n";*/
								fout << "\tpush " << tables.idenTable.table[tables.lexTable.table[i].idxTI].id << endl;
								break;
							}
							//--- 168 was here | if bad res => return
							break;
						}

						case '@':
						{
							fout << "\t\tcall " << tables.idenTable.table[tables.lexTable.table[i - tables.lexTable.table[i].idxTI - 1].idxTI].id << "\n\tpush eax\n";
							break;
						}

						case LEX_ARITHMETIC:
						{
							switch (tables.idenTable.table[tables.lexTable.table[i].idxTI].id[0])
							{

								case LEX_STAR:
								{
									fout << "\tpop eax\n\tpop ebx\n";
									fout << "\tmul ebx\n\tpush eax\n";
									break;
								}

								case LEX_PLUS:
								{
									fout << "\tpop eax\n\tpop ebx\n";
									fout << "\tadd eax, ebx\n\tpush eax\n";
									break;
								}

								case LEX_MINUS:
								{
									fout << "\tpop ebx\n\tpop eax\n";
									fout << "\tsub eax, ebx\n\tpush eax\n";
									break;
								}

								case LEX_DIRSLASH:
								{
									fout << "\tpop ebx\n\tpop eax\n";
									fout << "\tcmp ebx,0\n"\
										"\tje SOMETHINGWRONG\n";
									fout << "\tcdq\n";
									fout << "\tidiv ebx\n\tpush eax\n";
									break;
								}

								case LEX_MODULO:
								{

									fout << "\tpop ebx\n\tpop eax\n";
									fout << "\tcmp ebx,0\n"\
										"\tje SOMETHINGWRONG\n";
									fout << "\tcdq\n";
									fout << "\tidiv ebx\n\tpush edx\n";
									break;
								}


								default:
									break;
							}
							break;
						}

						default:
							break;
					}
					i++;
				}

				if (tables.idenTable.table[tables.lexTable.table[resPosition].idxTI].iddatatype == IT::IDDATATYPE::INT)
				{
					fout << "\tpop eax\n";
					fout << "\tcmp eax, 2147483647\n";
					fout << "\tjg overflow\n";
					fout << "\tcmp eax, -2147483648\n";
					fout << "\tjl overflow\n";
					fout << "\tmov " << tables.idenTable.table[tables.lexTable.table[resPosition].idxTI].id << ", eax";
				}
				else
				{
					fout << "\tpop " << tables.idenTable.table[tables.lexTable.table[resPosition].idxTI].id << "\n";
				}
				fout << endl;
				break;

			}
			case LEX_LEFTHESIS:		//+++
			{
				if (numOfIf && tables.lexTable.table[i - 1].lexema == LEX_IF)
				{
					fout << "\tmov eax, " << tables.idenTable.table[tables.lexTable.table[i + 1].idxTI].id << endl;
					fout << "\tcmp eax, " << tables.idenTable.table[tables.lexTable.table[i + 3].idxTI].id << endl;
					if (tables.lexTable.table[i + 2].lexema == LEX_MORE)
					{
						fout << "\t\tjg ifi" << numOfIf << endl;
						fout << "\t\tjl else" << numOfIf << endl;
					}
					else if(tables.lexTable.table[i + 2].lexema == LEX_LESS)
					{
						fout << "\t\tjl ifi" << numOfIf << endl;
						fout << "\t\tjg else" << numOfIf << endl;
					}
				}
				break;
			}
			case LEX_OUTSTREAM:		//+++
			{
				switch (tables.idenTable.table[tables.lexTable.table[i + 1].idxTI].iddatatype)
				{

					case IT::IDDATATYPE::INT:
					{
						fout << "\npush " << tables.idenTable.table[tables.lexTable.table[i + 1].idxTI].id << "\ncall outStreamN\n";
						break;
					}

					case IT::IDDATATYPE::STR:
					{
						if (tables.idenTable.table[tables.lexTable.table[i + 1].idxTI].idtype == IT::IDTYPE::L)
							fout << "\npush offset " << tables.idenTable.table[tables.lexTable.table[i + 1].idxTI].id << "\ncall outStreamW\n";
						else fout << "\npush " << tables.idenTable.table[tables.lexTable.table[i + 1].idxTI].id << "\ncall outStreamW\n";

						break;
					}

				}
				break;
			}
			case LEX_LEFTBRACE:		//+++
			{
				if (numOfIf && !flElse && flIf)
				{
					fout << "ifi" << ifI.top() << ":\n";
					flIf = false;
				}
				if (flElse && tables.lexTable.table[i - 1].lexema == LEX_ELSE)
				{
					fout << "else" << ifI.top() << ":\n";
				}
				break;
			}
			case LEX_CLOSE_PROC:	//+++
			{
				if (flEntry && !flagFunc && tables.lexTable.table[i + 1].lexema == LEX_SEMICOLON)
				{
					if (flret)
					{
						fout << "theend:\n";
						flret = false;
					}
					fout << END;
					break;
				}
				if (flagFunc && tables.lexTable.table[i + 1].lexema == LEX_SEMICOLON)
				{
					if (flret)
					{
						fout << "local" << numOfret++ << ":\n";
						fout << "\tpop eax\n\tret\n";
						flret = false;
					}
					fout << funcName << " ENDP\n\n";
					flagFunc = false;
					break;
				}
				break;
			}
			case LEX_RIGHTBRACE:	//+++
			{
			
				//----
				/*if (flagFunc && tables.lexTable.table[i + 1].lexema == LEX_SEMICOLON)
				{
					if (flret)
					{
						fout << "local" << numOfret++ << ":\n";
						fout << "\tpop eax\n\tret\n";
						flret = false;
					}
					fout << funcName << " ENDP\n\n";
					flagFunc = false;
				}*/

				if (!stk.empty())
				{
					switch (stk.top())
					{
						case 1:
						{
							if (tables.lexTable.table[i + 1].lexema == LEX_ELSE)
							{
								fout << "\tjmp ifEnd" << ifI.top() << endl;
								//ifi.pop();
							}
							else
							{
								fout << "else" << ifI.top() << ":\n";
								ifI.pop();
								//num_of_if--; // --
							}
							stk.pop();
							break;
						}
						case 2:
						{
							fout << "ifEnd" << ifI.top() << ":\n";
							ifI.pop();
							flElse = false;
							//num_of_if--; // --
							stk.pop();
							break;
						}
						default:
							break;
					}
				}
				break;
			}
			case LEX_IF:			//+++
			{
				flIf = true;
				stk.push(1); // 1 - признак if
				numOfIf++;
				ifI.push(numOfIf);
				break;
			}

			case LEX_ELSE:			//+++		
			{
				flElse = true;
				stk.push(2);			// 2- признак else
				break;
			}


		}
	}

	fout.close();
	std::cout << "Code Generation is done" << endl;
}
