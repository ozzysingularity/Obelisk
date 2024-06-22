#ifndef     OBELISK_UTIL
#define     OBELISK_UTIL


/* The ALIGN Macro
 *  number aligned to 8 byte bound. if it divisible by 8, it keeps the value
 *  if not, it subtracts the remainder of the number divided by 8 (the modulus)
 *  then adds 8
 */
#define ALIGN(n) (((n) % 8 == 0) ? (n) : ((n) - ((n) % 8) + 8))

/* The LEN Macro
 *  takes an array, assuming it is an array, and not a pointer, and takes the
 *  total size of the array and divides it by the first element of the array
 */
#define LEN(a)      (sizeof(a)/sizeof(a[0]))

#endif
