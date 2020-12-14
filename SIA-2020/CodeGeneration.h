#pragma once
#include "stdafx.h"

#define	HEAD ".586\n.model flat, stdcall\nincludelib libucrt.lib\nincludelib kernel32.lib\nincludelib ..\\Debug\\LIB.lib\nExitProcess PROTO :DWORD"

#define LIBPROTOS "\noutStreamW PROTO: SDWORD\noutStreamN PROTO: DWORD\nstringLen PROTO: DWORD\nlexStrCmp PROTO: DWORD, :DWORD\n.stack 4096"

#define CONST "\n.CONST\nnull_division BYTE \'ERROR: DIVISION BY ZERO\', 0\n\tOVER_FLOW BYTE \'ERROR: OVERFLOW\', 0\n"

#define END \
"\n\tcall ExitProcess"\
"\nSOMETHINGWRONG:"\
"\n\tpush offset null_division"\
"\n\tcall outStreamW"\
"\n\tjmp konec"\
"\nkonec:"\
"\n\tpush -1"\
"\n\tcall ExitProcess"\
"\nmain ENDP\nend main"

namespace Generation
{
	void CodeGeneration(Scanner::Tables& tables);
}