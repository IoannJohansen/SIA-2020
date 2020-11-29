#include <fstream>
#include <string>
#include "In.h"
#include "Error.h"
#include <iostream>

using namespace std;

namespace In
{
	IN getin(wchar_t* infile)
	{
		IN inner_text;

		ifstream file;
		file.open(infile);

		if (!file)
			throw ERROR_THROW(110);
		inner_text.text = new unsigned char[IN_MAX_LEN_TEXT];

		unsigned char tempChar;
		int position = 0;
		int positionArray = 0;
		bool flagEmptyFile = true;
		bool flagLiteral = false;

		while ((tempChar = file.get()) && !file.eof())
		{
			flagEmptyFile = false;
			if (tempChar == IN_CODE_ENDL)	// перенос строки
			{
				inner_text.text[positionArray++] = IN_CODE_ENDL;
				inner_text.size++;
				inner_text.lines++;
				position = 0;
				continue;
			}
			switch (inner_text.code[tempChar])
			{
			case IN::S:
			case IN::B:
			case IN::V:
			case IN::T:	// разрешение
			{
				inner_text.text[positionArray++] = tempChar;
				inner_text.size++;
				position++;
				break;
			}
			
			case IN::Q:
			{
				if (!flagLiteral)
				{
					flagLiteral = true;
				}
				else
				{
					flagLiteral = false;
				}
				inner_text.text[positionArray++] = tempChar;
				inner_text.size++;
				position++;
				break;
			}

			case IN::F:
			{	// запрет
				if (flagLiteral)
				{
					inner_text.text[positionArray++] = tempChar;
					inner_text.size++;
					position++;
					break;
				}
				throw ERROR_THROW_IN(111, inner_text.lines, position + 1);
				break;
			}

			default:
			{
				cout << tempChar << endl;
				inner_text.text[positionArray++] = inner_text.code[tempChar];
				inner_text.size++;
				position++;
				break;
			}
			}
		}
		inner_text.text[positionArray++] = '\0';
		if (flagEmptyFile)
			throw ERROR_THROW(113);

		if (inner_text.size == 0)
			inner_text.lines = 0;

		file.close();
		return inner_text;
	}
}
