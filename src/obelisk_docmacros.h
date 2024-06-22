#ifndef     OBELISK_DOCMACROS
#define     OBELISK_DOCMACROS


/* The THROWS Macro
 *  Documentation macro that tells what errors a function will throw. If a
 *  function throws an error, it will set an errno coresponding with the
 *  function/data-type.
 */
#define THROWS(e, ...)

/* The INIT Macro
 *  Documentation macro to tell which fields of a struct is initialized by a
 *  function.
 */
#define INIT(i, ...)

#endif
