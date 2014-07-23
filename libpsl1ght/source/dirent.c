#include <stdlib.h>
#include <string.h>
#include <reent.h>
#include <errno.h>
#include <dirent.h>
#include <psl1ght/lv2/filesystem.h>
#include <psl1ght/lv2/errno.h>

DIR* psl1ght_opendir_r(struct _reent* r, const char* path)
{
	DIR* dir = (DIR*)malloc(sizeof(DIR));
	struct dirent* buffer = (struct dirent*)malloc(sizeof(struct dirent));
	if (!dir || !buffer) {
		free(dir); free(buffer);
		r->_errno = ENOMEM;
		return NULL;
	}

	memset(dir, 0, sizeof(DIR));
	memset(buffer, 0, sizeof(struct dirent));
	dir->dd_buf = buffer;
	dir->dd_len = sizeof(struct dirent);

	Lv2FsFile fd;
	int ret = lv2FsOpenDir(path, &fd);
	if (!ret) {
		dir->dd_fd = fd;
		return dir;
	}

	free(dir); free(buffer);
	lv2ErrnoReentrant(r, ret);
	return NULL;
}

static void convertLv2Dirent(struct dirent* dirent, Lv2FsDirent* lv2dirent, DIR* dir)
{
	dirent->d_reclen = sizeof(struct dirent);
	dirent->d_seekoff = dir->dd_seek;
	dirent->d_namlen = lv2dirent->d_namlen;
	dirent->d_type = lv2dirent->d_type;
	strncpy(dirent->d_name, lv2dirent->d_name, MAXPATHLEN + 1);
}

int psl1ght_readdir_r_r(struct _reent* r, DIR* dir, struct dirent* dirent, struct dirent** out)
{
	u64 read = 0;
	Lv2FsDirent lv2dir;

	int ret = lv2FsReadDir(dir->dd_fd, &lv2dir, &read);
	if (!ret) {
		if (read) {
			convertLv2Dirent(dirent + dir->dd_loc, &lv2dir, dir);
			dir->dd_seek++;
			*out = dirent;
		} else
			*out = NULL;
	} else
		*out = NULL;
	
	return lv2Error(ret);
}

struct dirent* psl1ght_readdir_r(struct _reent* r, DIR* dir)
{
	struct dirent* out;
	int ret = psl1ght_readdir_r_r(r, dir, (struct dirent*)dir->dd_buf, &out);
	
	if (ret)
		r->_errno = ret;

	return out;
}

long int psl1ght_telldir_r(struct _reent* r, DIR* dir)
{
	return dir->dd_seek;
}

void psl1ght_rewinddir_r(struct _reent* r, DIR* dir)
{
	r->_errno = ENOSYS;
}

void psl1ght_seekdir_r(struct _reent* r, DIR* dir, long int seek)
{
	r->_errno = ENOSYS;
}

int psl1ght_closedir_r(struct _reent* r, DIR* dir)
{
	free(dir->dd_buf);
	int ret = lv2FsCloseDir(dir->dd_fd);
	free(dir);
	return lv2ErrnoReentrant(r, ret);
}
