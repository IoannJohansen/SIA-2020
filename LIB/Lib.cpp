#include "stdafx.h"
//показываем что это вызов функции как на языке C

extern "C"
{

	int __stdcall strln(char* source)
	{
		int result = 0;
		while (source[result] != '\0')
		{
			result++;
		}
		return result;
	}

	int __stdcall Strcmp(char* source1, char* source2)
	{
		int i = 0;
		while (source1[i] != '\0')
		{
			if (source1[i] != source2[i])
			{
				return -1;
			}
			i++;
		}
		return 0;

	}

	int __stdcall readw(char* value)
	{
		setlocale(0, "");
		std::cout << value << std::endl;
		return 0;
	}

	int __stdcall readr(int value)
	{
		std::cout << value << std::endl;
		return 0;
	}
}