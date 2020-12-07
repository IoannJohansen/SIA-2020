#pragma once
#define IN_MAX_LEN_TEXT 2048
#define IN_CODE_ENDL '\n'

namespace In
{
#define IN_CODE_TABLE {\
	/*0		  1		  2		  3		  4		  5		  6		  7		  8		  9	     A		  B	      C	      D	      E		  F*/\
	IN::E,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::S,	IN::S,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
	IN::S,	IN::V,	IN::F,	IN::F,	IN::F,	IN::V,	IN::V,	IN::Q,	IN::B,	IN::B,	IN::V,	IN::V,	IN::B,	IN::V,	IN::F,	IN::V,\
	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::F,	IN::B,	IN::V,	IN::V,	IN::V,	IN::F,\
	IN::F,	IN::F,	IN::F,	IN::T,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::T,	IN::F,	IN::F,	IN::F,\
	IN::F,	IN::F,	IN::F,	IN::T,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::B,	IN::F,	IN::B,	IN::F,	IN::F,\
	IN::F,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::B,	IN::F,	IN::B,	IN::F,	IN::F,\
	\
	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,\
	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F,	IN::F \
	};
	struct IN
	{
		enum { T = -1, V = -2, S = -3, B = -4, E = -5, F = -6, Q = -7};
		int size = 0;
		int lines = 1;
		int ignor = 0;
		unsigned char* text = new unsigned char[IN_MAX_LEN_TEXT];
		int code[256] = IN_CODE_TABLE;
	};
	IN getin(wchar_t* infile);
}