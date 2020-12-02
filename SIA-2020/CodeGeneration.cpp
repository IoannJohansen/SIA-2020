#include "CodeGeneration.h"

void Generation::CodeGeneration(Scanner::Tables& tables)
{
	ofstream fout;
	fout.open("../SIA_ASM/SIA_Asm.asm");
	if (!fout.is_open())throw ERROR_THROW(1);
	fout << HEAD;
	fout << LIBPROTOS;
	fout << CONST;
	fout << "Hello wordl!";
	for (int i = 0; i < tables.idenTable.size; i++)
	{
		if (tables.idenTable.table[i].idtype == IT::L)
		{
			fout << '\t' << tables.idenTable.table[i].id;
			switch (tables.idenTable.table[i].idtype)
			{

			case IT::INT:
			{
				fout << " DWORD " << tables.idenTable.table[i].value.vint << endl;
				break;
			}

			case IT::STR:
			{
				fout << " BYTE " << tables.idenTable.table[i].value.vstr.str << ", 0\n";
				break;
			}

			}
		}
	}
	fout.close();
	cout << "Code Generation is done" << endl;
}
