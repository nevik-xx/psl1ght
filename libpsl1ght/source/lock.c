#include <stdio.h>
#include <sys/reent.h>
#include <lv2/mutex.h>

int psl1ght_lwmutex_create_r(struct _reent* r, sys_lwmutex_t* lwmutex, const sys_lwmutex_attr_t* attr)
{
	return sysLwMutexCreate(lwmutex,attr);
}

int psl1ght_lwmutex_destroy_r(struct _reent* r, sys_lwmutex_t* lwmutex)
{
	return sysLwMutexDestroy(lwmutex);
}

int psl1ght_lwmutex_lock_r(struct _reent* r, sys_lwmutex_t*lwmutex, unsigned long long timeout)
{
	return sysLwMutexLock(lwmutex,timeout);
}

int psl1ght_lwmutex_trylock_r(struct _reent* r, sys_lwmutex_t* lwmutex)
{
	return sysLwMutexTryLock(lwmutex);
}

int psl1ght_lwmutex_unlock_r(struct _reent* r, sys_lwmutex_t* lwmutex)
{
	return sysLwMutexUnlock(lwmutex);
}
