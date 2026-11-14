#ifndef MEC_ERROR_H
#define MEC_ERROR_H

#include "base.h"

typedef struct ERROR ERROR;
typedef uint8        ERROR_Code;

#define ERR_FMT "[0x%02X]"

enum
{
  ERROR_NONE                = 0x00,
  ERROR_UNKNOWN             = 0x01,
  ERROR_INVALID_ARGUMENT    = 0x02,
  ERROR_NOT_SUPPORTED       = 0x03,
  ERROR_NOT_FOUND           = 0x04,
  ERROR_ALREADY_EXISTS      = 0x05,
  ERROR_PERMISSION_DENIED   = 0x06,
  ERROR_TIMEOUT             = 0x07,
  ERROR_CANCELLED           = 0x08,

  ERROR_INVALID_STATE       = 0x10,
  ERROR_NOT_INITIALIZED     = 0x11,
  ERROR_ALREADY_INITIALIZED = 0x12,
  ERROR_BUSY                = 0x13,
  ERROR_STALE               = 0x14,

  ERROR_OUT_OF_MEMORY       = 0x20,
  ERROR_BUFFER_TOO_SMALL    = 0x21,
  ERROR_OVERFLOW            = 0x22,
  ERROR_UNDERFLOW           = 0x23,
  ERROR_CORRUPTION          = 0x24,
  ERROR_FULL                = 0x25,

  ERROR_IO                  = 0x30,
  ERROR_EOF                 = 0x31,
  ERROR_PATH_INVALID        = 0x32,
  ERROR_BAD_FORMAT          = 0x33,

  ERROR_LOCK_FAILED         = 0x41,
  ERROR_THREAD_CREATE       = 0x42,
  ERROR_CHANNEL_CLOSED      = 0x43,

  ERROR_CREATION_FAILED     = 0x50,
  ERROR_INVALID_DIMENSIONS  = 0x51,
  ERROR_INVALID_VIDEO_MODE  = 0x52,
  ERROR_RENDER_FAILED       = 0x53,
  ERROR_CONTEXT_LOST        = 0x54,
  ERROR_UNSUPPORTED_FORMAT  = 0x55,

  ERROR_NETWORK             = 0x60,
  ERROR_CONNECTION_REFUSED  = 0x61,
  ERROR_CONNECTION_RESET    = 0x62,
  ERROR_HOST_UNREACHABLE    = 0x63,
  ERROR_PROTOCOL            = 0x64
};

struct ERROR
{
  ERROR_Code  code;
  const char *msg;
};

static inline ERROR error (ERROR_Code code, const char *msg)
{
  return (ERROR){
    .code = code,
    .msg  = msg
  };
}

static inline ERROR error_null ()
{
  return (ERROR){
    .code = ERROR_NONE,
    .msg  = NULL
  };
}

static inline bool error_is_null (ERROR error)
{
  return error.code == ERROR_NONE;
}

#endif // MEC_ERROR_H
