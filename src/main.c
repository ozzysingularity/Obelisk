#include <dlfcn.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#if 0
#include <string.h>
#endif

typedef struct
program_options {
    char *config_path;
} ProgramOptions;


int (*build)(void);


int
main(int argc, char **argv)
{
    char *argv0;
    void *handle;

    argv0 = *argv++;
    argc--;

    if (argc < 1) {
        exit(1);
    }

    handle = dlopen(*argv, RTLD_NOW);

    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    dlerror();

    build = dlsym(handle, "build");
    int buildres = build();
    printf("build result: %d\n", buildres);

    return 0;
}

