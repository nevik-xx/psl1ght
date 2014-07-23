#ifndef __REALITY_PROGRAM_H__
#define __REALITY_PROGRAM_H__

#include <psl1ght/types.h>

//Param types
#define PARAM_FLOAT				0
#define PARAM_FLOAT2				1
#define PARAM_FLOAT3				2
#define PARAM_FLOAT4				3
#define PARAM_FLOAT4x4			4
#define PARAM_SAMPLER1D			5
#define PARAM_SAMPLER2D			6
#define PARAM_SAMPLER3D			7
#define PARAM_SAMPLERCUBE		8
#define PARAM_SAMPLERRECT		9
#define PARAM_UNKNOWN			0xff


#ifdef __cplusplus
extern "C" {
#endif

typedef struct reality_vp
{
	u16 magic;
	u16 num_attrib;
	u32 attrib_off;

	u32 input_mask;
	u32 output_mask;

	u16 const_start;
	u16 num_const;
	u32 const_off;

	u16 start_insn;
	u16 num_insn;
	u32 ucode_off;
} realityVertexProgram;

typedef struct reality_fp
{
	u16 magic;
	u16 num_attrib;
	u32 attrib_off;

	u32 num_regs;
	u32 fp_control;

	u16 _pad0;

	u16 num_const;
	u32 const_off;

	u16 num_insn;
	u32 ucode_off;
} realityFragmentProgram;

typedef struct reality_const
{
	u32 name_off;
	u32 index;
	u8 type;
	u8 is_internal;
	u8 count;

	u8 _pad0;
	
	union {
		u32 u;
		f32 f;
	} values[4];

} realityProgramConst;

typedef struct reality_co_table
{
	u32 num;
	u32 offset[];
} realityConstOffsetTable;

typedef struct reality_attrib
{
	u32 name_off;
	u32 index;
} realityProgramAttrib;



void *realityVertexProgramGetUCode(realityVertexProgram *vertexprogram);
u32 realityVertexProgramGetInputMask(realityVertexProgram *vertexprogram);
u32 realityVertexProgramGetOutputMask(realityVertexProgram *vertexprogram);
realityProgramAttrib *realityVertexProgramGetAttributes(realityVertexProgram *vertexprogram);
s32 realityVertexProgramGetAttribute(realityVertexProgram *vertexprogram,const char *name);
realityProgramConst *realityVertexProgramGetConstants(realityVertexProgram *vertexprogram);
s32 realityVertexProgramGetConstant(realityVertexProgram *vertexprogram,const char *name);

void* realityFragmentProgramGetUCode(realityFragmentProgram *fp,u32 *size);
realityProgramConst* realityFragmentProgramGetConsts(realityFragmentProgram *fp);
s32 realityFragmentProgramGetConst(realityFragmentProgram *fp,const char *name);
realityProgramAttrib* realityFragmentProgramGetAttribs(realityFragmentProgram *fp);
s32 realityFragmentProgramGetAttrib(realityFragmentProgram *fp,const char *name);

realityConstOffsetTable* realityFragmentProgramGetConstOffsetTable(realityFragmentProgram *fp,u32 table_off);

#ifdef __cplusplus
	}
#endif

#endif
