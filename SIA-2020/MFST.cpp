#include "MFST.h"
template<class T>T getStackElement(const std::stack<T>& st, size_t element)
{
	using base = std::stack<T>;
	struct acces : base { using base::c; };
	return (st.* & acces::c)[element];
}

namespace MFST
{
	MfstState::MfstState()									 // конструктор по умолчанию
	{
		lenta_position = 0;									 //позиция на ленте
		nrule = -1;											 //номер текущего правила
		nrulechain = -1;									 //номер текущей цепочки
	}

	MfstState::MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain)	//конструктор (позиция на ленте, стек автомата, номер текущей цепочки и текущего правила)
	{
		lenta_position = pposition;						//позиция на ленте
		st = pst;										//стек автомата
		nrulechain = pnrulechain;						//номер текущего правила и цепочки
	}

	MfstState::MfstState(short pposition, MFSTSTSTACK pst, short pnrule, short pnrulechain)
	{						//конструктор (позиция на ленте, стек автомата,номер текущего правила, номер текущей цепочки)
		lenta_position = pposition;						//позиция в ленте
		st = pst;										//стек автомата
		nrule = pnrule;									//номер текущего правила
		nrulechain = pnrulechain;						//номер текущей цепочки
	}

	Mfst::MfstDiagnosis::MfstDiagnosis()
	{
		lenta_position = -1;
		rc_step = SURPRICE;
		nrule = -1;
		nrule_chain = -1;
	}

	Mfst::MfstDiagnosis::MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain)  //диагностика
	{						    //(позиция на ленте, код завершения шага, номер правила, номер цепочки правила)
		lenta_position = plenta_position;		//позиция на ленте
		rc_step = prc_step;						//код завершения шага
		nrule = pnrule;							//номер правила
		nrule_chain = pnrule_chain;				//номер цепочки правила
	}

	Mfst::Mfst() { lenta = 0; lenta_size = lenta_position = 0; }		  //конструктор по умолчанию 

	Mfst::Mfst(Scanner::Tables plex, GRB::Greibach pgrebach)				  //(результат работы лексического анализатора, грамматика Грейбах)
	{
		grebach = pgrebach;												   //Грейбах
		Scanner = plex;														   //рез работы лекс анализатора
		lenta = new short[lenta_size = Scanner.lexTable.size];				   //размер ленты = текущий размер таблицы лексем
		using namespace GRB;
		for (int k = 0; k < lenta_size; ++k)							   //заносит в ленту терминалы
			lenta[k] = TS(Scanner.lexTable.table[k].lexema);
		lenta_position = 0;
		st.push(grebach.stbottomT);											//добавляет дно стека
		st.push(grebach.startN);											//добавляет стартовый символ
		nrulechain = -1;													//изначально правило равно -1
	}

	Mfst::RC_STEP Mfst::step()												//выполнить шаг автомата
	{
		RC_STEP rc = SURPRICE;												//код возврата = ошибка возврата
		if (lenta_position < lenta_size)
		{
			if (ISNS(st.top()))							  //извлекаем последний элемент стека и проверяем нетерминал ли он
			{
				GRB::Rule rule;
				if ((nrule = grebach.getRule(st.top(), rule)) >= 0)	 //смотрим, если такое правило есть идём дальше, если нет то елсе
				{
					GRB::Rule::Chain chain;
					if ((nrulechain = rule.getNextChain(lenta[lenta_position], chain, nrulechain + 1)) >= 0)
					{									   //получаем следующую цепочку и выводим её номер, либо возвращаем -1
						char lbuf[256];
						char rbuf[256];
						char sbuf[256];
						MFST_TRACE1						   //вывод
							savestate();				   //сохранить состояние автомата
						st.pop();						   //извлекаем верхушку стека.
						push_chain(chain);				   //поместить цепочку правила в стек
						rc = NS_OK;						//найдено правило и цепочка... цепочка записана в стек
						MFST_TRACE2					  //вывод
					}
					else
					{
						MFST_TRACE4("TNS_NORULECHAIN/NS_NORULE");	  //вывод
						savediagnosis(NS_NORULECHAIN);				//код завершения
						rc = restate() ? NS_NORULECHAIN : NS_NORULE; //восстановить состояние автомата
					}
				}
				else
				{
					rc = NS_ERROR;				   //неизвестный нетерминальный символ грамматики
				}
			}
			else if ((st.top() == lenta[lenta_position]))	  //если текущий символ ленты равен вершине стека
			{
				++lenta_position;							//продвигаем ленту
				st.pop();								   //вершина стека
				nrulechain = -1;						  //номер текущего правила равен -1
				rc = TS_OK;
				char sbuf[256], lbuf[256];
				MFST_TRACE3
			}
			else
			{
				MFST_TRACE4("TS_NOK/NS_NORULECHAIN");
				rc = restate() ? TS_NOK : NS_NORULECHAIN;
			}
		}
		else
		{
			rc = LENTA_END;
			MFST_TRACE4("LENTA_END");
		}
		return rc;
	}

	bool Mfst::push_chain(GRB::Rule::Chain chain)		 //поместить цепочку правила в стек (цепочка правила)
	{
		for (int k = chain.size - 1; k >= 0; --k)			//к = длинне цепочке-1. заносим цепочку в стек
			st.push(chain.nt[k]);
		return true;
	}

	bool Mfst::savestate()								   //сохранить состояние автомата
	{
		storestate.push(MfstState(lenta_position, st, nrule, nrulechain)); //стек для сохранения состояния. заносим сохраняемое состояние
		MFST_TRACE6("SAVESTATE:", storestate.size());
		return true;
	}

	bool Mfst::restate()							//восстановить состояние автомата
	{
		bool rc = false;
		MfstState state;
		if (rc = (storestate.size() > 0))
		{
			state = storestate.top();
			lenta_position = state.lenta_position;
			st = state.st;
			nrule = state.nrule;
			nrulechain = state.nrulechain;
			storestate.pop();
			MFST_TRACE5("RESTATE");
			char rbuf[256], lbuf[256], sbuf[256];
			MFST_TRACE2
		}
		return rc;
	}

	bool Mfst::savediagnosis(RC_STEP prc_step)
	{
		bool rc = false;
		short k = 0;
		while (k < MFST_DIAGN_NUMBER && lenta_position <= diagnosis[k].lenta_position)
			++k;
		if (rc = (k < MFST_DIAGN_NUMBER))
		{
			diagnosis[k] = MfstDiagnosis(lenta_position, prc_step, nrule, nrulechain);
			for (short j = k + 1; j < MFST_DIAGN_NUMBER; ++j)
				diagnosis[j].lenta_position = -1;
		}
		return rc;
	}

	bool Mfst::start()
	{
		bool rc = false;
		RC_STEP rc_step = SURPRICE;
		char buf[MFST_DIAGN_MAXSIZE];
		rc_step = step();
		while (rc_step == NS_OK || rc_step == NS_NORULECHAIN || rc_step == TS_OK || rc_step == TS_NOK)
			rc_step = step();
		switch (rc_step)
		{
		case LENTA_END:
			MFST_TRACE4("------->LENTA_END");
			std::cout << std::setfill('-') << std::setw(100) << ' ' << std::setfill(' ') << std::endl;
			sprintf_s(buf, MFST_DIAGN_MAXSIZE, "%d: всего строк %d, синтаксический анализ выполнен без ошибок", 0, lenta_size);
			std::cout << buf << std::endl;
			rc = true;
			break;
		case NS_NORULE:
			MFST_TRACE4("------>NS_NORULE");
			std::cout << std::setfill('-') << std::setw(100) << ' ' << std::setfill(' ') << std::endl;
			throw getDiagnosis(buf);
			break;
		case NS_NORULECHAIN:
			MFST_TRACE4("------>NS_NORULENORULECHAIN");
			break;
		case NS_ERROR:
			MFST_TRACE4("------>NS_ERROR");
			break;
		case SURPRICE:
			MFST_TRACE4("------>SURPRICE");
			break;
		}
		return rc;
	}

	char* Mfst::getCSt(char* buf)	//заполняет буфер содержимым стека для отображения
	{
		for (int k = (signed)st.size() - 1; k >= 0; --k)
		{
			short p = getStackElement(st, k);
			buf[st.size() - 1 - k] = GRB::Rule::Chain::alphabet_to_char(p);
		}
		buf[st.size()] = 0x00;
		return buf;
	}

	char* Mfst::getCLenta(char* buf, short pos, short n)	//заполняет буфер содержимым ленты с заданной позиции заданное количество символов  для отображения,
	{
		short i, k = (pos + n < lenta_size) ? pos + n : lenta_size;
		for (i = pos; i < k; ++i)
			buf[i - pos] = GRB::Rule::Chain::alphabet_to_char(lenta[i]);
		buf[i - pos] = 0x00;
		return buf;
	}

	char* Mfst::getDiagnosis(char* buf)
	{
		char* temp = new char[300];
		temp[0] = '\0';
		int errid = 0;
		int lpos = -1;
		for (int i = 0; i < 3; i++)
		{
			if (i < MFST_DIAGN_NUMBER && (lpos = diagnosis[i].lenta_position) >= 0)
			{
				errid = grebach.getRule(diagnosis[i].nrule).iderror;
				Error::ERROR err = Error::geterror(errid);
				sprintf_s(buf, MFST_DIAGN_MAXSIZE, "Ошибка %d : %s\n Строка %d | Позиция %d\n", err.id, err.message, Scanner.lexTable.table[lpos].sn, Scanner.lexTable.table[lpos].posInStr);
				strcat_s(temp, 300, buf);
			}
		}
		return temp;
	}

	void Mfst::printrules()
	{
		MfstState state;
		GRB::Rule rule;
		for (unsigned short k = 0; k < storestate.size(); ++k)
		{
			state = getStackElement(storestate, k);
			rule = grebach.getRule(state.nrule);
			char rbuf[256];
			MFST_TRACE7
		}
	}

	bool Mfst::savededucation()
	{
		MfstState state;
		GRB::Rule rule;
		deducation.nrules = new short[deducation.size = storestate.size()];
		deducation.nrulechains = new short[deducation.size];
		for (unsigned short k = 0; k < storestate.size(); ++k)
		{
			state = getStackElement(storestate, k);
			deducation.nrules[k] = state.nrule;
			deducation.nrulechains[k] = state.nrulechain;
		}
		return true;
	}
};