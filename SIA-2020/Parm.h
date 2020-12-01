#pragma once
#define PARM_MAX_SIZE 300

#define PARM_IN		L"-in:"
#define PARM_SIN	L"-sin:"
#define PARM_LOG	L"-log:"

#define PARM_SIN_DEFAULT_EXT L".sin"
#define PARM_LOG_DEFAULT_EXT L".log"

namespace Parm
{
	struct PARM
	{
		wchar_t in[PARM_MAX_SIZE];
		wchar_t sin[PARM_MAX_SIZE];
		wchar_t log[PARM_MAX_SIZE];
	};

	PARM getparm(int argc, wchar_t* argv[]);
}