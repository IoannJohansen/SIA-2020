#pragma once
#define	LT_MAXSIZE			1024		// максимальное количество эл-ов в таблице лексем	
#define	LT_TI_NULLXDX		-1			// нет элемента таблицы идентификаторов				
#define	LEX_NUM				'n'			// лексема дл€ num
#define	LEX_WORD			'w'			// лексема дл€ word
#define	LEX_TYPE			't'			// лексема дл€ типов
#define	LEX_ID				'i'			// лексема дл€ идентификатора
#define	LEX_LITERAL			'l'			// лексема дл€ литерала
#define	LEX_PROC			'p'			// лексема дл€ proc
#define	LEX_CREATE			'c'			// лексема дл€ create
#define	LEX_OUT				'o'			// лексема дл€ out
#define	LEX_OUTSTREAM		'r'			// лексема дл€ outStream
#define	LEX_ENTRY			'e'			// лексема дл€ главной функции
#define	LEX_IF				'm'			// лексема дл€ условного оператора
#define	LEX_ELSE			'a'			// лексема дл€ условного оператора (2)
#define	LEX_STRLEN			's'			// лексема дл€ библиотечной функции
#define	LEX_STRCMP			'x'			// лексема дл€ библиотечной функции
#define	LEX_OPEN_PROC		'['			// лексема дл€ открывающкй процедурной скобки
#define	LEX_CLOSE_PROC		']'			// лексема дл€ закрывающей процедурной скобки
#define	LEX_ARITHMETIC		'v'			// лексема дл€ арифметических знаков
#define	LEX_SEMICOLON		';'			// лексема дл€ ;
#define	LEX_COMMA			','			// лексема дл€ ,
#define	LEX_LEFTBRACE		'{'			// лексема дл€ {
#define	LEX_RIGHTBRACE		'}'			// лексема дл€ }
#define	LEX_LEFTHESIS		'('			// лексема дл€ (
#define	LEX_RIGHTHESIS		')'			// лексема дл€ )
#define	LEX_PLUS			'+'			// лексема дл€ +
#define	LEX_MINUS			'-'			// лексема дл€ -
#define	LEX_STAR			'*'			// лексема дл€ *
#define	LEX_DIRSLASH		'/'			// лексема дл€ /
#define	LEX_MODULO			'%'			// лексема дл€ делени€ по модулю
#define	LEX_EQUAL_SIGN		'='			// лексема дл€ =
#define LEX_LESS			'<'			// лексема дл€ <
#define LEX_MORE			'>'			// лексема дл€ >
#define PARM_LEX_DEFAULT_EXT L".lex.txt" //дл€ файла с итогом лексического анализa


namespace LT
{
	struct Entry	//строка таблицы лексем
	{
		char lexema;	//лексема
		int sn;			//номер строки в исходном тексте
		int idxTI;		//индекс в таблице идентификаторов или LT_TI_NULLIDX
		int posInStr;
	};

	struct LexTable		//экземпл€р таблицы лексем
	{
		int maxsize;	//емкость таблицы лексем < LT_MAXSIZE
		int size;		//текущий размер таблицы лексем < maxsize
		Entry* table;	//массив строк таблицы лексем
		void writeLT(const wchar_t* in);
	};

	LexTable Create(	//создать таблицу лексем
		int size	//емкость таблицы лексем < LT_MAXSIZE
	);
	void Add(	//добавить строку в таблицу лексем
		LexTable& lextable,		//экземпл€р таблицы лексем
		Entry entry		//строка таблицы лексем
	);

	Entry GetEntry(		//получить строку таблицы лексем
		LexTable& lextable,		//экземпл€р таблицы лексем
		int n		//номер получаемой строки
	);

	void Delete(LexTable& lextable);	//удалить таблицу лексем (освободить пам€ть)
}
