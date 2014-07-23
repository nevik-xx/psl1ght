#include <sys/syscalls.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

extern caddr_t psl1ght_sbrk_r(struct _reent* r, ptrdiff_t increment);
extern int psl1ght_close_r(struct _reent* r, int fd);
extern int psl1ght_open_r(struct _reent* r, const char* path, int oflag, int mode);
extern ssize_t psl1ght_read_r(struct _reent* r, int fd, void* buffer, size_t size);
extern ssize_t psl1ght_write_r(struct _reent* r, int fd, const void* buffer, size_t size);
extern off_t psl1ght_lseek64_r(struct _reent* r, int fd, off_t offset, int whence);
extern off_t psl1ght_lseek_r(struct _reent* r, int fd, off_t offset, int whence);
extern int psl1ght_fstat_r(struct _reent* r, int fd, struct stat* buf);
extern int psl1ght_fstat64_r(struct _reent* r, int fd, struct stat* buf);
extern int psl1ght_stat_r(struct _reent* r, const char* path, struct stat* buf);
extern int psl1ght_stat64_r(struct _reent* r, const char* path, struct stat* buf);
extern int psl1ght_ftruncate_r(struct _reent* r, int fd, off_t length);
extern int psl1ght_truncate_r(struct _reent* r, const char* path, off_t length);
extern int psl1ght_fsync_r(struct _reent* r, int fd);
extern int psl1ght_link_r(struct _reent* r, const char* old, const char* new);
extern int psl1ght_unlink_r(struct _reent* r, const char* path);
extern int psl1ght_chmod_r(struct _reent* r, const char* path, mode_t mode);
extern int psl1ght_utime_r(struct _reent* r, const char* path, const struct utimbuf* times);
extern mode_t psl1ght_umask_r(struct _reent* r, mode_t cmask);
extern int psl1ght_isatty_r(struct _reent* r, int fd);
extern void psl1ght_exit(int status);
extern int psl1ght_mkdir_r(struct _reent* r, const char* path, mode_t mode);
extern int psl1ght_rmdir_r(struct _reent* r, const char* path);
extern int psl1ght_rename_r(struct _reent* r, const char* old, const char* new);
extern int psl1ght_closedir_r(struct _reent* r, DIR* dir);
extern void psl1ght_seekdir_r(struct _reent* r, DIR* dir, long int seek);
extern void psl1ght_rewinddir_r(struct _reent* r, DIR* dir);
extern long int psl1ght_telldir_r(struct _reent* r, DIR* dir);
extern struct dirent* psl1ght_readdir_r(struct _reent* r, DIR* dir);
extern int psl1ght_readdir_r_r(struct _reent* r, DIR* dir, struct dirent* dirent, struct dirent** out);
extern DIR* psl1ght_opendir_r(struct _reent* r, const char* path);
extern int psl1ght_settimeofday_r(struct _reent* r, const struct timeval * tv, const struct timezone * tz);
extern int psl1ght_gettimeofday_r(struct _reent* r, struct timeval * tv, void * unused);
extern int psl1ght_lwmutex_create_r(struct _reent* r, sys_lwmutex_t* lwmutex, const sys_lwmutex_attr_t* attr);
extern int psl1ght_lwmutex_destroy_r(struct _reent* r, sys_lwmutex_t* lwmutex);
extern int psl1ght_lwmutex_lock_r(struct _reent* r, sys_lwmutex_t*lwmutex, unsigned long long timeout);
extern int psl1ght_lwmutex_trylock_r(struct _reent* r, sys_lwmutex_t* lwmutex);
extern int psl1ght_lwmutex_unlock_r(struct _reent* r, sys_lwmutex_t* lwmutex);

__attribute__((constructor(104)))
static void initSyscalls()
{
	__syscalls.sbrk_r = psl1ght_sbrk_r;
	__syscalls.close_r = psl1ght_close_r;
	__syscalls.open_r = psl1ght_open_r;
	__syscalls.read_r = psl1ght_read_r;
	__syscalls.write_r = psl1ght_write_r;
	__syscalls.lseek_r = psl1ght_lseek_r;
	__syscalls.lseek64_r = psl1ght_lseek64_r;
	__syscalls.fstat_r = psl1ght_fstat_r;
	__syscalls.fstat64_r = psl1ght_fstat64_r;
	__syscalls.stat_r = psl1ght_stat_r;
	__syscalls.stat64_r = psl1ght_stat64_r;
	__syscalls.ftruncate_r = psl1ght_ftruncate_r;
	__syscalls.truncate_r = psl1ght_truncate_r;
	__syscalls.fsync_r = psl1ght_fsync_r;
	__syscalls.link_r = psl1ght_link_r;
	__syscalls.unlink_r = psl1ght_unlink_r;
	__syscalls.chmod_r = psl1ght_chmod_r;
	__syscalls.rename_r = psl1ght_rename_r;
	__syscalls.utime_r = psl1ght_utime_r;

	__syscalls.umask_r = psl1ght_umask_r;

	__syscalls.mkdir_r = psl1ght_mkdir_r;
	__syscalls.rmdir_r = psl1ght_rmdir_r;
/*	__syscalls.chdir_r = psl1ght_chdir_r;
	__syscalls.getcwd_r = psl1ght_getcwd_r;*/

	__syscalls.closedir_r = psl1ght_closedir_r;
	__syscalls.opendir_r = psl1ght_opendir_r;
	__syscalls.readdir_r = psl1ght_readdir_r;
	__syscalls.readdir_r_r = psl1ght_readdir_r_r;
	__syscalls.rewinddir_r = psl1ght_rewinddir_r;
	__syscalls.seekdir_r = psl1ght_seekdir_r;
	__syscalls.telldir_r = psl1ght_telldir_r;

	__syscalls.isatty_r = psl1ght_isatty_r;
	__syscalls.gettod_r = psl1ght_gettimeofday_r;
	__syscalls.settod_r = psl1ght_settimeofday_r;
/*	__syscalls.execve_r = psl1ght_execve_r;
	__syscalls.getrusage_r = psl1ght_getrusage_r;*/

	__syscalls.sys_lwmutex_create_r = psl1ght_lwmutex_create_r;
	__syscalls.sys_lwmutex_destroy_r = psl1ght_lwmutex_destroy_r;
	__syscalls.sys_lwmutex_lock_r = psl1ght_lwmutex_lock_r;
	__syscalls.sys_lwmutex_trylock_r = psl1ght_lwmutex_trylock_r;
	__syscalls.sys_lwmutex_unlock_r = psl1ght_lwmutex_unlock_r;
	
	__syscalls.exit = psl1ght_exit;
}
