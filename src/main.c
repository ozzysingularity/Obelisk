#include <dlfcn.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#if 0
#include <string.h>
#endif

#include <obelisk.h>

typedef struct
program_options {
    char *config_path;
} ProgramOptions;


int (*build)(Build *);


void
build_so(char *source)
{
    Build _b, *b = &_b;

    build_init(b, "/tmp/build.so");

    build_set(b, compiler, "clang");
    build_set(b, root_src, source);

    build_add(b, sysobj, "obelisk");

    build_add(b, flag, "-shared");
    build_add(b, flag, "-fPIC");

    build_command(b);

    char cmd[513];

    sprintf(cmd, "%.*s", (int) command->len, command->str);
    cmd[512] = 0;

    system(cmd);
}


int
main(int argc, char **argv)
{
    char *argv0;
    void *handle;

    Build _b, *b = &_b;

    argv0 = *argv++;
    argc--;

    if (argc < 1) {
        fprintf(stderr, "Not enough arguments\n");
        exit(1);
    }

    build_so(*argv);

    if (b_errno > B_good) {
        fprintf(stderr, "Build failed\n");
        exit(1);
    }

    handle = dlopen("/tmp/build.so", RTLD_LAZY);

    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    dlerror();

    build = dlsym(handle, "build");

    build(b);

    remove("/tmp/build.so");

    return 0;
}

