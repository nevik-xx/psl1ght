#pragma once

#include <psl1ght/types.h>
#include <psl1ght/lv2/filesystem.h>

EXTERN_BEGIN

typedef struct sysFsAio {
  s32 fd;
  u64 offset;
  u32 addr_buffer;
  u64 size;
  u64 userdata;
} sysFsAio;


s32 sysFsOpen(const char* path, s32 oflags, Lv2FsFile* fd, const void* arg, u64 argsize);
s32 sysFsClose(Lv2FsFile fd);
s32 sysFsRead(Lv2FsFile fd, void* buf, u64 size, u64* read);
s32 sysFsWrite(Lv2FsFile fd, const void* buf, u64 size, u64* written);
s32 sysFsLseek(Lv2FsFile fd, s64 offset, s32 whence, u64* position);
s32 sysFsStat(const char* path, Lv2FsStat* buf);
s32 sysFsFstat(Lv2FsFile fd, Lv2FsStat* buf);
s32 sysFsChmod(const char* path, Lv2FsMode mode);
s32 sysFsMkdir(const char* path, Lv2FsMode mode);
s32 sysFsRmdir(const char *path);
s32 sysFsUnlink(const char *path);

s32 sysFsOpendir(const char *path, Lv2FsFile *fd);
s32 sysFsClosedir(Lv2FsFile fd);
s32 sysFsReaddir(Lv2FsFile fd, Lv2FsDirent* entry, u64* read);

s32 sysFsAioInit(const char * path);
s32 sysFsAioFinish(const char * path);
s32 sysFsAioCancel(s32 id);

s32 sysFsAioRead (sysFsAio *Aio, s32 *id, void (*func)(sysFsAio *Aio, s32 error, s32 xid, u64 size));
s32 sysFsAioWrite(sysFsAio *Aio, s32 *id, void (*func)(sysFsAio *Aio, s32 error, s32 xid, u64 size));

s32 sysFsGetFreeSize(const char *path, u32 *blockSize, u64 *freeBlocks);

EXTERN_END


