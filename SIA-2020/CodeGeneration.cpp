#include "CodeGeneration.h"

void Generation::CodeGeneration(Scanner::Tables& tables)
{
	ofstream fout;
	string funcName = "";
	stack<int> stk;
	stack<int> ifI;
	int numOfret = 0, numOfIf = 0;
	bool flagFunc = false, flEntry = false, flret = false, flOut = false, flElse = false, flIf = false;
	fout.open("D:\\Desktop\\Labs\\SIA-2020\\SIA_ASM\\SIA_Asm.asm");
	if (!fout.is_open())throw ERROR_THROW(114);
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
					if (tables.idenTable.table[i].value.vstr.len-2==0)
					{
						fout << " BYTE " << "0\n";
					}
					else
					{
						fout << " BYTE " << tables.idenTable.table[i].value.vstr.str << ", 0\n";
					}
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
			case LEX_PROC:		
			{
				fout  << (funcName = tables.idenTable.table[tables.lexTable.table[++i].idxTI].id) << " PROC ";
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
			case LEX_ENTRY:			
			{
				flEntry = true;
				fout << "main PROC\n";
				break;
			}
			case LEX_OUT:
			{
				i++;
				while (tables.lexTable.table[i].lexema != LEX_SEMICOLON)
				{
					switch (tables.lexTable.table[i].lexema)
					{

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
							if (tables.idenTable.table[tables.lexTable.table[i].idxTI].idtype != IT::IDTYPE::F)
							{
								fout << "\tpush " << tables.idenTable.table[tables.lexTable.table[i].idxTI].id << endl;
								break;
							}
							break;
						}

						case '@':
						{
							fout << "\tcall " << tables.idenTable.table[tables.lexTable.table[i - tables.lexTable.table[i].idxTI - 1].idxTI].id << "\n\tpush eax\n";
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
								{
									break;
								}

							}

						}
						
					}
					i++;
				}

				if (flagFunc)
				{
					fout << "\tjmp local" << numOfret << endl;
					flret = true;
				}

				if (flEntry)
				{
					fout << "\tjmp theend\n";
					flret = true;
				}
				
				break;
			}
			case LEX_EQUAL_SIGN:
			{
				int resPosition = i - 1;
				while (tables.lexTable.table[i].lexema != LEX_SEMICOLON)
				{
					switch (tables.lexTable.table[i].lexema)
					{
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
								if (tables.idenTable.table[tables.lexTable.table[i].idxTI].idtype != IT::IDTYPE::F)
								{
									fout << "\tpush " << tables.idenTable.table[tables.lexTable.table[i].idxTI].id << endl;
									break;
								}
								break;
							}

						case '@':
						{
								fout << "\tcall " << tables.idenTable.table[tables.lexTable.table[i - tables.lexTable.table[i].idxTI - 1].idxTI].id << "\n\tpush eax\n";
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
					fout << "\tmov " << tables.idenTable.table[tables.lexTable.table[resPosition].idxTI].id << ", eax";
				}
				else
				{
					fout << "\tpop " << tables.idenTable.table[tables.lexTable.table[resPosition].idxTI].id << "\n";
				}
				fout << endl;
				break;

			}
			case LEX_LEFTHESIS:
			{
				if (numOfIf && tables.lexTable.table[i - 1].lexema == LEX_IF)
				{
					fout << "\tmov eax, " << tables.idenTable.table[tables.lexTable.table[i + 1].idxTI].id << endl;
					fout << "\tcmp eax, " << tables.idenTable.table[tables.lexTable.table[i + 3].idxTI].id << endl;
					if (tables.lexTable.table[i + 2].lexema == LEX_MORE)
					{
						fout << "\t\tjg ifi" << numOfIf << endl;
						fout << "\t\tjle else" << numOfIf << endl;
					}
					else if(tables.lexTable.table[i + 2].lexema == LEX_LESS)
					{
						fout << "\t\tjl ifi" << numOfIf << endl;
						fout << "\t\tjge else" << numOfIf << endl;
					}
					else if (tables.lexTable.table[i + 2].lexema == LEX_OPERSEQUAL)
					{
						fout << "\t\tjz ifi" << numOfIf << endl;
						fout << "\t\tjnz else" << numOfIf << endl;
					}
					else if (tables.lexTable.table[i + 2].lexema == LEX_OPERSNOTEQUAL)
					{
						fout << "\t\tjnz ifi" << numOfIf << endl;
						fout << "\t\tjz else" << numOfIf << endl;
					}
				}
				break;
				}
			case LEX_OUTSTREAM:
			{
				i++;
				IT::IDDATATYPE outType = tables.idenTable.table[tables.lexTable.table[i].idxTI].iddatatype;

				while (tables.lexTable.table[i].lexema!=LEX_SEMICOLON)
				{
					switch (tables.lexTable.table[i].lexema)
					{
				
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
							if (tables.idenTable.table[tables.lexTable.table[i].idxTI].idtype != IT::IDTYPE::F)
							{
								fout << "\tpush " << tables.idenTable.table[tables.lexTable.table[i].idxTI].id << endl;
								break;
							}
							break;
						}

						case '@':
						{
							fout << "\tcall " << tables.idenTable.table[tables.lexTable.table[i - tables.lexTable.table[i].idxTI - 1].idxTI].id << "\n\tpush eax\n";
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
								{
									break;
								}

							}

						}
					}
					i++;
				}

				if(outType==IT::INT)
					fout << "\n\tcall outStreamN\n";
				else 
					fout << "\ncall outStreamW\n";
				break;

				}
			case LEX_LEFTBRACE:
			{
				if (numOfIf && flIf)
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
			case LEX_CLOSE_PROC:	
			{
				if (flEntry && !flagFunc && tables.lexTable.table[i + 1].lexema == LEX_SEMICOLON)
				{
					if (flret)
					{
						fout << "theend:";
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
			case LEX_RIGHTBRACE:	
			{
				if (!stk.empty())
				{
					switch (stk.top())
					{
						case 1:
						{
							if (tables.lexTable.table[i + 1].lexema == LEX_ELSE)
							{
								fout << "\tjmp ifEnd" << ifI.top() << endl;
							}
							else
							{
								fout << "else" << ifI.top() << ":\n";
								ifI.pop();
							}
							stk.pop();
							break;
						}

						case 2:
						{
							fout << "ifEnd" << ifI.top() << ":\n";
							ifI.pop();
							flElse = false;
							stk.pop();
							break;
						}

						default:
							break;
					}
				}
				break;
				}
			case LEX_IF:			
			{
				flIf = true;
				stk.push(1);
				numOfIf++;
				ifI.push(numOfIf);
				break;
			}
			case LEX_ELSE:					
			{
				flElse = true;
				stk.push(2);
				break;
			}
		}
	}

	fout.close();
	std::cout << "Code Generation is done" << endl;
}
