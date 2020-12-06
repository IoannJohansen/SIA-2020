#pragma once
#define ID_MAXSIZE		9				//максимальное количество сиволов в идентификаторе
#define TI_MAXSIZE		1024			// максимальное количество эл-ов в таблице идентификаторов 
#define TI_INT_DEFAULT	0x00000000		// значение по умолчанию дл€ типа integer 
#define TI_STR_DEFAULT	0x00			// значение по умолчанию дл€ типа string 
#define TI_NULLIDX		-1				// нет элемента таблицы идентификаторов
#define TI_STR_MAXSIZE	257
#define TI_BLOCK_DEFAULT "GLOBAL"
#define TI_BLOCK_MAIN	"ENTRY"
#define PARM_ID_DEFAULT_EXT L".id.txt" //дл€ файла с итогом лексического анализa(идентификаторы и литералы)


namespace IT	// таблица идентификатов
{
	enum IDDATATYPE { DEF = 0, INT = 1, STR = 2 };	//типы данных идентификаторов: integer, string
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4 , A = 5};		//типы идентификаторов: переменна€, функци€, параметр, литерал
	struct Entry	//строка таблицы идентификаторов
	{
		char parrentBlock[ID_MAXSIZE+1];	//!!!
		int			idxfirstLE;		//индекс первой строки в таблице лексем
		char		id[2*ID_MAXSIZE];		//идентификатор (автоматически усекаетс€ до ID_MAXSIZE)
		IDDATATYPE  iddatatype;		//тип данных
		IDTYPE		idtype;		//тип идентификатора
		struct VALUE
		{
			int vint = NULL;	//значение integer 
			struct
			{
				int len;	//кол-во символов в string
				char str[TI_STR_MAXSIZE];	//символы string
			} vstr;		//значение string
		} value;
	};

	struct IdTable		//экземпл€р таблицы идентификаторов
	{
		int maxsize;	//емкость таблицы идентификаторов < TI_MAXSIZE
		int size;	//текущий размер таблицы идентификаторов < maxsize
		Entry* table;	//массив строк таблицы идентификаторов
		void writeIT(const wchar_t* in);
	};
	IdTable Create(		//создать таблицу идентификаторов
		int size		//емкость таблицы идентификаторов < TI_MAXSIZE
	);
	void Add(	//добавить строку в таблицу идентификаторов
		IdTable& idtable,	//экземпл€р таблицы идентификаторов
		Entry entry		//строка таблицы идентификаторов
	);
	int IsId(	//возврат: номер строки (если есть), TI_NULLIDX(если нет)
		IdTable& idtable,	//экземпл€р таблицы идентификаторов
		char id[ID_MAXSIZE],		//идентификатор
		char block[ID_MAXSIZE]
		);

	int IsId(IdTable& idtable, char* block, IDDATATYPE type, char* literal);

	int IsId(IdTable& idtable, char* id);

	void ShowTable(IdTable* idtable);

	void Delete(IdTable& idtable);		//удалить таблицу лексем (освободить пам€ть)
	Entry GetEntry(IdTable& idtable, int n);

}
