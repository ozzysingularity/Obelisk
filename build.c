#include <obelisk/build.h>

int
build(Build *b)
{
    build_init(b, "./bin/obelisk");

    build_set(b, compiler, "clang");
    build_set(b, root_src, "src/main.c");

    build_set(b, source_path, "src/obelisk");
    build_add(b, src, "obelisk.c");

    build_set(b, source_path, "src/obelisk_arena");
    build_add(b, src, "obelisk_arena.c");

    build_set(b, source_path, "src/obelisk_arena");
    build_add(b, src, "obelisk_arena_string.c");

    build_set(b, source_path, "src/obelisk_string");
    build_add(b, src, "obelisk_string.c");

    build_add(b, include_path, "src");

//  build_add(b, sysobj, "obelisk");
    build_add(b, flag, "-O3");

    build_compile(b);

    return 0;
}
