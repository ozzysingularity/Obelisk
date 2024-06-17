#include <obelisk_arena.h>


#define OPAQUE  /* types that don't allow caller to modify themselves */
#define PRIVATE static

/* adds new chunk to the arena */
PRIVATE void arena_addChunk(Arena *a);

/* adds a new ArenaChunk */
PRIVATE ArenaChunk * arenaChunk_new(size_t chunk_size);

/* frees an arena chunk */
PRIVATE void arenaChunk_free(ArenaChunk *ach);


ArenaError a_errno;


void
arena_init(Arena *a, size_t chunk_size)
{
    size_t a_chsz = ALIGN(chunk_size);
    ArenaChunk *a_rt = arenaChunk_new(a_chsz);

    if (a_errno != A_ok) {
        return;
    }

    a->root = a_rt;
    a->cur = a->root;
    a->chunk_size = a_chsz;

    a_errno = A_ok;
}

void
arena_free(Arena *a)
{
    ArenaChunk *cur = a->root,
               *next = cur->next;
    
    while (cur) {
        if (cur == a->cur) { ; }
        arenaChunk_free(cur);
        cur = next;
        next = cur->next;
    }
}

/* PRIVATE */

void
arena_addChunk(Arena *a) THROWS(A_oom)
{
    const size_t chsz = a->chunk_size;
    ArenaChunk *const new_chunk = arenaChunk_new(chsz);

    if (a_errno != A_ok) {
        
    }
    
}

ArenaChunk *
arenaChunk_new(size_t chunk_size) THROWS(A_oom)
{
    ArenaChunk * res;

    const size_t ch_cap = chunk_size;
    const size_t ch_size = 0;
    void * const ch_dat = malloc(ch_cap);
    void * const ch_next = NULL;

    if (!(res = malloc(sizeof(ArenaChunk)))) {
        a_errno = A_oom;
        return NULL;
    }

    a_errno = A_ok;

    res->data = ch_dat;
    res->size = ch_size;
    res->cap = ch_cap;
    res->next = ch_next;

    return res;
}

void
arenaChunk_free(ArenaChunk *ach)
{
    free(ach->data);
    free(ach);

    ach->data = NULL;
    ach->next = NULL;

    ach->size = 0;
    ach->cap = 0;
}

