#pragma once

#include "errno.h"
#include "wasi.h"

#define ERR(x) case x: return WASI_##x;

#define RET_MAP_ERRNO \
  switch (errno) { \
    ERR(E2BIG) \
    ERR(EACCES) \
    ERR(EADDRINUSE) \
    ERR(EADDRNOTAVAIL) \
    ERR(EAFNOSUPPORT) \
    ERR(EAGAIN) \
    ERR(EALREADY) \
    ERR(EBADF) \
    ERR(EBADMSG) \
    ERR(EBUSY) \
    ERR(ECANCELED) \
    ERR(ECHILD) \
    ERR(ECONNABORTED) \
    ERR(ECONNREFUSED) \
    ERR(ECONNRESET) \
    ERR(EDEADLK) \
    ERR(EDESTADDRREQ) \
    ERR(EDOM) \
    ERR(EDQUOT) \
    ERR(EEXIST) \
    ERR(EFAULT) \
    ERR(EFBIG) \
    ERR(EHOSTUNREACH) \
    ERR(EIDRM) \
    ERR(EILSEQ) \
    ERR(EINPROGRESS) \
    ERR(EINTR) \
    ERR(EINVAL) \
    ERR(EIO) \
    ERR(EISCONN) \
    ERR(EISDIR) \
    ERR(ELOOP) \
    ERR(EMFILE) \
    ERR(EMLINK) \
    ERR(EMSGSIZE) \
    ERR(EMULTIHOP) \
    ERR(ENAMETOOLONG) \
    ERR(ENETDOWN) \
    ERR(ENETRESET) \
    ERR(ENETUNREACH) \
    ERR(ENFILE) \
    ERR(ENOBUFS) \
    ERR(ENODEV) \
    ERR(ENOENT) \
    ERR(ENOEXEC) \
    ERR(ENOLCK) \
    ERR(ENOLINK) \
    ERR(ENOMEM) \
    ERR(ENOMSG) \
    ERR(ENOPROTOOPT) \
    ERR(ENOSPC) \
    ERR(ENOSYS) \
    ERR(ENOTCONN) \
    ERR(ENOTDIR) \
    ERR(ENOTEMPTY) \
    ERR(ENOTRECOVERABLE) \
    ERR(ENOTSOCK) \
    ERR(ENOTSUP) \
    ERR(ENOTTY) \
    ERR(ENXIO) \
    ERR(EOVERFLOW) \
    ERR(EOWNERDEAD) \
    ERR(EPERM) \
    ERR(EPIPE) \
    ERR(EPROTO) \
    ERR(EPROTONOSUPPORT) \
    ERR(EPROTOTYPE) \
    ERR(ERANGE) \
    ERR(EROFS) \
    ERR(ESPIPE) \
    ERR(ESRCH) \
    ERR(ESTALE) \
    ERR(ETIMEDOUT) \
    ERR(ETXTBSY) \
    ERR(EXDEV) \
  } \

#define SYSCALL(result) \
  if (result == -1) { \
    RET_MAP_ERRNO; \
  }