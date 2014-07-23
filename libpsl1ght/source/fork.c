#include <unistd.h>
#include <sys/reent.h>
#include <errno.h>

pid_t _fork_r(struct _reent* r)
{
	r->_errno = ENOSYS;
	return -1;
}
