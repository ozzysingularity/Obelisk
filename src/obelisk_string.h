#ifndef     OBELISK_STRING_H
#define     OBELISK_STRING_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


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


String
string_new(char *sz);

String
string_alloc(size_t len);

String
string_fromSlice(StringSlice *sli);

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

/* Type Ideas
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

