#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include <physfs.h>
#include <rthreads/rthreads.h>
#include <streams/file_stream.h>
#include <retro_dirent.h>

#define __PHYSICSFS_INTERNAL__ 1
#include "physfs_internal.h"

extern char *home_directory;
extern struct retro_vfs_interface *vfs_interface;

int __PHYSFS_platformInit(void)
{
	return 1;  /* always succeed. */
} /* __PHYSFS_platformInit */


void __PHYSFS_platformDeinit(void)
{
	/* no-op */
} /* __PHYSFS_platformDeinit */


void __PHYSFS_platformDetectAvailableCDs(PHYSFS_StringCallback cb, void *data)
{
}

char *home_dir_copy(int add_slash) {
	size_t l = home_directory ? strlen(home_directory) : 0;
	char *ret = allocator.Malloc(l + 2);

	if (home_directory)
		memcpy(ret, home_directory, l + 1);
	else
		memset(ret, 0, l + 1);
	if (add_slash && (l == 0 || ret[l-1] != __PHYSFS_platformDirSeparator)) {
		ret[l] = __PHYSFS_platformDirSeparator;
		ret[l+1] = '\0';
	}
	return ret;
}
	

char *__PHYSFS_platformCalcBaseDir(const char *argv0)
{
	return home_dir_copy(1);
}

char *__PHYSFS_platformCalcPrefDir(const char *org, const char *app)
{
	return home_dir_copy(1);
}

char *__PHYSFS_platformCalcUserDir(void)
{
	return home_dir_copy(1);
} /* __PHYSFS_platformCalcUserDir */


 // Single-threaded. WiiU is multi-threaded but our frontend is single-threaded and we're statically linked
typedef struct
{
	slock_t *mutex;
	uintptr_t owner;
	PHYSFS_uint32 count;
} PthreadMutex;

void *__PHYSFS_platformGetThreadID(void)
{
	return ( (void *) sthread_get_current_thread_id() );
} /* __PHYSFS_platformGetThreadID */

void *__PHYSFS_platformCreateMutex(void)
{
	PthreadMutex *m = (PthreadMutex *) allocator.Malloc(sizeof (PthreadMutex));
	BAIL_IF(!m, PHYSFS_ERR_OUT_OF_MEMORY, NULL);
	m->mutex = slock_new();
	if (!m->mutex)
	{
		allocator.Free(m);
		BAIL(PHYSFS_ERR_OS_ERROR, NULL);
	} /* if */

	m->count = 0;
	m->owner = (uintptr_t) 0xDEADBEEF;
	return ((void *) m);
} /* __PHYSFS_platformCreateMutex */


void __PHYSFS_platformDestroyMutex(void *mutex)
{
	PthreadMutex *m = (PthreadMutex *) mutex;

	/* Destroying a locked mutex is a bug, but we'll try to be helpful. */
	if ((m->owner == sthread_get_current_thread_id()) && (m->count > 0))
		slock_unlock(m->mutex);

	slock_free(m->mutex);
	allocator.Free(m);
} /* __PHYSFS_platformDestroyMutex */

int __PHYSFS_platformGrabMutex(void *mutex)
{
	PthreadMutex *m = (PthreadMutex *) mutex;
	uintptr_t tid = sthread_get_current_thread_id();
	if (m->owner != tid)
	{
		slock_lock(m->mutex);
		m->owner = tid;
	} /* if */

	m->count++;
	return 1;
} /* __PHYSFS_platformGrabMutex */

void __PHYSFS_platformReleaseMutex(void *mutex)
{
	PthreadMutex *m = (PthreadMutex *) mutex;
	assert(m->owner == sthread_get_current_thread_id());  /* catch programming errors. */
	assert(m->count > 0);  /* catch programming errors. */
	if (m->owner == sthread_get_current_thread_id()) {
		if (--m->count == 0) {
			m->owner = (uintptr_t) 0xDEADBEEF;
			slock_unlock(m->mutex);
		} /* if */
	} /* if */
} /* __PHYSFS_platformReleaseMutex */

PHYSFS_EnumerateCallbackResult __PHYSFS_platformEnumerate(const char *dirname,
                               PHYSFS_EnumerateCallback callback,
                               const char *origdir, void *callbackdata)
{
	RDIR *dir;
	PHYSFS_EnumerateCallbackResult retval = PHYSFS_ENUM_OK;

	dir = retro_opendir(dirname);
	BAIL_IF(dir == NULL, PHYSFS_ERR_NOT_FOUND, PHYSFS_ENUM_ERROR);

	while (retro_readdir(dir))
	{
		const char *name = retro_dirent_get_name(dir);
		if (name[0] == '.')  /* ignore "." and ".." */
		{
			if ((name[1] == '\0') || ((name[1] == '.') && (name[2] == '\0')))
				continue;
		} /* if */
		
		retval = callback(callbackdata, origdir, name);
		if (retval == PHYSFS_ENUM_ERROR)
			PHYSFS_setErrorCode(PHYSFS_ERR_APP_CALLBACK);
	} /* while */

	retro_closedir(dir);

	return retval;
} /* __PHYSFS_platformEnumerate */

