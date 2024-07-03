#!/bin/sh

prefix="/usr"
bin="/bin"
lib="/lib"
include="/include"

install() {
    mkdir -p $prefix$bin $prefix$lib $prefix$include/obelisk

    cc  -shared                                     \
        -fPIC                                       \
        -I./src                                     \
        -o/tmp/libobelisk.so                        \
        ./src/obelisk/obelisk.c                     \
        ./src/obelisk_arena/obelisk_arena.c         \
        ./src/obelisk_arena/obelisk_arena_string.c  \
        ./src/obelisk_string/obelisk_string.c

    mv  /tmp/libobelisk.so $prefix$lib/libobelisk.so

    cc  -I./src                                     \
        -o/tmp/obelisk                              \
        ./src/main.c                                \
        -lobelisk

    mv  /tmp/obelisk $prefix$bin/obelisk

    cp  ./src/obelisk.h             $prefix$include/obelisk/build.h
    cp  ./src/obelisk_arena.h       $prefix$include/obelisk/arena.h
    cp  ./src/obelisk_string.h      $prefix$include/obelisk/string.h
    cp  ./src/obelisk_docmacros.h   $prefix$include/obelisk/docmacros.h
    cp  ./src/obelisk_util.h        $prefix$include/obelisk/util.h
}

uninstall() {
    rm  $prefix$bin/obelisk                         \
        $prefix$lib/libobelisk.so

    rm  -r $prefix$include/obelisk
}

while [ $# -ne 0 ]; do
    if [ "$1" = "--prefix" ] || [ "$1" = "-p" ]; then
        shift
        prefix=$1
    elif [ "$1" = "--uninstall" ] || [ "$1" = "-U" ]; then
        uninstall
        exit
    fi

    shift
done

install
