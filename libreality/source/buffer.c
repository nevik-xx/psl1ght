#include <rsx/buffer.h>
#include <assert.h>

s32 __attribute__((noinline)) rsxContextCallback(gcmContextData *context,u32 count)
{
	register s32 result asm("3");
	asm volatile (
		"stdu	1,-128(1)\n"
		"mr		31,2\n"
		"lwz	0,0(%0)\n"
		"lwz	2,4(%0)\n"
		"mtctr	0\n"
		"bctrl\n"
		"mr		2,31\n"
		"addi	1,1,128\n"
		: : "b"(context->callback)
		: "r31", "r0", "r1", "r2", "lr"
	);
	return result;
}

void commandBufferPut(gcmContextData* context, uint32_t value) {
	uint32_t* buffer = (uint32_t *)(uint64_t) context->current;
	*buffer++ = value;
	context->current = (uint32_t)(uint64_t) buffer;
}

