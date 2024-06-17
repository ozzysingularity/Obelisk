#ifndef     OBELISK_ARENA_H
#define     OBELISK_ARENA_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ALIGN(n) (((n) % 8 == 0) ? (n) : ((n) - ((n) % 8) + 8))

#define THROWS(e, ...) /* decorative macros to tell what functions throw in
                        * case of error, and what to check against.
                        * If a function throws an error, it will set a_errno.
                        */


typedef struct arena_chunk {
    void *data;
    size_t size,
           cap;
    struct arena_chunk *next;
} ArenaChunk;

typedef struct arena {
    ArenaChunk *root,
               *cur;
    size_t chunk_size;
} Arena;

/* error are handled by the user */
typedef enum arena_error {
    A_ok = 0,
    A_oom,    /* chunk alloc fail, throws if out of memory */
    A_bc,     /* bounds check fail, throws if end of chunk detected
                           make a new chunk if bound reached */
} ArenaError;


extern ArenaError a_errno;


/* initializes an arena */
void arena_init(Arena *a, size_t chunk_size) THROWS(A_oom);

void arena_free(Arena *a);


#endif  //  OBELISK_ARENA_H
