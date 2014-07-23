#include <unistd.h>
#include <sys/reent.h>
#include <errno.h>

pid_t _wait_r(struct _reent* r, int* status)
{
	r->_errno = ENOSYS;
	return -1;
}

