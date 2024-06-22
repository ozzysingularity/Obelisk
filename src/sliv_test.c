#include <obelisk_arena.h>
#include <obelisk_string.h>

int
main(void)
{
    Arena a;
    arena_init(&a, 1024);
    arena_error();

    StringSliceVector ssv = stringSlice_vectorNew(&a, 2);

    printf(
            "stringSlice_vectorPut(&ssv, stringSlice(\"Hello, world!\"));\n"
            "string_error();\n"
          );

    stringSlice_vectorPut(&ssv, stringSlice("Hello, world!"));
    string_error();

    // (void) getchar();

    printf(
            "stringSlice_vectorPut(&ssv, stringSlice(\"Goodbye, world!\"));\n"
            "string_error();\n"
          );

    stringSlice_vectorPut(&ssv, stringSlice("Goodbye, world!"));
    string_error();

    // (void) getchar();

    printf(
            "stringSlice_at(ssv, 2);\n"
            "string_error();\n"
          );

    stringSlice_at(ssv, 2);
    string_error();

    // (void) getchar();

    printf(
            "stringSlice_at(ssv, 10);\n"
            "string_error();\n"
          );

    stringSlice_at(ssv, 10);
    string_error();

    // (void) getchar();

    return 0;
}
