#include <obelisk_arena.h>


ArenaError a_errno;


/* types that don't allow caller to modify themselves */
#define OPAQUE

/* hides function from other translation units */
#define PRIVATE static

//OPAQUE
//struct arena_chunk {
//    void *data;
//    size_t pos,
//           cap;
//    struct arena_chunk *next;
//};

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

    if (a_errno > A_good) {
        return;
    }

    a->root = a_rt;
    a->cur = a->root;
    a->chunk_size = a_chsz;

    a_errno = A_ok;
}

void *
arena_alloc(Arena *a, size_t pos) THROWS(A_oom)
{
    void *res;

    ArenaChunk *const cur_ch = a->cur;
    void *cur_dat = cur_ch->data + cur_ch->pos;
    

    const size_t al_pos = ALIGN(pos);
    const size_t new_pos = cur_ch->pos + al_pos;


    if (new_pos >= cur_ch->cap) {
        arena_addChunk(a);
    }

    if (a_errno > A_good) {
        return NULL;
    }

    res = cur_dat + cur_ch->pos;
    cur_ch->pos = new_pos;

    return res;
}

void
arena_free(Arena *a)
{
    ArenaChunk *cur = a->root,
               *next = cur->next;

    /* base condition, asumes last arena node ends pointing to NULL */
    while (cur) {
        /* FALLBACK CONDITION
         *  checks if the current pointer equals the current
         *  pointer in the arena, if it break from the loop
         */

        arenaChunk_free(cur);
        free(cur);

        if (cur == a->cur) {
            break;
        }

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

    if (a_errno > A_good) {
        return;
    }

    a->cur->next = new_chunk;
    a->cur = new_chunk;

    a_errno = A_ok;
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
    res->pos = ch_size;
    res->cap = ch_cap;
    res->next = ch_next;

    return res;
}

void
arenaChunk_free(ArenaChunk *ach)
{
    free(ach->data);

    ach->data = NULL;

    ach->pos = 0;
    ach->cap = 0;
}
