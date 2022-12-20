#include "time.h"
#include "wasi.h"
#include "errno.h"
#include "unix_util.h"
#include "fcntl.h"
#include "unistd.h"
#include "sys/stat.h"
#include "dirent.h"
#include "string.h"

wasi_errno wasi_clock_res_get(wasi_clockid id, wasi_timestamp *offset)
{
  struct timespec t;
  SYSCALL(clock_getres(id, &t));
  *offset = t.tv_nsec;
  return WASI_SUCCESS;
}

wasi_errno wasi_time_get(wasi_clockid id, wasi_timestamp *offset)
{
  struct timespec t;
  SYSCALL(clock_gettime(id, &t));
  *offset = t.tv_nsec;
  return WASI_SUCCESS;
}

wasi_errno wasi_fd_advice(wasi_fd fd, wasi_filesize offset, wasi_filesize len, wasi_advise advise)
{
  int advise_unix;
  switch (advise) {
  case WASI_ADVISE_NOREUSE:
    advise_unix = POSIX_FADV_NOREUSE;
    break;
  case WASI_ADVISE_WILLNEED:
    advise_unix = POSIX_FADV_WILLNEED;
    break;
  case WASI_ADVISE_DONTNEED:
    advise_unix = POSIX_FADV_DONTNEED;
    break;
  default:
    advise_unix = advise;
  }

  SYSCALL(posix_fadvise(fd, offset, len, advise_unix));
  return WASI_SUCCESS;
}

wasi_errno wasi_fd_allocate(wasi_fd fd, wasi_filesize offset, wasi_filesize len)
{
  SYSCALL(posix_fallocate(fd, offset, len));
  return WASI_SUCCESS;
}

wasi_errno wasi_fd_close(wasi_fd fd)
{
  SYSCALL(close(fd));
  return WASI_SUCCESS;
}

wasi_errno wasi_fd_datasync(wasi_fd fd)
{
  SYSCALL(fdatasync(fd));
  return WASI_SUCCESS;
}

wasi_errno wasi_fd_fdstat_get(wasi_fd fd, wasi_fdstat *stat)
{
  // struct stat s;
  // SYSCALL(fstat(fd, &s));
  return WASI_SUCCESS;
}

wasi_errno wasi_fd_fdstat_set_flags(wasi_fd fd, wasi_fdflags flags)
{
  int flags_unix = 0;
  if (flags & WASI_FDFLAG_APPEND) {
    flags_unix |= O_APPEND;
  }
  if (flags & WASI_FDFLAG_DSYNC) {
    flags_unix |= O_DSYNC;
  }
  if (flags & WASI_FDFLAG_NONBLOCK) {
    flags_unix |= O_NONBLOCK;
  }
  if (flags & WASI_FDFLAG_RSYNC) {
    flags_unix |= O_RSYNC;
  }
  if (flags & WASI_FDFLAG_SYNC) {
    flags_unix |= O_SYNC;
  }

  SYSCALL(fcntl(fd, F_SETFL, flags_unix));
  return WASI_SUCCESS;
}

wasi_errno wasi_fd_fdstat_set_rights(wasi_fd fd, wasi_rights rights_base, wasi_rights rights_inheriting)
{
  return WASI_SUCCESS;
}

wasi_errno wasi_fd_filestat_get(wasi_fd fd, wasi_filestat *stat)
{
  struct stat s;
  SYSCALL(fstat(fd, &s));
  stat->dev = s.st_dev;
  stat->ino = s.st_ino;
  stat->filetype = s.st_mode;
  stat->nlink = s.st_nlink;
  stat->size = s.st_size;
  stat->atim = s.st_atim.tv_nsec;
  stat->mtim = s.st_mtim.tv_nsec;
  stat->ctim = s.st_ctim.tv_nsec;
  return WASI_SUCCESS;
}

wasi_errno wasi_fd_filestat_set_size(wasi_fd fd, wasi_filesize size)
{
  SYSCALL(ftruncate(fd, size));
  return WASI_SUCCESS;
}

wasi_errno wasi_fd_filestat_set_times(wasi_fd fd, wasi_timestamp atim, wasi_timestamp mtim, wasi_fstflags flags)
{
  struct timespec ts[2];
  if (flags & WASI_FSTFLAGS_ATIM_NOW) {
    ts[0].tv_nsec = atim;
  }
  if (flags & WASI_FSTFLAGS_MTIM_NOW) {
    ts[1].tv_nsec = mtim;
  }
  SYSCALL(futimens(fd, ts));
  return WASI_SUCCESS;
}

wasi_errno wasi_fd_pread(void* base_ptr, wasi_fd fd, const wasi_iovec *iovs, wasi_size iovs_len, wasi_filesize offset, wasi_size *nread)
{
  size_t total = 0;
  for (size_t i = 0; i < iovs_len; i++) {
    ssize_t n = pread(fd, base_ptr + iovs[i].buf, iovs[i].buf_len, offset);
    if (n < 0) {
      RET_MAP_ERRNO
    }
    total += n;
  }
  *nread = total;
  return WASI_SUCCESS;
}

wasi_errno wasi_fd_prestat_get(wasi_fd fd, void *prestat)
{
  return WASI_SUCCESS;
}

wasi_errno wasi_fd_prestat_dir_name(wasi_fd fd, char *path, wasi_size path_len)
{
  return WASI_SUCCESS;
}

wasi_errno wasi_fd_pwrite(void* base_ptr, wasi_fd fd, const wasi_ciovec *iovs, wasi_size iovs_len, wasi_filesize offset, wasi_size *nwritten)
{
  size_t total = 0;
  for (size_t i = 0; i < iovs_len; i++) {
    ssize_t n = pwrite(fd, base_ptr + iovs[i].buf, iovs[i].buf_len, offset);
    if (n < 0) {
      RET_MAP_ERRNO
    }
    total += n;
  }
  *nwritten = total;
  return WASI_SUCCESS;
}

wasi_errno wasi_fd_read(void* base_ptr, wasi_fd fd, const wasi_iovec* iovs, wasi_size iovs_len, wasi_size* nread)
{
  size_t total = 0;
  for (size_t i = 0; i < iovs_len; i++) {
    ssize_t n = read(fd, base_ptr + iovs[i].buf, iovs[i].buf_len);
    if (n < 0) {
      RET_MAP_ERRNO;
    }
    total += n;
  }
  *nread = total;
  return WASI_SUCCESS;
}

wasi_errno wasi_fd_readdir(wasi_fd fd, wasi_dirent* buf, wasi_size buf_len, wasi_dircookie dircookie, wasi_size* nread)
{
  void* dir = fdopendir(fd);

  if (dir == NULL) {
    RET_MAP_ERRNO
  }

  seekdir(dir, dircookie);
  
  errno = 0;
  u32 consumed = 0;
  while (consumed < buf_len) {
    struct dirent* entry = readdir(dir);
    if (entry == NULL && errno != 0) {
      RET_MAP_ERRNO;
    }

    struct dirent dir_entry = *entry;
    if (dir_entry.d_reclen + consumed >= buf_len) {
      break;
    }

    struct wasi_dirent dirent;
    dirent.d_next = dircookie++;
    dirent.ino = dir_entry.d_ino;
    dirent.namlen = dir_entry.d_reclen;
    dirent.type = dir_entry.d_type;

    *(buf + consumed) = dirent;
    consumed += 24;
    strcpy(dir_entry.d_name, (char*)(buf + consumed));
    consumed += dir_entry.d_reclen;
    // Align
    consumed = (consumed + 8 - 1) &~(8 - 1);
  }

  *nread = consumed;

  return WASI_SUCCESS;
}
