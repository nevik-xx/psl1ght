#include "string.h"
#include "rsx/reality_program.h"

void *realityVertexProgramGetUCode(realityVertexProgram *vertexprogram)
{
	unsigned char *ptr=(unsigned char *)vertexprogram;

	return (void*)(ptr+vertexprogram->ucode_off);
}

u32 realityVertexProgramGetInputMask(realityVertexProgram *vertexprogram)
{
	return vertexprogram->input_mask;
}

u32 realityVertexProgramGetOutputMask(realityVertexProgram *vertexprogram)
{
	return vertexprogram->output_mask;
}

realityProgramAttrib *realityVertexProgramGetAttributes(realityVertexProgram *vertexprogram)
{
	return (realityProgramAttrib*) (((unsigned char*)vertexprogram)+vertexprogram->attrib_off);
}

s32 realityVertexProgramGetAttribute(realityVertexProgram *vertexprogram,const char *name)
{
	int i;
	realityProgramAttrib *attributes = realityVertexProgramGetAttributes(vertexprogram);
	for(i=0;i<vertexprogram->num_attrib;++i)
	{
		char *namePtr;
		if(attributes[i].name_off==0)
			continue;
		namePtr=((char*)vertexprogram)+attributes[i].name_off;
		if(strcasecmp(name,namePtr)==0)
			return attributes[i].index;
	}

	return -1;
}

realityProgramConst *realityVertexProgramGetConstants(realityVertexProgram *vertexprogram)
{
	return (realityProgramConst*) (((unsigned char*)vertexprogram)+vertexprogram->const_off);
}

s32 realityVertexProgramGetConstant(realityVertexProgram *vertexprogram,const char *name)
{
	s32 i;
	realityProgramConst *constants = realityVertexProgramGetConstants(vertexprogram);

	for(i=0;i<vertexprogram->num_const;++i)
	{
		char *namePtr;
		if(constants[i].name_off==0)
			continue;
		namePtr=((char*)vertexprogram)+constants[i].name_off;
		if(strcasecmp(name,namePtr)==0)
			return i;
	}

	return -1;
}