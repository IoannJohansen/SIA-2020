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
		
		//TODO: delete <> from LEX_ARITHMETIC					|	+
		//TODO: add to name of literals - L[#lit]				|	+
		//TODO: add to name of id - name of parrent block		|	

		Scanner::Words* words = Scanner::TextDivision(in);
		Scanner::Tables tables = Scanner::GetTables(words);

		//-------------------------


		//-------SYNTAX ANALYSE----								
		//TODO: fix chanes with literals and less|more|<>		|	+


		log = Log::getlog(param.sin);
		MFST_TRACE_START(log);								
		MFST::Mfst mfst(tables, GRB::getGreibach());	
		mfst.start(log);
		mfst.savededucation();
		mfst.printrules(log);
		Log::Close(log);

		//-------------------------
		
		//-------SEMANTIC ANALYSE----

		// TODO: add processing of right sequence with outStream		|	+
		// TODO: add processing of right sequence of block IF-ELSE		|	+
		// TODO: add processing of according of libFoo's and variables	|	+
		// TODO: add processing of value for return in procedures		|	+
		// TODO: fix processing of value for out from entry				|	+
		
		Semantic::SemanticAnalysis(&tables);
		

		//---------------------------
		
		//-------POLISH NOTATION---

		PN::PolishNotation(tables);

		//-------------------------
		
		//-------CODE GENERATION

		Generation::CodeGeneration(tables);
		

		//-------CODE GENERATION
		IT::ShowTable(tables.idenTable);
		tables.idenTable.writeIT(param.in);
		tables.lexTable.writeLT(param.in);
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