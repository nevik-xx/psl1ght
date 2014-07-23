#include "sysutil/events.h"
#include "sysutil/disc.h"
#include "io/msg.h"

s32 sysRegisterCallback(sysEventSlot slot, sysCallback func, void * userdata)
{
	return sysRegisterCallback_ex(slot, OPD32(func), userdata);
}

s32 msgDialogOpen(u32 type, const char * msg, msgDialog func, void * userdata, void *unused)
{
	return msgDialogOpen_ex(type, msg, OPD32(func), userdata, unused);
}

s32 msgDialogOpen2(u32 type, const char * msg, msgDialog func, void * userdata, void *unused)
{
	return msgDialogOpen2_ex(type, msg, OPD32(func), userdata, unused);
}

s32 msgDialogErrorCode(u32 errorcode, msgDialog func, void * userdata, void *unused)
{
    return msgDialogErrorCode_ex(errorcode, OPD32(func), userdata, unused);
}

/* Disc utility support */
extern s32 sysDiscRegisterDiscChangeCallbackEx(opd32 *cbEject,opd32 *cbInsert);

/* Disc utility support */
s32 sysDiscRegisterDiscChangeCallback(sysDiscEjectCallback cbEject,sysDiscInsertCallback cbInsert)
{
	return sysDiscRegisterDiscChangeCallbackEx(OPD32(cbEject), OPD32(cbInsert));
}

