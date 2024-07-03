#!/bin/sh

set -e

mkdir -p ./bin

cc  -Isrc -O3                                       \
    -o./bin/obelisk                                 \
    ./src/main.c                                    \
    ./src/obelisk/obelisk.c                         \
    ./src/obelisk_arena/obelisk_arena.c             \
    ./src/obelisk_arena/obelisk_arena_string.c      \
    ./src/obelisk_string/obelisk_string.c

exit 0
