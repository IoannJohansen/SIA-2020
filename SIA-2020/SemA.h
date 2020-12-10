#pragma once
#include "stdafx.h"
#define SEM_ERROR_SIRES 700
namespace Semantic
{
	struct Entry
	{
		int index;
		int countOfParam;
		IT::IDDATATYPE types[8];
	};


	struct Functions
	{
		int maxsize;
		int size;
		Entry* table;
	};

	Functions Create(int size);
	void SemanticAnalysis(Scanner::Tables* tables);
	void CheckTypesMapping(Scanner::Tables* tables);
	void FillFunction(Functions& functions, IT::IdTable& idenTables);
	void AddFunc(Functions& functions, Entry entry);
	void CheckFuncitionParams(Functions& functions, Scanner::Tables& tales);
	bool isEqual(Entry& entry1, Entry& entry2);
	void CheckBuiltInFunParam(LT::LexTable& lextable, IT::IdTable& idtable);
	void CheckForReturnType(LT::LexTable& lextable, IT::IdTable& idtable);
	void CheckCondAndStreams(LT::LexTable& lextable, IT::IdTable& idtable);
	void AddParrentBlockToId(IT::IdTable& idenTable);

}