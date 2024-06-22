#ifndef     OBELISK_STRING
#define     OBELISK_STRING


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <obelisk_arena.h>


#define ALIGN(n)    (( n % 8 ) == 0 ? n + 8 : ((n) - ((n) % 8) + 8))
#define LEN(a)      (sizeof(a)/sizeof(a[0]))


typedef struct
string {
    char * str;
    size_t len,
           cap;
} String;

typedef struct
string_slice {
    char * str;
    size_t len;
} StringSlice;

typedef enum
string_error {
    S_ok = 0,

    S_good,

    S_fail,
    S_bcf,

    S_oom = 255,

    SV_bcf = 511,
} StringError;

extern StringError s_errno; // [TODO] implement s_errno in func calls


String
string_new(char *sz);

String
string_alloc(size_t len);

String
string_fromSlice(StringSlice sli);

void
string_free(String *str);

StringSlice
string_slice(String *str, size_t offset, size_t len);

StringSlice
string_sliceCString(char *sz, size_t offset, size_t len);

String
string_cat(void *ams_a, void *ams_b);

String
string_catWithDelimitCString(void *str_a, void *str_b, char *delimit_buf);

String
string_catWithDelimitChar(void *str_a, void *str_b, char delimit_char);

size_t
string_print(void *ams);

size_t
string_cap(String *str);

size_t
string_len(void *ams);

char *
string(void *ams);

StringSlice
stringSlice(char *sz);

/* Type Ideas
 * String Vectors (Obelisk.Arena.String)
 *  typedef struct string_vector {
 *      String *strs;
 *      size_t cnt,
 *             cap;
 *  } StringVector
 *
 *  typedef struct string_slice_vector {
 *      StringSlice *slis;
 *      size_t cnt,
 *             cap;
 *  } StringSliceVector;
 *
 * Delimiter Strings
 *  StringSlice string_sliceByDelimiter(String *str, char delim);
 *  String **string_chopByDelimiter(String *str, char delim);
 *  StringSlice string_sliceByDelimiters(String *str, char *delims);
 *  StringVector *string_chopByDelimiters(String *str, char *delims);
 */

#endif  //  OBELISK_STRING_H

/* Variable abbreviations
 *  sz = char *
 *  str = String or struct string
 *  sli = StringSlice or struct string_slice
 *  ams = ambiguous string
 *  len = size_t
 *  cap = size_t
 *  res = result -- anything that will be returned
 *  res_* = anything that is a part of the result
 */

#ifdef OBELISK_ARENA


typedef struct
string_vector {
    String *strs;
    size_t cnt,
           cap;
} StringVector;

typedef struct
string_slice_vector {
    StringSlice *slis;
    size_t pos,
           cap;
} StringSliceVector;


String
arenaString_new(Arena *a, char *sz);

String
arenaString_alloc(Arena *a, size_t len);

String
arenaString_fromSlice(Arena *a, StringSlice sli);

String
arenaString_cat(Arena *a, void *ams1, void *ams2);

String
arenaString_catWithDelimitCString(Arena *a, void *str_a, void *str_b, char *delimit_buf);

String
arenaString_catWithDelimitChar(Arena *a, void *str_a, void *str_b, char delimit_char);

/* cap is the capacity of the vector, the amount of strings that it will store
 */
StringSliceVector
stringSlice_vectorNew(Arena *a, size_t cap);

void
stringSlice_vectorPut(StringSliceVector *sliv, StringSlice sli);

StringSlice *
stringSlice_at(StringSliceVector sliv, size_t idx);


#endif
