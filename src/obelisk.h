#ifndef     OBELISK_H
#define     OBELISK_H


#include <obelisk_docmacros.h>
#include <obelisk_arena.h>
#include <obelisk_string.h>


typedef enum
build_error {
    B_ok = 0,

    B_good,
    
    B_fail = 255, /* simple fail, unknown cause */
} BuildError;

typedef enum
build_exe_set {
    root_src,
    output_path,
    include_path,
    library_path,
    source_path,
} SetFlag;

typedef enum
build_exe_add {
    src,
    obj,
    sysobj,
    flag,
} AddFlag;

typedef struct
build {
    /* exe is changed by the user through functions, not directly
     * anything outside of exe is not changed and remains the same.
     */
    struct {
        StringSlice
            root_src,           /* location of main.c */
            output_path,        /* -o */
            include_path,       /* -I */
            library_path;       /* -L */

        struct {
            StringSlice
                path;           /* defines a relative point to look for src
                                 * files (in the src_paths field) to be found
                                 * in. if set to (StringSlice) { 0 }, it won't
                                 * search here.
                                 */
            int search;         /* if not zero, it will use a search path */
        } source_path;

        StringSliceVector
            src_paths,          /* location of other .c files */
            obj_paths,          /* location of obj files */
            sysobj_names,       /* the lib name for shared objects,
                                 * ex. GL (for libGL.so), X11 (for libX11.so),
                                 *     c (for libc.so/.a), m (for libm.so/.a)
                                 */
            flags;              /* other path flags */
    } exe;

    const StringSlice name;               /* the name of the program */

    struct {
        /* i am lazy, so I will store a reference to the
         * arena within the thing here...
         */
        const Arena _arena; /* where the arena will be inlined */
        const Arena *arena; /* where the arena will be referred */
    };
} Build;


void
build_init(Build *b, char *name)
    INIT(
            Build.name, 
            Build._arena, 
            Build.arena
        );

void
build_set(Build *b, SetFlag sf, char *sv)
    INIT(
            Build.root_src, 
            Build.output_path, 
            Build.include_path, 
            Build.library_path, 
            Build.source_path
        );

void
build_add(Build *b, AddFlag af, char *av)
    INIT(
            Build.src_paths,
            Build.obj_paths,
            Build.sysobj_names,
            Build.flags
        );

void
build_vAdd(Build *b, AddFlag af, size_t ac, ...) /* ... is char * list */
    INIT(
            Build.src_paths,
            Build.obj_paths,
            Build.sysobj_names,
            Build.flags
        );

#endif  // OBELISK_H
