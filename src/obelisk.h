#ifndef     OBELISK_H
#define     OBELISK_H


#include <obelisk_docmacros.h>
#include <obelisk_arena.h>
#include <obelisk_string.h>


typedef enum
build_error {
    B_ok = 0,

    B_good,
    
    B_add_fail,
    B_init_fail,
    B_fail = 255, /* simple fail, unknown cause */
} BuildError;

typedef enum
build_exe_set {
    compiler,
    root_src,
    output_path,
    source_path,
} SetFlag;

typedef enum
build_exe_add {
    src,
    obj,
    sysobj,
    include_path,
    library_path,
    flag,
} AddFlag;

typedef struct
build {
    /* exe is changed by the user through functions, not directly
     * anything outside of exe is not changed and remains the same.
     */
    struct {
        StringSlice
            compiler,
            root_src,           /* location of main.c */
            output_path;        /* -o */

        struct {
            StringSlice path;   /* defines a relative point to look for src
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
            include_path,       /* -I */
            library_path,       /* -L */
            flags;              /* other path flags */
    } exe;

    StringSlice name;               /* the name of the program */

    struct {
        /* i am lazy, so I will store a reference to the
         * arena within the thing here...
         */
        Arena _arena; /* where the arena will be inlined */
        Arena *arena; /* where the arena will be referred */
    };
} Build;


extern BuildError b_errno;
extern String *command;


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
build_vAdd(Build *b, AddFlag af, ...) /* ... is char * list, if NULL,
                                       * end of list */
    INIT(
            Build.src_paths,
            Build.obj_paths,
            Build.sysobj_names,
            Build.flags
        );

void
build_command(Build *b);

#endif  // OBELISK_H
