#pragma once

#include "stddef.h"

#ifndef WASI_EXPORT
  #if defined(_WIN32)
    #define WASI_EXPORT __declspec(dllexport)
  #else
    #define WASI_EXPORT
  #endif
#endif

#ifndef WASI_SYSCALL
  #define WASI_SYSCALL(name) WASI_EXPORT wasi_errno wasi_##name
#endif

typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef long long s64;
typedef u32 wasi_size;
typedef u32 wasi_filesize;
typedef u64 wasi_timestamp;
typedef u32 wasi_fd;
typedef u32 wasi_ptr;
typedef u64 wasi_device;
typedef u64 wasi_inode;
typedef u64 wasi_linkcount;
typedef u64 wasi_dircookie;
typedef u32 wasi_dirnamlen;
typedef s64 wasi_filedelta;

typedef enum wasi_whence {
  WASI_WHENCE_SET = 0,
  WASI_WHENCE_CUR = 1,
  WASI_WHENCE_END = 2,
} wasi_whence;

typedef enum wasi_filetype: unsigned char {
  WASI_FILETYPE_UNKNOWN = 0,
  WASI_FILETYPE_BLOCK_DEVICE = 1,
  WASI_FILETYPE_CHARACTER_DEVICE = 2,
  WASI_FILETYPE_DIRECTORY = 3,
  WASI_FILETYPE_REGULAR_FILE = 4,
  WASI_FILETYPE_SOCKET_DGRAM = 5,
  WASI_FILETYPE_SOCKET_STREAM = 6,
  WASI_FILETYPE_SYMBOLIC_LINK = 7,
} wasi_filetype;

typedef struct wasi_dirent {
  wasi_dircookie d_next;
  wasi_inode ino;
  wasi_dirnamlen namlen;
  wasi_filetype type;
} wasi_dirent;

typedef struct wasi_iovec
{
  wasi_ptr buf;
  wasi_filesize buf_len;
} wasi_iovec;

typedef struct wasi_ciovec
{
  const wasi_ptr buf;
  wasi_filesize buf_len;
} wasi_ciovec;

typedef enum wasi_fdflags: u16 {
  WASI_FDFLAG_APPEND = 0x0001,
  WASI_FDFLAG_DSYNC = 0x0002,
  WASI_FDFLAG_NONBLOCK = 0x0004,
  WASI_FDFLAG_RSYNC = 0x0008,
  WASI_FDFLAG_SYNC = 0x0010,
} wasi_fdflags;

typedef u64 wasi_rights;

typedef struct wasi_fdstat {
  wasi_filetype filetype;
  wasi_fdflags fdflags;
  wasi_rights rights_base;
  wasi_rights rights_inheriting;
} wasi_fdstat;

typedef struct wasi_filestat {
  wasi_device dev;
  wasi_inode ino;
  wasi_filetype filetype;
  wasi_linkcount nlink;
  wasi_filesize size;
  wasi_timestamp atim;
  wasi_timestamp mtim;
  wasi_timestamp ctim;
} wasi_filestat;

typedef enum wasi_fstflags: u16 {
  WASI_FSTFLAGS_ATIM = 0x0001,
  WASI_FSTFLAGS_ATIM_NOW = 0x0002,
  WASI_FSTFLAGS_MTIM = 0x0004,
  WASI_FSTFLAGS_MTIM_NOW = 0x0008,
} wasi_fstflags;

typedef enum wasi_advise
{
  WASI_ADVISE_NORMAL = 0,
  WASI_ADVISE_SEQUENTIAL = 1,
  WASI_ADVISE_RANDOM = 2,
  WASI_ADVISE_WILLNEED = 3,
  WASI_ADVISE_DONTNEED = 4,
  WASI_ADVISE_NOREUSE = 5
} wasi_advise;

typedef enum wasi_clockid
{
  WASI_CLOCKID_REALTIME = 0,
  WASI_CLOCKID_MONOTONIC = 1,
  WASI_CLOCKID_PROCESS_CPUTIME_ID = 2,
  WASI_CLOCKID_THREAD_CPUTIME_ID = 3,
} wasi_clockid;

