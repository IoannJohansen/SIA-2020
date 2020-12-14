#include "stdafx.h"
//показываем что это вызов функции как на языке C

extern "C"
{
	int __stdcall stringLen(char* source)
	{
		int result = 0;
		while (source[result] != '\0')
		{
			result++;
		}
		return result;
	}

	int __stdcall lexStrCmp(char* source1, char* source2)
	{
		return -strcmp(source1, source2);
	}

	int __stdcall outStreamW(char* value)
	{
		setlocale(0, "");
		std::cout << value << std::endl;
		return 0;
	}

	int __stdcall outStreamN(int value)
	{
		std::cout << value << std::endl;
		return 0;
	}
}