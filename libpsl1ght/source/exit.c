#include <unistd.h>

#include <lv2/process.h>

void _fini();

void psl1ght_exit(int status)
{
	_fini();
	sysProcessExit(status);
}
