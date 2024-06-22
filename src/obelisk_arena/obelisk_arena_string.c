#include <obelisk_string.h>
#include <obelisk_arena.h>


String
arenaString_new(Arena *a, char *sz)
{
    String res;

    const
        size_t res_len = strlen(sz),
               res_cap = ALIGN(res_len);
    char *res_str = arena_alloc(a, res_cap);;

    if (a_errno > A_good) {
        s_errno = S_fail;
        return (String) { 0 };
    }

    memcpy(res_str, sz, res_len);

    res.str = res_str;
    res.len = res_len;
    res.cap = res_cap;

    return res;
}

String
arenaString_alloc(Arena *a, size_t len)
{
    String res;

    char *res_str;
    const size_t res_len = len,
                 res_cap = ALIGN(res_len);

    res_str = arena_alloc(a, res_cap);

    if (a_errno > A_good) {
        s_errno = S_fail;
        return (String) { 0 };
    }

    res.str = res_str;
    res.len = res_len;
    res.cap = res_cap;

    return res;
}

String
arenaString_fromSlice(Arena *a, StringSlice sli)
{
    String res = arenaString_alloc(a, sli.len);

    memcpy(res.str, sli.str, res.len);

    return res;
}

String
arenaString_cat(Arena *a, void *ams1, void *ams2)
{

    String res;

    const
        StringSlice * ams1_sli = (StringSlice *) ams1,
                    * ams2_sli = (StringSlice *) ams2;

    const size_t res_len = ams1_sli->len + ams2_sli->len;

    res = arenaString_alloc(a, res_len);

    memcpy(res.str, ams1_sli->str, ams1_sli->len);
    memcpy(res.str + ams1_sli->len, ams2_sli->str, ams2_sli->len);

    return res;
}

String
arenaString_catWithDelimitCString
(
 Arena *a,
 void *str_a, void *str_b,
 char *delimit_buf
) {
    String res;
    return res;
}

String
arenaString_catWithDelimitChar
(
 Arena *a,
 void *str_a, void *str_b,
 char delimit_char
) {
    String res;
    return res;
}

StringSliceVector
stringSlice_vectorNew(Arena *a, size_t cap)
{
    StringSliceVector res;

    if (!cap) {
        res.cap = 16;
    } else {
        res.cap = cap;
    }
    res.pos = 0;
    res.slis = arena_alloc(a, sizeof(StringSlice) * res.cap);

    return res;
}

void
stringSlice_vectorPut(StringSliceVector *sliv, StringSlice sli)
{
    if (sliv->pos + 1 >= sliv->cap) {
        s_errno = SV_bcf;
        return;
    }

    sliv->slis[sliv->pos] = sli;
    sliv->pos += 1;
}

StringSlice *
stringSlice_at(StringSliceVector sliv, size_t idx)
{
    if (idx > sliv.pos || idx > sliv.cap) {
        s_errno = SV_bcf;
        return NULL;
    }
    return &sliv.slis[idx];
}

