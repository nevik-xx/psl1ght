#ifndef __LV2_SYSUTIL_DISC_H__
#define __LV2_SYSUTIL_DISC_H__

#include <psl1ght/types.h>

EXTERN_BEGIN

typedef enum
{
	SYS_DISCTYPE_OTHER = 0,
	SYS_DISCTYPE_PS3,
	SYS_DISCTYPE_PS2
} sysDiscType;

typedef void (*sysDiscEjectCallback)(void);
typedef void (*sysDiscInsertCallback)(u32 discType,char *title);

s32 sysDiscRegisterDiscChangeCallback(sysDiscEjectCallback cbEject,sysDiscInsertCallback cbInsert);
s32 sysDiscUnregisterDiscChangeCallback();

EXTERN_END

#endif