static void *doOpen(const char *filename, unsigned lr_mode, int appending)
{
	RFILE *fd;
	
	fd = filestream_open(filename, lr_mode, RETRO_VFS_FILE_ACCESS_HINT_NONE);
	BAIL_IF(fd == NULL, PHYSFS_ERR_NOT_FOUND, NULL); // TODO: improve error handling?

	if (appending)
	{	    
		if (filestream_seek(fd, 0, RETRO_VFS_SEEK_POSITION_END) < 0)
		{
			filestream_close(fd);
			BAIL(PHYSFS_ERR_IO, NULL);
		}
	} /* if */

	return fd;
} /* doOpen */


void *__PHYSFS_platformOpenRead(const char *filename)
{
	return doOpen(filename, RETRO_VFS_FILE_ACCESS_READ, 0);
} /* __PHYSFS_platformOpenRead */


void *__PHYSFS_platformOpenWrite(const char *filename)
{
	return doOpen(filename, RETRO_VFS_FILE_ACCESS_WRITE, 0);
} /* __PHYSFS_platformOpenWrite */


void *__PHYSFS_platformOpenAppend(const char *filename)
{
	return doOpen(filename, RETRO_VFS_FILE_ACCESS_WRITE | RETRO_VFS_FILE_ACCESS_UPDATE_EXISTING, 1);
} /* __PHYSFS_platformOpenAppend */

PHYSFS_sint64 __PHYSFS_platformRead(void *opaque, void *buffer,
                                    PHYSFS_uint64 len)
{
	RFILE *fd = (RFILE *) opaque;
	ssize_t rc = 0;

	if (!__PHYSFS_ui64FitsAddressSpace(len))
		BAIL(PHYSFS_ERR_INVALID_ARGUMENT, -1);

	rc = filestream_read(fd, buffer, (size_t) len);
	BAIL_IF(rc == -1, PHYSFS_ERR_IO, -1);
	assert(rc >= 0);
	assert(rc <= len);
	return (PHYSFS_sint64) rc;
} /* __PHYSFS_platformRead */

PHYSFS_sint64 __PHYSFS_platformWrite(void *opaque, const void *buffer,
                                     PHYSFS_uint64 len)
{
	RFILE *fd = (RFILE *) opaque;
	ssize_t rc = 0;

	if (!__PHYSFS_ui64FitsAddressSpace(len))
		BAIL(PHYSFS_ERR_INVALID_ARGUMENT, -1);

	rc = filestream_write(fd, (void *) buffer, (size_t) len);
	BAIL_IF(rc == -1, PHYSFS_ERR_IO, rc);
	assert(rc >= 0);
	assert(rc <= len);
	return (PHYSFS_sint64) rc;
} /* __PHYSFS_platformWrite */


int __PHYSFS_platformSeek(void *opaque, PHYSFS_uint64 pos)
{
	RFILE *fd = (RFILE *) opaque;
	const int64_t rc = filestream_seek(fd, (off_t) pos, RETRO_VFS_SEEK_POSITION_START);
	BAIL_IF(rc == -1, PHYSFS_ERR_IO, 0);
	return 1;
} /* __PHYSFS_platformSeek */


PHYSFS_sint64 __PHYSFS_platformTell(void *opaque)
{
	RFILE *fd = (RFILE *) opaque;
	PHYSFS_sint64 retval;
	retval = (PHYSFS_sint64) filestream_tell(fd);
	BAIL_IF(retval == -1, PHYSFS_ERR_IO, -1);
	return retval;
} /* __PHYSFS_platformTell */


PHYSFS_sint64 __PHYSFS_platformFileLength(void *opaque)
{
	RFILE *fd = (RFILE *) opaque;
	PHYSFS_sint64 retval;
	retval = (PHYSFS_sint64) filestream_get_size(fd);
	BAIL_IF(retval == -1, PHYSFS_ERR_IO, -1);
	return retval;
} /* __PHYSFS_platformFileLength */

int __PHYSFS_platformFlush(void *opaque)
{
	RFILE *fd = (RFILE *) opaque;
	filestream_flush(fd);
	return 1;
} /* __PHYSFS_platformFlush */


void __PHYSFS_platformClose(void *opaque)
{
	RFILE *fd = (RFILE *) opaque;
	filestream_close(fd);
} /* __PHYSFS_platformClose */

int __PHYSFS_platformDelete(const char *path)
{
    BAIL_IF(filestream_delete(path) == -1, PHYSFS_ERR_IO, 0);
    return 1;
} /* __PHYSFS_platformDelete */

