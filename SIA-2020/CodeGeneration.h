#pragma once
#include "stdafx.h"

#define	HEAD ".586\n\t.model flat, stdcall\n\tincludelib libucrt.lib\n\tincludelib kernel32.lib\n\tincludelib ..\\Debug\\LIB.lib\n\tExitProcess PROTO :DWORD\n\n"

#define LIBPROTOS "\outStreamW PROTO: DWORD\n\outStreamN PROTO: DWORD\n\stringLen PROTO: DWORD\n\lexStrCmp PROTO: DWORD, :DWORD\n.stack 4096\n"

#define CONST ".CONST\n\tnull_division BYTE \'ERROR: DIVISION BY ZERO\', 0\n\tOVER_FLOW BYTE \'ERROR: OVERFLOW\', 0\n"

#define END \
"\n\tpush 0"\
"\n\tcall ExitProcess"\
"\nSOMETHINGWRONG::"\
"\n\tpush offset null_division"\
"\n\tcall outStreamW"\
"\njmp konec"\
"\noverflow::"\
"\n\tpush offset OVER_FLOW"\
"\n\tcall outStreamW"\
"\nkonec:"\
"\n\tpush -1"\
"\n\tcall ExitProcess"\
"\nmain ENDP\nend main"

namespace Generation
{
	void CodeGeneration(Scanner::Tables& tables);
}