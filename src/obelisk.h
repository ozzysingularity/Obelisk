#ifndef     OBELISK_H
#define     OBELISK_H


#include <obelisk_string.h>


typedef struct
build {
    struct {
        StringSlice root_path;
        StringSliceVector src_paths;
    } exe;
} Build;


#endif  // OBELISK_H
