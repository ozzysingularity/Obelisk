#include <obelisk.h>

int
build(Build *b)
{
    build_init(b, "./bin/lisk");

    build_set(b, compiler, "clang");
    build_set(b, root_src, "src/main.c");

    build_add(b, sysobj, "obelisk");

    build_command(b);

    return 0;
}
