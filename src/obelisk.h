#ifndef     OBELISK_H
#define     OBELISK_H


#include <obelisk_arena.h>
#include <obelisk_string.h>


typedef struct
build {
    struct {
        StringSlice
            root_path,          /* location of main.c */
            output_path,        /* -o */
            include_path,       /* -I */
            library_path;       /* -L */

        StringSliceVector
            src_paths,          /* location of other .c files */
            obj_paths,          /* location of obj files */
            sysobj_names,       /* the lib name for shared objects,
                                 * ex. GL (for libGL.so), X11 (for libX11.so),
                                 *     c (for libc.so/.a), m (for libm.so/.a)
                                 */
            flags;              /* other path flags */
    } exe;
} Build;


#endif  // OBELISK_H
