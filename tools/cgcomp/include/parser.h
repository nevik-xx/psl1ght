#ifndef __PARSER_H__
#define __PARSER_H__

#include <list>
#include <stack>
#include <string>
#include <sstream>

#include "nv30_vertprog.h"
#include "nv40_vertprog.h"
#include "nv30-40_3d.xml.h"

/** For GL_NV_vertex_program */
/*@{*/
#define MAX_NV_VERTEX_PROGRAM_INSTRUCTIONS 256
#define MAX_NV_VERTEX_PROGRAM_TEMPS         16
#define MAX_NV_VERTEX_PROGRAM_PARAMS        96
#define MAX_NV_VERTEX_PROGRAM_INPUTS        16
#define MAX_NV_VERTEX_PROGRAM_OUTPUTS       15
/*@}*/

/** For GL_NV_fragment_program */
/*@{*/
#define MAX_NV_FRAGMENT_PROGRAM_INSTRUCTIONS 1024 /* 72 for GL_ARB_f_p */
#define MAX_NV_FRAGMENT_PROGRAM_TEMPS         96
#define MAX_NV_FRAGMENT_PROGRAM_PARAMS        64
#define MAX_NV_FRAGMENT_PROGRAM_INPUTS        12
#define MAX_NV_FRAGMENT_PROGRAM_OUTPUTS        3
#define MAX_NV_FRAGMENT_PROGRAM_WRITE_ONLYS    2
/*@}*/

enum eparams { PARAM_FLOAT = 0,PARAM_FLOAT2,PARAM_FLOAT3,PARAM_FLOAT4,PARAM_FLOAT4x4,PARAM_SAMPLER1D,PARAM_SAMPLER2D,PARAM_SAMPLER3D,PARAM_SAMPLERCUBE,PARAM_SAMPLERRECT };

typedef struct _jmpdst
{
	char ident[64];
	u32 location;
} jmpdst;

typedef struct _paramtype
{
	const char *ident;
	enum eparams type;
} paramtype;

typedef struct _param
{
	std::string name;
	u8 is_const;
	u8 is_internal;
	u8 type;
	u32 index;
	f32 (*values)[4];
	u32 count;
	u32 user;
} param;

typedef struct _ioset
{
	const char *name;
	int index;
} ioset;

typedef struct _opcode opcode;

class CParser
{
public:
	CParser();
	virtual ~CParser();

	virtual int Parse(const char *str) = 0;

	int GetInstructionCount() const { return m_nInstructions; }
	struct nvfx_insn* GetInstructions() const { return m_pInstructions; }

	std::list<param> GetParameters() const {return m_lParameters;}

protected:
	void ParseComment(const char *line);

	const char* ParseTempReg(const char *token,s32 *idx);
	const char* ConvertCond(const char *token,struct nvfx_insn *insn);
	const char* ParseMaskedDstRegExt(const char *token,struct nvfx_insn *insn);
	const char* ParseCond(const char *token,struct nvfx_insn *insn);

	s32 GetParamType(const char *param_str);
	virtual s32 ConvertInputReg(const char *token) = 0;
	virtual const char* ParseOutputMask(const char *token,u8 *mask) = 0;

	void InitInstruction(struct nvfx_insn *insn,u8 op);
	void InitParameter(param *p);

	bool isLetter(int c);
	bool isDigit(int c);
	bool isWhitespace(int c);

	inline char* SkipSpaces(char *ptr)
	{
		while(ptr && *ptr==' ') {
			ptr++;
		}
		return ptr;
	}

	int m_nOption;
	int m_nInstructions;
	struct nvfx_insn *m_pInstructions;

	std::list<jmpdst> m_lJmpDst;
	std::list<jmpdst> m_lIdent;

	std::list<param> m_lParameters;
};

#endif
