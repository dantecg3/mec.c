#ifndef MEC_EMBED_H
#define MEC_EMBED_H
#ifndef MEC_NO_EMBED

#ifndef __clang__
#error "embed.h requires Clang to compile"
#endif

#include "base.h"
#include "mem.h"
#include "fs.h"

#define $str_(x) #x
#define $str(x)  $str_ (x)

#ifdef MACOS__
#define EMBED_PUSH_SECTION__ ".pushsection __TEXT,__const\n"
#elif WINDOWS__
#define EMBED_PUSH_SECTION__ ".pushsection .rdata,\"dr\"\n"
#elif LINUX__
#define EMBED_PUSH_SECTION__ ".pushsection .rodata\n"
#endif

FS_File embed_make (const byte *start, const byte *end, const char *path);

#define $embed_impl(path, id)                                                          \
  ({                                                                                    \
    extern const byte $cat (embed_start_, id)[] __asm__ ("embed_" $str (id) "_start");  \
    extern const byte $cat (embed_end_, id)[] __asm__ ("embed_" $str (id) "_end");      \
    __asm__ (EMBED_PUSH_SECTION__                                                       \
             ".balign 16\n"                                                             \
             "embed_" $str (id) "_start:\n"                                             \
             ".incbin \"" path "\"\n"                                                   \
             "embed_" $str (id) "_end:\n"                                               \
             ".byte 0\n"                                                                \
             ".popsection\n");                                                          \
    embed_make ($cat (embed_start_, id), $cat (embed_end_, id), path);                  \
  })

#define $embed(path) $embed_impl (path, __COUNTER__)

#ifdef MEC_IMPL
FS_File embed_make (const byte *start, const byte *end, const char *path)
{
  return (FS_File){
    .buffer   = (byte *)start,
    .metadata = {
        .size      = (usize)(end - start),
        .extension = fs_map_extension (fs_path_extension (fs_path (path))) },
    .alloc = { 0 }
  };
}
#endif // MEC_IMPL
#endif // MEC_NO_EMBED
#endif // MEC_EMBED_H
