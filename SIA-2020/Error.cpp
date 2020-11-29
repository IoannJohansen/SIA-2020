#include "Error.h"

namespace Error
{
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "[SYSTEM] Недопустимый код ошибки"),
		ERROR_ENTRY(1, "[SYSTEM] Системный сбой"),

		ERROR_ENTRY_NODEF(2),		ERROR_ENTRY_NODEF(3),		ERROR_ENTRY_NODEF(4),
		ERROR_ENTRY_NODEF(5),		ERROR_ENTRY_NODEF(6),		ERROR_ENTRY_NODEF(7),
		ERROR_ENTRY_NODEF(8),		ERROR_ENTRY_NODEF(9),		ERROR_ENTRY_NODEF10(10),
		ERROR_ENTRY_NODEF10(20),	ERROR_ENTRY_NODEF10(30),	ERROR_ENTRY_NODEF10(40),
		ERROR_ENTRY_NODEF10(50),	ERROR_ENTRY_NODEF10(60),	ERROR_ENTRY_NODEF10(70),
		ERROR_ENTRY_NODEF10(80),	ERROR_ENTRY_NODEF10(90),

		ERROR_ENTRY(100, "[SYSTEM] Параметр -in должен быть задан"),

		ERROR_ENTRY_NODEF(101),		ERROR_ENTRY_NODEF(102),		ERROR_ENTRY_NODEF(103),

		ERROR_ENTRY(104, "[SYSTEM] Превышена длина входного параметра"),

		ERROR_ENTRY_NODEF(105),		ERROR_ENTRY_NODEF(106),		ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),		ERROR_ENTRY_NODEF(109),

		ERROR_ENTRY(110, "[SYSTEM] Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, "[SYSTEM] Недопустимый символ в исходном коде (-in)"),
		ERROR_ENTRY(112, "[SYSTEM] Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113, "[SYSTEM] Файл, переданный как -in:, пуст"),
		ERROR_ENTRY_NODEF(114),
		ERROR_ENTRY_NODEF(115),

		//------------------LEXICAL ANALYSE ( 116-133 )

		ERROR_ENTRY(116, "[LEX_ANALYSIS] Кол-во открывающих и закрывающих фигурных скобок не совпадает"),	//+
		ERROR_ENTRY(117, "[LEX_ANALYSIS] Таблица лексем переполнена"),										//+
		ERROR_ENTRY(118, "[LEX_ANALYSIS] Таблица идентификаторов переполнена"),								//+
		ERROR_ENTRY(119, "[LEX_ANALYSIS] Не удалось создать файл с лексемами / идентификаторами"),			//+
		ERROR_ENTRY(120, "[LEX_ANALYSIS] Превышена длинна стркового литерала"),								//+
		ERROR_ENTRY(121, "[LEX_ANALYSIS] Превышена длинна идентификатора"),									//+
		ERROR_ENTRY(122, "[LEX_ANALYSIS] Запрещенные символы в имени идетификатора"),						//+
		ERROR_ENTRY(123, "[LEX_ANALYSIS] Слишком большое значение целочисленного литерала"),				//+
		ERROR_ENTRY(124, "[LEX_ANALYSIS] Не объявлена точка входа в программу ( main )"),					//+
		ERROR_ENTRY(125, "[LEX_ANALYSIS] Определено несколько точек входа в программу ( main )"),			//+
		ERROR_ENTRY(126, "[LEX_ANALYSIS] Использование необъявленного идентификатора"),						//+
		ERROR_ENTRY(127, "[LEX_ANALYSIS] Неверное оъявление параметров"), 									//+
		ERROR_ENTRY(128, "[LEX_ANALYSIS] Не найдена закрывающая кавычка строкового литерала"),				//+
		ERROR_ENTRY(129, "[LEX_ANALYSIS] Запрещенный элемент в глобальной области видимости"), 
		ERROR_ENTRY_NODEF10(130),
		ERROR_ENTRY_NODEF10(140),
		ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),
		ERROR_ENTRY_NODEF10(170),
		ERROR_ENTRY_NODEF10(180),
		ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300),
		ERROR_ENTRY_NODEF100(400),
		ERROR_ENTRY_NODEF100(500),

		//------------------LEXICAL ANALYSE


		//------------------SYNTAX ANAL	( 600 - 100 )

		ERROR_ENTRY(600, "[SYNTAX_ANALYSIS] Неверная структура программы"),								  //+
		ERROR_ENTRY(601, "[SYNTAX_ANALYSIS] Ошибочный оператор"),										  //+
		ERROR_ENTRY(602, "[SYNTAX_ANALYSIS] Ошибка в выражении"),										  //+
		ERROR_ENTRY(603, "[SYNTAX_ANALYSIS] Ошибка в параметрах функции"),								  //+
		ERROR_ENTRY(604, "[SYNTAX_ANALYSIS] Ошибка в параметрах вызываемой функции"),					  //+
		ERROR_ENTRY_NODEF(605),
		ERROR_ENTRY_NODEF(606),
		ERROR_ENTRY_NODEF(607),
		ERROR_ENTRY_NODEF(608),
		ERROR_ENTRY_NODEF(609),
		ERROR_ENTRY_NODEF10(610),	ERROR_ENTRY_NODEF10(620),	ERROR_ENTRY_NODEF10(630),
		ERROR_ENTRY_NODEF10(640),	ERROR_ENTRY_NODEF10(650),	ERROR_ENTRY_NODEF10(660),
		ERROR_ENTRY_NODEF10(670),	ERROR_ENTRY_NODEF10(680),	ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700),	ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)

		//------------------SYNTAX ANALYSYS
	};

	ERROR geterror(int id)
	{
		if (0 < id < ERROR_MAX_ENTRY)
			return errors[id];
		else
			return ERROR_ENTRY(0, "");
	}

	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		ERROR e;

		if (0 < id < ERROR_MAX_ENTRY)
		{
			e = errors[id];
			e.errorPosition.col = col;
			e.errorPosition.line = line;
			return e;
		}
		else
			return ERROR_ENTRY(0, "");
	}
}