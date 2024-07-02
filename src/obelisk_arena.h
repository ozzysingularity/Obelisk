#ifndef     OBELISK_ARENA
#define     OBELISK_ARENA


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <obelisk_docmacros.h>
#include <obelisk_util.h>


/* error are handled by the user */
typedef enum
arena_error {
    A_ok = 0,
    A_resolved = 1,

    A_good,

    /* chunk alloc fail, throws if out of memory */
    A_oom = 255,

    /* bounds check fail, throws if end of chunk detected
     * make a new chunk if bound reached
     */
//    A_bcf = 254,
} ArenaError;

typedef struct
arena_chunk {
    void *data;
    size_t pos,
           cap;
    struct arena_chunk *next;
}ArenaChunk;

typedef struct
arena {
    ArenaChunk *root,
               *cur;
    size_t chunk_size;
    ArenaError err;
} Arena;


/* initializes an arena */
Arena *
arena_init(Arena *a, size_t chunk_size) THROWS(A_oom);

/* allocates a chunk of memory in the current arena chunk */
void *
arena_alloc(Arena *a, size_t len) THROWS(A_oom, A_bcf);

/* iterates though all of the arena chunks and frees them */
void
arena_free(Arena *a);

/* adds new chunk to the arena */
void
arena_addChunk(Arena *a);

void
arena_error(Arena *a);

#endif  //  OBELISK_ARENA_H
