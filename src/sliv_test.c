#include <obelisk_arena.h>
#include <obelisk_string.h>

#define KiB(n) ((n) * 1024)

int
main(void)
{
    Arena a;
    arena_init(&a, KiB(1));
    StringSliceVector s = stringSlice_vectorNew(&a, 16);


    StringSlice sli1 = stringSlice("Hello, world!");
    StringSlice sli2 = stringSlice("Goodbye, world!");
    StringSlice sli3 = stringSlice("Hello, my friend!");
    StringSlice sli4 = stringSlice("Goodbye, my friend!");
    StringSlice sli5 = stringSlice("The World!");

    stringSlice_vectorPut(&s, sli1);
    stringSlice_vectorPut(&s, sli2);
    stringSlice_vectorPut(&s, sli3);
    stringSlice_vectorPut(&s, sli4);
    stringSlice_vectorPut(&s, sli5);

    printf("%.*s\n", (int)string_len(stringSlice_at(s, 0)), string(stringSlice_at(s, 0)));
    printf("%.*s\n", (int)string_len(stringSlice_at(s, 1)), string(stringSlice_at(s, 1)));
    printf("%.*s\n", (int)string_len(stringSlice_at(s, 2)), string(stringSlice_at(s, 2)));
    printf("%.*s\n", (int)string_len(stringSlice_at(s, 3)), string(stringSlice_at(s, 3)));
    printf("%.*s\n", (int)string_len(stringSlice_at(s, 4)), string(stringSlice_at(s, 4)));

    return 0;
}
