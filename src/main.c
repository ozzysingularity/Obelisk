#include <dlfcn.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#if 0
#include <string.h>
#endif

#include <obelisk.h>

typedef struct
program_options {
    char *config_path;
} ProgramOptions;


int (*build)(Build *);


char output[256];


struct {
    char * build_file;
    int run,
        vebose;
} Options = {
    .build_file = NULL,
    .run = 0,
    .vebose = 0,
};


void
usage()
{
    printf(
            "Usage: obelisk [OPTION...]\n"
            "Options:\n"
            "  -h, --help               Shows this information\n"
          //"  -r, --run                Runs the program after generation\n"
          //"  -i, --install            Installs the program in /usr/bin\n"
          //"  -s, --set                Sets a value to the pattern of "
          //                           "OPT:VAL\n"
            "  -t, -b, --target         Selects the build file to build the "
                                       "program with\n"
          //"  --lib                    Selects an archive to link the build "
          //                           "file to"
          );

    exit(1);
}

int
file_exists(char *name)
{
    int res;
    FILE *fp;

    if ((fp = fopen(name, "r"))) {
        res = 1;
        fclose(fp);
    } else {
        res = 0;
    }

    return res;
}

void
build_so(char *source)
{
    Build _b, *b = &_b;

    srand(time(NULL));
    int rng = rand();

    sprintf(output, "/tmp/%s-%.6x.so", source, rng);

    if (!file_exists("/usr/lib/libobelisk.so")) {
        fprintf(stderr,
                "\033[1mobelisk: \033[91merror: \033[0mcould not link "
                "libobelisk.so; please install obelisk or specify the "
                "--lib <libobelisk.a path> to run\n");
        exit(1);
    }

    build_init(b, output);

    build_set(b, compiler, "cc");
    build_set(b, root_src, source);

    build_add(b, sysobj, "obelisk");

    build_add(b, include_path, "src");

    build_add(b, flag, "-shared");
    build_add(b, flag, "-fPIC");

    build_compile(b);
}


int
main(int argc, char **argv)
{
    char *program;
    void *handle;

    program = *argv++, argc--;

    Build _b, *b = &_b;


    if (argc < 1) {
        Options.build_file = "build.c";
    }


    while (argc && argv[0][0] == '-' && argv[0][1]) {
        switch (argv[0][1]) {

        /* options that consume values, ie. -tbuild.c/-t build.c uses
         * build.c as a target
         */
        case 't': case 'b':
            if (argv[0][2]) {
                Options.build_file = &argv[0][2];

                argv++, argc--;
            } else {
                argv++, argc--;

                Options.build_file = *argv++, argc--;
            }
            
            break;

        /* long options, ie. --help = print help */
        case '-':
            if (!(strcmp("help", &argv[0][2]))) {
                usage();
            } else
            if (!(strcmp("target", &argv[0][2]))) {
                argv++, argc--;

                Options.build_file = *argv++, argc--;
            } else
            if (!(strcmp("verbose", &argv[0][2]))) {
                argv++, argc--;

                Options.vebose = 1;
            } else {
                fprintf(stderr, "\033[1mobelisk: \033[91merror:\033[0m "
                        "unknown option: %s\n",
                        &argv[0][2]);
                usage();
            }

            break;

        /* compound options, ie. -vr/-rv run verbosely */
        default:                    
            while (*++argv[0]) {    /* skips '-' */
                switch (*argv[0]) {
                case 'h':
                    usage();
        
                case 'r':
                    Options.run = 1;

                    break;
                    
                case 'v':
                    Options.vebose = 1;

                    break;

                default:
                    fprintf(stderr, "\033[1mobelisk: \033[91merror:\033[0m "
                            "unknown option: %c/%d\n",
                            *argv[0], *argv[0]);
                    usage();
                }
            }

            argv++, argc--;

            break;
        }
    }

    if (argc > 0) {
        usage();
    }

    if (Options.vebose) {
        printf("[OPTION] build file: %s\n", Options.build_file);
    }

    if (!file_exists(Options.build_file)) {
        fprintf(stderr, "\033[1mobelisk: \033[91merror: \033[0m%s: "
                "no such file\n", Options.build_file);
        exit(1);
    }

    build_so(Options.build_file);

    if (b_errno > B_good) {
        fprintf(stderr, "Build failed\n");
        exit(1);
    }


    handle = dlopen(output, RTLD_LAZY);

    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    dlerror();

    build = dlsym(handle, "build");

    build(b);

    remove(output);

    return 0;
}

