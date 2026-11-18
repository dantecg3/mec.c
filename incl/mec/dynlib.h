#ifndef MEC_DYNLIB_H
#define MEC_DYNLIB_H

#include "base.h"
#include "sys.h"
#include "fs.h"

typedef void *DYNLIB;

DYNLIB dynlib_load (FS_Path path);
void dynlib_unload (DYNLIB *p_dynlib);
void *dynlib_symbol (DYNLIB dynlib, STR_View name);

#define $dynlib_symbol(T, dynlib, name) (__extension__ (T)dynlib_symbol ((dynlib), (name)))

#ifdef MEC_IMPL
DYNLIB dynlib_load (FS_Path path)
{
  $mem_scope_init (4 * MEM_KB, &s_context.temp_allocator);
  STR_C path_c = str_c_new (path, s_context.temp_allocator);
  return sys_load_dynlib (path_c);
}

void dynlib_unload (DYNLIB *p_dynlib)
{
  sys_unload_dynlib (*p_dynlib);
  *p_dynlib = NULL;
}

void *dynlib_symbol (DYNLIB dynlib, STR_View name)
{
  $mem_scope_init (4 * MEM_KB, &s_context.temp_allocator);
  STR_C name_c = str_c_new (name, s_context.temp_allocator);
  return sys_dynlib_symbol((void *)dynlib, name_c);
}

#endif // MEC_IMPL
#endif // MEC_DYNLIB_H
