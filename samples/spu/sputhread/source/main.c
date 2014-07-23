#include <psl1ght/lv2.h>
#include <psl1ght/lv2/spu.h>
#include <lv2/spu.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "spu.bin.h"

#define ptr2ea(x) ((u64)(void *)(x))

int main(int argc, const char* argv[])
{
	sysSpuImage image;
	u32 entry = 0;
	u32 segmentcount = 0;
	sysSpuSegment* segments;
	u32 thread_id;
	u32 group_id;
	Lv2SpuThreadAttributes attr = { ptr2ea("mythread"), 8+1, LV2_SPU_THREAD_ATTRIBUTE_NONE };
	Lv2SpuThreadArguments arg = { 0, 0, 0, 0 };
	Lv2SpuThreadGroupAttributes grpattr = { 7+1, ptr2ea("mygroup"), 0, 0 };
	u32 cause, status;
	static vu32 sync __attribute__((aligned(16)));
	static vu32 response __attribute__((aligned(16)));

	printf("Initializing 6 SPUs... ");
	printf("%08x\n", lv2SpuInitialize(6, 0));

	printf("Getting ELF information... ");
	printf("%08x\n", sysSpuElfGetInformation(spu_bin, &entry, &segmentcount));
	printf("\tEntry Point: %08x\n\tSegment Count: %08x\n", entry, segmentcount);

	size_t segmentsize = sizeof(sysSpuSegment) * segmentcount;
	segments = (sysSpuSegment*)malloc(segmentsize);
	memset(segments, 0, segmentsize);

	printf("Getting ELF segments... ");
	printf("%08x\n", sysSpuElfGetSegments(spu_bin, segments, segmentcount));

	printf("Loading ELF image... ");
	printf("%08x\n", sysSpuImageImport(&image, spu_bin, 0));

	printf("Creating thread group... ");
	printf("%08x\n", lv2SpuThreadGroupCreate(&group_id, 1, 100, &grpattr));
	printf("group id = %d\n", group_id);

	arg.argument1 = ptr2ea(&sync);
	arg.argument2 = ptr2ea(&response);

	printf("Creating SPU thread... ");
	printf("%08x\n", lv2SpuThreadInitialize(&thread_id, group_id, 0, &image, &attr, &arg));
	printf("thread id = %d\n", thread_id);

	printf("Configuring SPU... %08x\n",
	lv2SpuThreadSetConfiguration(thread_id, LV2_SPU_SIGNAL1_OVERWRITE|LV2_SPU_SIGNAL2_OVERWRITE));

	printf("Starting SPU thread group... ");
	printf("%08x\n", lv2SpuThreadGroupStart(group_id));

	sync = 0;
	printf("Sending value 42... %08x\n",
		lv2SpuThreadWriteSignal(thread_id, 0, 42));

	printf("Waiting for SPU to return...\n");
	while (sync == 0);

	printf("output value = %d\n", response);

	printf("Joining SPU thread group... ");
	printf("%08x\n", lv2SpuThreadGroupJoin(group_id, &cause, &status));
	printf("cause=%d status=%d\n", cause, status);

	printf("Closing image... ");
	printf("%08x\n", sysSpuImageClose(&image));

	return 0;
}
