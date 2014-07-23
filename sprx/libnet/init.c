#include <psl1ght/lv2.h>
#include <psl1ght/lv2/errno.h>
#include <net/net.h>

#include <stdlib.h>
#include <string.h>

#include <sysmodule/sysmodule.h>

#define LIBNET_MEMORY_SIZE 0x20000 // 128KB
extern void* __netMemory;
int netInitialize()
{
	if (__netMemory)
		return 0;
	
	s32 ret = SysLoadModule(SYSMODULE_NET);
	if (ret < 0)
		return lv2Errno(ret);

	__netMemory = malloc(LIBNET_MEMORY_SIZE);
	netInitialization init;
	memset(&init, 0, sizeof(init));
	init.memory = (lv2_void)(u64)__netMemory;
	init.memory_size = LIBNET_MEMORY_SIZE;
	init.flags = 0;
	ret = netInitializeNetworkEx(&init);
	if (ret) {
		free(__netMemory);
		__netMemory = NULL;
	}
	return ret;
}

int netDeinitialize()
{
	netFinalizeNetwork();
	if (__netMemory)
		free(__netMemory);
	__netMemory = NULL;

	SysUnloadModule(SYSMODULE_NET);
	return 0;
}
