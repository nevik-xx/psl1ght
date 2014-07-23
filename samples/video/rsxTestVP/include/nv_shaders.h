#ifndef __NV_SHADERS_H__
#define __NV_SHADERS_H__

#include <rsx/commands.h>


/*******************************************************************************
 * NV30/NV40/G70 fragment shaders
 */

static realityFragmentProgram_old nv30_fp = {
.num_regs = 2,
.size = (2*4),
.data = {
/* TEX R0, fragment.texcoord[0], texture[0], 2D */
0x17009e00, 0x1c9dc801, 0x0001c800, 0x3fe1c800,
/* MOV R0, R0 */
0x01401e81, 0x1c9dc800, 0x0001c800, 0x0001c800,
}
};

#endif
