#include "stdafx.h"
using namespace std;

int wmain(int argc, wchar_t* argv[])
{
	Log::LOG log = Log::INITLOG;
	setlocale(LC_ALL, "Russian");
	Parm::PARM param = Parm::getparm(argc, argv);
	try
	{
		log = Log::getlog(param.log);
		In::IN in = In::getin(param.in);
		Log::WriteLog(log);
		Log::WriteParm(log, param);
		Log::WriteIn(log, in);
		Log::Close(log);

		//-------LEX ANALYSE-------
		
		Scanner::Words* words = Scanner::TextDivision(in);
		Scanner::Tables tables = Scanner::GetTables(words);

		//-------------------------


		//-------SYNTAX ANALYSE----

		log = Log::getlog(param.sin);
		MFST_TRACE_START(log);								
		MFST::Mfst mfst(tables, GRB::getGreibach());	
		mfst.start(log);
		Log::Close(log);

		//-------------------------
		tables.idenTable.writeIT(param.in);
		tables.lexTable.writeLT(param.in);

		//-------SEMANTIC ANALYSE----

		Semantic::SemanticAnalysis(&tables);

		//---------------------------

		//-------POLISH NOTATION---

		//PN::PolishNotation(tables);

		//-------------------------
		


		LT::Delete(tables.lexTable);
		IT::Delete(tables.idenTable);
	}
	catch (Error::ERROR e) 
	{
		log = Log::getlog(param.log);
		Log::WriteError(log, e);
		if(e.id!=100)Log::Close(log);
	}
	catch (char* e)
	{
		Log::Close(log);
		log = Log::getlog(param.log);
		Log::WriteError(log, e);
		Log::Close(log);
	}
	system("pause");
	return 0;
}