typedef enum wasi_errno
{
  WASI_SUCCESS = 0,
  WASI_E2BIG = 1,
  WASI_EACCES = 2,
  WASI_EADDRINUSE = 3,
  WASI_EADDRNOTAVAIL = 4,
  WASI_EAFNOSUPPORT = 5,
  WASI_EAGAIN = 6,
  WASI_EALREADY = 7,
  WASI_EBADF = 8,
  WASI_EBADMSG = 9,
  WASI_EBUSY = 10,
  WASI_ECANCELED = 11,
  WASI_ECHILD = 12,
  WASI_ECONNABORTED = 13,
  WASI_ECONNREFUSED = 14,
  WASI_ECONNRESET = 15,
  WASI_EDEADLK = 16,
  WASI_EDESTADDRREQ = 17,
  WASI_EDOM = 18,
  WASI_EDQUOT = 19,
  WASI_EEXIST = 20,
  WASI_EFAULT = 21,
  WASI_EFBIG = 22,
  WASI_EHOSTUNREACH = 23,
  WASI_EIDRM = 24,
  WASI_EILSEQ = 25,
  WASI_EINPROGRESS = 26,
  WASI_EINTR = 27,
  WASI_EINVAL = 28,
  WASI_EIO = 29,
  WASI_EISCONN = 30,
  WASI_EISDIR = 31,
  WASI_ELOOP = 32,
  WASI_EMFILE = 33,
  WASI_EMLINK = 34,
  WASI_EMSGSIZE = 35,
  WASI_EMULTIHOP = 36,
  WASI_ENAMETOOLONG = 37,
  WASI_ENETDOWN = 38,
  WASI_ENETRESET = 39,
  WASI_ENETUNREACH = 40,
  WASI_ENFILE = 41,
  WASI_ENOBUFS = 42,
  WASI_ENODEV = 43,
  WASI_ENOENT = 44,
  WASI_ENOEXEC = 45,
  WASI_ENOLCK = 46,
  WASI_ENOLINK = 47,
  WASI_ENOMEM = 48,
  WASI_ENOMSG = 49,
  WASI_ENOPROTOOPT = 50,
  WASI_ENOSPC = 51,
  WASI_ENOSYS = 52,
  WASI_ENOTCONN = 53,
  WASI_ENOTDIR = 54,
  WASI_ENOTEMPTY = 55,
  WASI_ENOTRECOVERABLE = 56,
  WASI_ENOTSOCK = 57,
  WASI_ENOTSUP = 58,
  WASI_ENOTTY = 59,
  WASI_ENXIO = 60,
  WASI_EOVERFLOW = 61,
  WASI_EOWNERDEAD = 62,
  WASI_EPERM = 63,
  WASI_EPIPE = 64,
  WASI_EPROTO = 65,
  WASI_EPROTONOSUPPORT = 66,
  WASI_EPROTOTYPE = 67,
  WASI_ERANGE = 68,
  WASI_EROFS = 69,
  WASI_ESPIPE = 70,
  WASI_ESRCH = 71,
  WASI_ESTALE = 72,
  WASI_ETIMEDOUT = 73,
  WASI_ETXTBSY = 74,
  WASI_EXDEV = 75,
  WASI_ENOTCAPABLE = 76,
} wasi_errno;

WASI_SYSCALL(clock_res_get) (wasi_clockid id, wasi_timestamp *offset);
WASI_SYSCALL(clock_time_get) (wasi_clockid id, wasi_timestamp *offset);
WASI_SYSCALL(fd_advice) (wasi_fd fd, wasi_filesize offset, wasi_filesize len, wasi_advise advise);
WASI_SYSCALL(fd_allocate) (wasi_fd fd, wasi_filesize offset, wasi_filesize len);
WASI_SYSCALL(fd_close) (wasi_fd fd);
WASI_SYSCALL(fd_datasync) (wasi_fd fd);
WASI_SYSCALL(fd_fdstat_get) (wasi_fd fd, wasi_fdstat *stat);
WASI_SYSCALL(fd_fdstat_set_flags) (wasi_fd fd, wasi_fdflags flags);
WASI_SYSCALL(fd_fdstat_set_rights) (wasi_fd fd, wasi_rights rights_base, wasi_rights rights_inheriting);
WASI_SYSCALL(fd_filestat_get) (wasi_fd fd, wasi_filestat *stat);
WASI_SYSCALL(fd_filestat_set_size) (wasi_fd fd, wasi_filesize size);
WASI_SYSCALL(fd_filestat_set_times) (wasi_fd fd, wasi_timestamp atim, wasi_timestamp mtim, wasi_fstflags flags);
WASI_SYSCALL(fd_pread) (void* base_ptr, wasi_fd fd, const wasi_iovec *iovs, wasi_size iovs_len, wasi_filesize offset, wasi_size *nread);
WASI_SYSCALL(fd_prestat_get) (wasi_fd fd, void *prestat);
WASI_SYSCALL(fd_prestat_dir_name) (wasi_fd fd, char *path, wasi_size path_len);
WASI_SYSCALL(fd_pwrite) (void* base_ptr, wasi_fd fd, const wasi_ciovec *iovs, wasi_size iovs_len, wasi_filesize offset, wasi_size *nwritten);
WASI_SYSCALL(fd_read) (void* base_ptr, wasi_fd fd, const wasi_iovec *iovs, wasi_size iovs_len, wasi_size *nread);
WASI_SYSCALL(fd_dirread) (wasi_fd fd, wasi_dirent* buf, wasi_size buf_len, wasi_dircookie dircookie, wasi_size* nread);
WASI_SYSCALL(fd_seek) (wasi_fd fd, wasi_filedelta offset, wasi_whence whence, wasi_filesize* pos);
WASI_SYSCALL(fd_sync) (wasi_fd fd);
WASI_SYSCALL(fd_tell) (wasi_fd fd, wasi_filesize* pos);