#include "string.h"
#include "rsx/reality_program.h"

void* realityFragmentProgramGetUCode(realityFragmentProgram *fp,u32 *size)
{
	*size = fp->num_insn*sizeof(u32)*4;
	return (void*)(((u8*)fp) + fp->ucode_off);
}

realityProgramConst* realityFragmentProgramGetConsts(realityFragmentProgram *fp)
{
	return (realityProgramConst*)(((u8*)fp) + fp->const_off);
}

s32 realityFragmentProgramGetConst(realityFragmentProgram *fp,const char *name)
{
	u32 i;
	realityProgramConst *fpc = realityFragmentProgramGetConsts(fp);

	for(i=0;i<fp->num_const;i++) {
		char *namePtr;

		if(!fpc[i].name_off) continue;

		namePtr = ((char*)fp) + fpc[i].name_off;
		if(strcasecmp(name,namePtr)==0)
			return i;
	}
	return -1;
}

realityProgramAttrib* realityFragmentProgramGetAttribs(realityFragmentProgram *fp)
{
	return (realityProgramAttrib*)(((u8*)fp) + fp->attrib_off);
}

s32 realityFragmentProgramGetAttrib(realityFragmentProgram *fp,const char *name)
{
	u32 i;
	realityProgramAttrib *attribs = realityFragmentProgramGetAttribs(fp);

	for(i=0;i<fp->num_attrib;i++) {
		char *namePtr;

		if(!attribs[i].name_off) continue;

		namePtr = ((char*)fp) + attribs[i].name_off;
		if(strcasecmp(name,namePtr)==0)
			return attribs[i].index;
	}
	return -1;
}

realityConstOffsetTable* realityFragmentProgramGetConstOffsetTable(realityFragmentProgram *fp,u32 table_off)
{
	return (realityConstOffsetTable*)(((u8*)fp) + table_off);
}
