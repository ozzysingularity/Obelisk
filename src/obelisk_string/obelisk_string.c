#include <obelisk_string.h> /* parent */


#define DEBUG

#ifdef DEBUG
    #include <assert.h>
#endif


String
string_new(char *sz)
{
    String res;

    size_t res_len;
    char *res_str;

    res_len = strlen(sz);
    res_str = malloc(res_len);
    memcpy(res_str, sz, res_len);

    res.str = res_str;
    res.len = res_len;
    res.cap = ALIGN(res_len);

    return res;
}

String
string_alloc(size_t len)
{
    String res;

    char * res_str;
    size_t res_len,
           res_cap;

    res_len = len;
    res_cap = ALIGN(res_len);
    res_str = malloc(res_cap);

    res.str = res_str;
    res.len = res_len;
    res.cap = res_cap;

    return res;
}

String
string_fromSlice(StringSlice *sli)
{
    String res = string_alloc(sli->len);

    memcpy(res.str, sli->str, sli->len);

    return res;
}

void
string_free(String *str)
{
    str->len = 0;
    str->cap = 0;

    free(str->str);
}

StringSlice
string_slice(String *str, size_t offset, size_t len)
{
    char *res_str;
    size_t res_len;
    
    StringSlice res;
    
    res_str = (str->str + offset);
    res_len = (len <= str->len - offset)
                ? len
                : str->len - offset;

    res.str = res_str;
    res.len = res_len;

    return res;
}

StringSlice
string_sliceCString(char *sz, size_t offset, size_t len)
{
    size_t sz_len;

    char *res_str;
    size_t res_len;

    StringSlice res;

    sz_len = strlen(sz);

    res_str = sz + offset;
    res_len = (len <= sz_len - offset)
                ? len
                : sz_len - offset;

    res.str = res_str;
    res.len = res_len;

    return res;
}

String
string_cat(void *str_a, void *str_b)
{
    String res;

    char * str_a_str,
         * str_b_str;

    size_t str_a_len,
           str_b_len;

    size_t res_len;

    str_a_str = *(char **)str_a;
    str_b_str = *(char **)str_b;

    str_a_len = *(size_t *)str_a + sizeof(char*);
    str_b_len = *(size_t *)str_b + sizeof(char*);

    res_len = str_a_len
            + str_b_len;

    res = string_alloc(res_len);

    memcpy(res.str, str_a_str, str_a_len);
    memcpy(res.str + str_a_len, str_b_str, str_b_len);

    return res;
}


String
string_catWithDelimitCString(void *str_a, void *str_b, char *delimit_buf)
{
    String res;

    char * str_a_str,
         * str_b_str;

    size_t str_a_len,
           str_b_len;

    size_t delimit_buf_len;

    size_t res_len;

    str_a_str = *(char **)str_a;
    str_b_str = *(char **)str_b;

    str_a_len = *(size_t *)str_a + sizeof(char*);
    str_b_len = *(size_t *)str_b + sizeof(char*);

    delimit_buf_len = strlen(delimit_buf);

    res_len = str_a_len
            + str_b_len
            + delimit_buf_len;

    res = string_alloc(res_len);

    memcpy(res.str, str_a_str, str_a_len);
    memcpy(res.str + str_a_len, delimit_buf, delimit_buf_len);
    memcpy(res.str + str_a_len + delimit_buf_len, str_b_str, str_b_len);

    return res;
}

String
string_catWithDelimitChar(void *str_a, void *str_b, char delimit_char)
{
    String res;

    StringSlice *sli_a,
                *sli_b;

    size_t res_len;

    sli_a = (StringSlice *)str_a;
    sli_b = (StringSlice *)str_b;

    res_len = sli_a->len + sli_b->len + 1;

    res = string_alloc(res_len);

    memcpy(res.str, sli_a->str, sli_a->len);
    res.str[sli_a->len] = delimit_char;
    memcpy(res.str + sli_a->len + 1, sli_b->str, sli_b->len);

    return res;
}

String
string_catCString(void *ams, char *sz)
{
    String res;
    size_t res_len;

    StringSlice *sli;

    size_t sz_len;

    sli = (StringSlice *)ams;

    sz_len = strlen(sz);

    res_len = sli->len + sz_len;
    res = string_alloc(res_len);


    memcpy(res.str, sli->str, sli->len);



    return res;
}

size_t
string_print(void *ams)
{
    StringSlice *reinterp = (StringSlice *)ams;
    size_t res;

    res = write(STDOUT_FILENO, reinterp->str, reinterp->len);

    return res;
}

size_t
string_cap(String *str)
{
    return str->cap;
}

size_t
string_len(void *ams)
{
    StringSlice *res = (StringSlice*)ams;
    return res->len;
}

char *
string(void *ams)
{
    StringSlice *res = (StringSlice*)ams;
    return res->str;
}