static PHYSFS_ErrorCode errcodeFromErrnoError(const int err)
{
    switch (err)
    {
        case 0: return PHYSFS_ERR_OK;
        case EACCES: return PHYSFS_ERR_PERMISSION;
        case EPERM: return PHYSFS_ERR_PERMISSION;
#ifndef _WIN32
        case EDQUOT: return PHYSFS_ERR_NO_SPACE;
#endif
        case EIO: return PHYSFS_ERR_IO;
        case ELOOP: return PHYSFS_ERR_SYMLINK_LOOP;
        case EMLINK: return PHYSFS_ERR_NO_SPACE;
        case ENAMETOOLONG: return PHYSFS_ERR_BAD_FILENAME;
        case ENOENT: return PHYSFS_ERR_NOT_FOUND;
        case ENOSPC: return PHYSFS_ERR_NO_SPACE;
        case ENOTDIR: return PHYSFS_ERR_NOT_FOUND;
        case EISDIR: return PHYSFS_ERR_NOT_A_FILE;
        case EROFS: return PHYSFS_ERR_READ_ONLY;
        case ETXTBSY: return PHYSFS_ERR_BUSY;
        case EBUSY: return PHYSFS_ERR_BUSY;
        case ENOMEM: return PHYSFS_ERR_OUT_OF_MEMORY;
        case ENOTEMPTY: return PHYSFS_ERR_DIR_NOT_EMPTY;
        default: return PHYSFS_ERR_OS_ERROR;
    } /* switch */
} /* errcodeFromErrnoError */


static inline PHYSFS_ErrorCode errcodeFromErrno(void)
{
    return errcodeFromErrnoError(errno);
} /* errcodeFromErrno */

int __PHYSFS_platformMkDir(const char *path)
{
	if (vfs_interface && vfs_interface->mkdir) {
		const int rc = vfs_interface->mkdir(path);
		BAIL_IF(rc == -1, PHYSFS_ERR_IO, 0);
		BAIL_IF(rc == -2, PHYSFS_ERR_DUPLICATE, 0); //Already exists
		return 1;
	} else {
#ifdef _WIN32
		const int rc = mkdir(path);
#else
		const int rc = mkdir(path, S_IRWXU);
#endif
		BAIL_IF(rc == -1, errcodeFromErrno(), 0);
		return 1;
	}
} /* __PHYSFS_platformMkDir */


int __PHYSFS_platformStat(const char *fname, PHYSFS_Stat *st, const int follow)
{
	if (vfs_interface && vfs_interface->stat) {
		int32_t size;
		int flags = vfs_interface->stat(fname, &size);
		if (!(flags & RETRO_VFS_STAT_IS_VALID)) {
			BAIL(PHYSFS_ERR_NOT_FOUND, 0);
		}

		if (flags & RETRO_VFS_STAT_IS_DIRECTORY) {
			st->filetype = PHYSFS_FILETYPE_DIRECTORY;
			st->filesize = 0;
		} else if (flags & RETRO_VFS_STAT_IS_CHARACTER_SPECIAL) {
			st->filetype = PHYSFS_FILETYPE_OTHER;
			st->filesize = 0;
		} else {
			st->filetype = PHYSFS_FILETYPE_REGULAR;
			st->filesize = size;
		}

		// TODO: Fill those properly
		st->modtime = 0;
		st->createtime = 0;
		st->accesstime = 0;
		st->readonly = 0;

		return 1;
	} else {
		struct stat statbuf;
#if defined(PS2) || defined(_WIN32) || defined(WIIU)
		const int rc = stat(fname, &statbuf);
#else
		const int rc = follow ? stat(fname, &statbuf) : lstat(fname, &statbuf);
#endif
		BAIL_IF(rc == -1, errcodeFromErrno(), 0);

		if (S_ISREG(statbuf.st_mode))
		{
			st->filetype = PHYSFS_FILETYPE_REGULAR;
			st->filesize = statbuf.st_size;
		} /* if */

		else if(S_ISDIR(statbuf.st_mode))
		{
			st->filetype = PHYSFS_FILETYPE_DIRECTORY;
			st->filesize = 0;
		} /* else if */
#if !(defined(PS2) || defined(_WIN32) || defined(WIIU))
		else if(S_ISLNK(statbuf.st_mode))
		{
			st->filetype = PHYSFS_FILETYPE_SYMLINK;
			st->filesize = 0;
		} /* else if */
#endif
		else
		{
			st->filetype = PHYSFS_FILETYPE_OTHER;
			st->filesize = statbuf.st_size;
		} /* else */

		st->modtime = statbuf.st_mtime;
		st->createtime = statbuf.st_ctime;
		st->accesstime = statbuf.st_atime;

		st->readonly = (access(fname, W_OK) == -1);
		return 1;
	}
} /* __PHYSFS_platformStat */
