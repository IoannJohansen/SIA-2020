#pragma once
#include "stdafx.h"
#define	HEAD ".586\n\t.model flat, stdcall\n\tincludelib libucrt.lib\n\tincludelib kernel32.lib\n\tincludelib ..\\Debug\\Lib.lib\n\tExitProcess PROTO :DWORD\n\n"
#define LIBPROTOS "\treadw PROTO: DWORD\n\treadr PROTO: DWORD\n\tstrln PROTO: DWORD\n\tStrcmp PROTO: DWORD, :DWORD\n.stack 4096\n"
#define CONST ".const\n"
namespace Generation
{
	void CodeGeneration(Scanner::Tables& tables);



}