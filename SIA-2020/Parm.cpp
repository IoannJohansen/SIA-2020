#include <wchar.h>
#include "Parm.h"
#include "Error.h"
#pragma warning(disable: 4996)

namespace Parm
{
	PARM getparm(int argc, wchar_t* argv[])
	{
		PARM parm;
		wchar_t* log = nullptr;
		wchar_t* sin = nullptr;
		wchar_t* in = nullptr;

		for (int i = 1; i < argc; i++)
		{
			if (argv[i] && wcslen(argv[i]) < PARM_MAX_SIZE)
			{
				if (wcsstr(argv[i], PARM_IN))
				{
					in = wcsstr(argv[i], PARM_IN);
					wcscpy(parm.in, argv[i] + wcslen(PARM_IN));
				}
				if (wcsstr(argv[i], PARM_SIN))
				{
					sin = wcsstr(argv[i], PARM_SIN);
					wcscpy(parm.sin, argv[i] + wcslen(PARM_SIN));
				}
				if (wcsstr(argv[i], PARM_LOG))
				{
					log = wcsstr(argv[i], PARM_LOG);
					wcscpy(parm.log, argv[i] + wcslen(PARM_LOG));
				}
			}
			else
				throw ERROR_THROW(104);
		}

		if (in == nullptr) { throw ERROR_THROW(100) };
		if (sin == nullptr)
		{
			wcscpy_s(parm.sin, parm.in);
			wcscat_s(parm.sin, PARM_SIN_DEFAULT_EXT);
		}
		if (log == nullptr)
		{
			wcscpy_s(parm.log, parm.in);
			wcscat_s(parm.log, PARM_LOG_DEFAULT_EXT);
		}
		return parm;
	}
}