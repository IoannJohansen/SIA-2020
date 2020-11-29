#include "stdafx.h"
using namespace std;

int wmain(int argc, wchar_t* argv[])
{
	Log::LOG log = Log::INITLOG;
	setlocale(LC_ALL, "Russian");
	try
	{
		Parm::PARM param = Parm::getparm(argc, argv);
		log = Log::getlog(param.log);
		In::IN in = In::getin(param.in);


		//-------LEX ANALYSE-------
		
		Scanner::Words* words = Scanner::TextDivision(in);
		Scanner::Tables tables = Scanner::GetTables(words);

		//-------------------------


		//-------SYNTAX ANALYSE----
		MFST_TRACE_START;								
		MFST::Mfst mfst(tables, GRB::getGreibach());	
		mfst.start();
		//-------------------------


		//-------POLISH NOTATION---

		PN::PolishNotation(tables);

		//-------------------------

		
		
		tables.idenTable.writeIT(param.in);
		tables.lexTable.writeLT(param.in);
		Log::WriteLog(log);
		Log::WriteParm(log, param);
		Log::WriteIn(log, in);
		Log::Close(log);

		LT::Delete(tables.lexTable);
		IT::Delete(tables.idenTable);
	}
	catch (Error::ERROR e) 
	{
		Log::WriteError(log, e);
		if(e.id!=100)Log::Close(log);
	}
	catch (char* e)
	{
		Log::WriteError(log, e);
		Log::Close(log);
	}
	system("pause");
	return 0;
}