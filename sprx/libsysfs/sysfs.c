#include <psl1ght/types.h>

s32 sysFsAioRead_ex(void *Aio, s32 *id, opd32* opdentry);
s32 sysFsAioWrite_ex(void *Aio, s32 *id, opd32* opdentry);

s32 sysFsAioRead(void *Aio, s32 *id, void (*func)(void *Aio, s32 error, s32 xid, u64 size))
{
	return sysFsAioRead_ex(Aio, id, OPD32(func));
}

s32 sysFsAioWrite(void *Aio, s32 *id, void (*func)(void *Aio, s32 error, s32 xid, u64 size))
{
	return sysFsAioWrite_ex(Aio, id, OPD32(func));
}


