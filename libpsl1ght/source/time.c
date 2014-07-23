#include <psl1ght/lv2/timer.h>
#include <psl1ght/lv2/errno.h>

#include <errno.h>
#include <sys/time.h>

int psl1ght_gettimeofday_r(struct _reent* r, struct timeval * tv, void * unused)
{
	u64 sec, nsec;

	int ret = lv2GetCurrentTime(&sec, &nsec);

	if (ret)
		return lv2ErrnoReentrant(r, ret);

	tv->tv_sec = sec;
	tv->tv_usec = nsec / 1000;

	return 0;
}

int psl1ght_settimeofday_r(struct _reent* r, const struct timeval * tv, const struct timezone * tz)
{
	u64 sec, nsec;

	sec  = tv->tv_sec;
	nsec = tv->tv_usec * 1000;

	return lv2ErrnoReentrant(r, lv2SetCurrentTime(sec, nsec));
}
