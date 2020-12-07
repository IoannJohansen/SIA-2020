#include "stdafx.h"
#include <iomanip>
#include "IT.h"
namespace IT
{
	IdTable Create(int size)
	{
		IdTable* New = new IdTable;
		New->maxsize = size;
		New->size = 0;
		New->table = new Entry[size];
		return *New;
	}

	void Add(IdTable& idtable, Entry entry)
	{
		if (idtable.size == idtable.maxsize) throw ERROR_THROW(118);	// lt overflow
		idtable.table[idtable.size++] = entry;
	}

	Entry GetEntry(IdTable& idtable, int n)
	{
		return idtable.table[n];
	}

	int IsId(IdTable& idtable, char id[ID_MAXSIZE], char block[ID_MAXSIZE])		// usuall search
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (!strcmp(idtable.table[i].id, id) && !strcmp(idtable.table[i].parrentBlock, block))
				return i;
			if (!strcmp(idtable.table[i].id, id) && idtable.table[i].idtype == F && !strcmp(idtable.table[i].parrentBlock, TI_BLOCK_DEFAULT))
				return i;
		}
		return TI_NULLIDX;
	}

	int IsId(IdTable& idtable, char* block, IDDATATYPE type, char* literal)		// search for literal
	{
		int val = atoi(literal);
		for (int i = 0; i < idtable.size; i++)
		{
			if (idtable.table[i].id[0]=='L' && (!strcmp(idtable.table[i].parrentBlock, block)))
			{
				switch (type)
				{
					case IT::INT:
					{
						if(idtable.table[i].iddatatype==IT::INT && (idtable.table[i].value.vint == val))return i;
						break;
					}
					case IT::STR:
					{
						if (idtable.table[i].iddatatype == IT::STR && (!strcmp(idtable.table[i].value.vstr.str, literal)))return i;
						break;
					}

				}
			}
		}
		return TI_NULLIDX;
	}

	int IsId(IdTable& idtable, char* id)										// for lib functions
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (!strcmp(idtable.table[i].id, id))
			{
				return i;
			}
		}
		return TI_NULLIDX;
	}



	void IdTable::writeIT(const wchar_t* in)
	{
		int i = 0;
		wchar_t id[300];
		for (; in[i] != '\0'; i++)
			id[i] = in[i];
		id[i] = '\0';
		wcscat_s(id, PARM_ID_DEFAULT_EXT);

		std::ofstream* idStream = new std::ofstream;
		idStream->open(id);

		if (idStream->is_open())
		{
			bool flagForFirst = false;

#pragma region Literals

			* (idStream) << "====================================================================================" << std::endl;
			*(idStream) << "| Литералы                                                                         |" << std::endl;
			*(idStream) << "====================================================================================" << std::endl;
			*(idStream) << '|' << std::setw(15) << "Тип данных: " << "|" << std::setw(50) << "Значение: " << '|' << std::setw(15) << "Длина строки: " << '|' << std::endl;
			*(idStream) << "====================================================================================" << std::endl;

			for (int i = 0; i < this->size; i++)
			{
				if (this->table[i].idtype == IT::IDTYPE::L)
				{
					if (flagForFirst)
						*(idStream) << "------------------------------------------------------------------------------------" << std::endl;

					switch (this->table[i].iddatatype)
					{
					case IT::IDDATATYPE::INT:
					{
						*(idStream) << '|' << std::setw(15) << "INT  " << '|' << std::setw(50) << this->table[i].value.vint << '|' << std::setw(15) << "-" << '|' << std::endl;
						break;
					}
					case IT::IDDATATYPE::STR:
					{
						*(idStream) << '|' << std::setw(15) << "STR  " << '|' << std::setw(50) << this->table[i].value.vstr.str  << '|' << std::setw(15) << (int)this->table[i].value.vstr.len << '|' << std::endl;
						break;
					}
					}

					flagForFirst = true;
				}
			}

			*(idStream) << "====================================================================================" << std::endl;


#pragma endregion
			* (idStream) << "\n\n\n";
#pragma region Functions

			flagForFirst = false;
			char buf[50]{};

			*(idStream) << "=====================================================" << std::endl;
			*(idStream) << "| Функции                                           |" << std::endl;
			*(idStream) << "=====================================================" << std::endl;
			*(idStream) << '|' << std::setw(20) << "Идентификатор: " << '|' << std::setw(30) << "Тип возвращаемого значения: " << '|' << std::endl;
			*(idStream) << "=====================================================" << std::endl;

			for (int i = 0; i < this->size; i++)
			{
				if (this->table[i].idtype == IT::IDTYPE::F)
				{
					strcat_s(buf, "  ");

					if (flagForFirst)
						*(idStream) << "-----------------------------------------------------" << std::endl;

					switch (this->table[i].iddatatype)
					{
					case IT::IDDATATYPE::INT:
					{
						*(idStream) << '|' << std::setw(20) << this->table[i].id << '|' << std::setw(30) << "INT " << '|' << std::endl;
						break;
					}
					case IT::IDDATATYPE::STR:
					{
						*(idStream) << '|' << std::setw(20) << this->table[i].id << '|' << std::setw(30) << "STR " << '|' << std::endl;
						break;
					}
					}

					flagForFirst = true;
				}


			}

			*(idStream) << "=====================================================" << std::endl;

#pragma endregion
			* (idStream) << "\n\n\n";
#pragma region Parameteres
			flagForFirst = false;
			*buf = '\0';
			*(idStream) << "=========================================================================" << std::endl;
			*(idStream) << "| Параметры                                                             |" << std::endl;
			*(idStream) << "=========================================================================" << std::endl;
			*(idStream) << '|' << std::setw(20) << "Параметр: " << '|' << std::setw(30) << "Родительский блок: " << '|' << std::setw(19) << "Тип данных: " << '|' << std::endl;
			*(idStream) << "=========================================================================" << std::endl;
			for (int i = 0; i < this->size; i++)
			{
				if (this->table[i].idtype == IT::IDTYPE::P)
				{
					strcat_s(buf, "   ");

					if (flagForFirst)
						*(idStream) << "-------------------------------------------------------------------------" << std::endl;

					*(idStream) << '|' << std::setw(20) << this->table[i].id << '|' << std::setw(30) << this->table[i].parrentBlock << '|' << std::setw(19);
					if (this->table[i].iddatatype == IT::STR)*(idStream) << "STR" << '|' << std::endl;
					if (this->table[i].iddatatype == IT::INT)*(idStream) << "INT" << '|' << std::endl;
					flagForFirst = true;
				}
			}
			*(idStream) << "=========================================================================" << std::endl;
#pragma endregion
			*(idStream) << "\n\n\n";
#pragma region Variables

			flagForFirst = false;

			*(idStream) << "==================================================================================================================================================================" << std::endl;
			*(idStream) << "| Переменные                                                                                                                                                     |" << std::endl;
			*(idStream) << "==================================================================================================================================================================" << std::endl;
			*(idStream) << '|' << std::setw(30) << "Имя родительского блока: " << '|' << std::setw(20) << "Идентификатор: " << '|' << std::setw(15) << "Тип данных: " << '|' << std::setw(25) << "Тип идентификатора: " << '|' << std::setw(50) << "Значение: " << '|' << std::setw(15) << "Длина строки: " << '|' << std::endl;
			*(idStream) << "==================================================================================================================================================================" << std::endl;

			for (int i = 0; i < this->size; i++)
			{
				if (this->table[i].idtype == IT::IDTYPE::V)
				{
					if (flagForFirst)
						*(idStream) << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;

					switch (this->table[i].iddatatype)
					{
					case IT::IDDATATYPE::INT:
					{
						*(idStream) << '|' << std::setw(30) << this->table[i].parrentBlock << '|' << std::setw(20) << this->table[i].id << '|' << std::setw(15) << "INT " << '|' << std::setw(25) << "V  " << '|' << std::setw(50) << this->table[i].value.vint << '|' << std::setw(15) << "- " << '|' << std::endl;
						break;
					}
					case IT::IDDATATYPE::STR:
					{
						*(idStream) << '|' << std::setw(30) << this->table[i].parrentBlock << '|' << std::setw(20) << this->table[i].id << '|' << std::setw(15) << "STR " << '|' << std::setw(25) << "V  " << '|' << std::setw(50) << this->table[i].value.vstr.str << '|' << std::setw(15) << (int)this->table[i].value.vstr.len << '|' << std::endl;
						break;
					}
					}

					flagForFirst = true;
				}

			}

			*(idStream) << "==================================================================================================================================================================" << std::endl;

#pragma endregion
			* (idStream) << "\n\n\n";

		}
		else
			throw ERROR_THROW(119);			// error of creating it file
		idStream->close();
		delete idStream;
	}

	void ShowTable(IdTable* idtable)
	{
		int i, numberOP = 0;
		cout << setfill('-') << setw(87) << '-' << endl;
		cout << "   №" << " | " << "Идентификатор" << " | " << "Тип данных" << " | " << "Тип идентификатора" << " | " << "Индекс в ТЛ" << " | " << "Значение    " << endl;
		cout << setw(87) << '-' << endl;
		for (i = 0; i < idtable->size; i++) {
			cout << setfill(' ') << setw(4) << std::right << i << " | ";
			cout << setw(13) << left << idtable->table[i].id << " | ";
			switch (idtable->table[i].iddatatype) {
			case  IT::INT:
			{
				cout << setw(10) << left;

				cout << "real" << " | "; break;
			}
			case  IT::STR:
			{
				cout << setw(10) << left;
				cout << "word" << " | ";
				break;
			}
			default:
				cout << setw(10) << left << "unknown" << " | "; break;
			}

			switch (idtable->table[i].idtype) 
			{

			case IT::V:
				cout << setw(18) << left << "переменная" << " | ";
				break;

			case IT::F:
				cout << setw(18) << left << "функция" << " | ";
				break;

			case IT::P:
				cout << setw(18) << left << "параметр" << " | ";
				break;

			case IT::L:
				cout << setw(18) << left << "литерал" << " | ";
				break;
			case IT::A:
				cout << setw(18) << left << "Арифм. Оп." << " | ";
				numberOP++;
				break;
			default:
				cout << setw(18) << left << "unknown" << " | ";
				break;

			}
			cout << setw(11) << left << idtable->table[i].idxfirstLE << " | ";
			if (idtable->table[i].iddatatype == IT::INT && (idtable->table[i].idtype == IT::V || idtable->table[i].idtype == IT::L)) {
				cout << setw(18) << left << idtable->table[i].value.vint;
			}
			else if (idtable->table[i].iddatatype == IT::STR && (idtable->table[i].idtype == IT::V || idtable->table[i].idtype == IT::L)) {
				cout << "[" << idtable->table[i].value.vstr.len << "]\"" << idtable->table[i].value.vstr.str << "\"";
			}
			else {
				cout << "-";
			}
			cout << endl;
		}
		cout << setfill('-') << setw(87) << '-' << endl;
		cout << "Количество идентификаторов: " << i - numberOP << endl;
		cout << setw(87) << '-' << endl;
	}


	void Delete(IdTable& idtable)
	{
		delete[] idtable.table;
		idtable = {};
	}

}
