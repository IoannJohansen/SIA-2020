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
		Scanner::Words* tokens = Scanner::DivisionIntoTokens(in);
		Scanner::Tables lex = Scanner::LexAnalysis(tokens);
		//-------------------------
		
		//-------SYNTAX ANALYSE----								
		log = Log::getlog(param.sin);
		MFST_TRACE_START(log);								
		MFST::Mfst mfst(lex, GRB::getGreibach());	
		mfst.start(log);
		mfst.savededucation();
		mfst.printrules(log);
		Log::Close(log);
		//-------------------------

		//-------SEMANTIC ANALYSE--
		Semantic::SemanticAnalysis(&lex);
		//-------------------------
	
		//-------POLISH NOTATION---
		PN::PolishNotation(lex);
		//-------------------------

		//-------CODE GENERATION
		Generation::CodeGeneration(lex);
		//-------------------------

		IT::ShowTable(&lex.idenTable);
		lex.idenTable.writeIT(param.in);
		lex.lexTable.writeLT(param.in);
		LT::Delete(lex.lexTable);
		IT::Delete(lex.idenTable);
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