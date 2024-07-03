# About

Obelisk Build System is inspired by [Tsoding's NoBuild](https://github.com/tsoding/nobuild) build system and the 
[Zig Build System](https://ziglang.org/documentation/0.13.0/#Zig-Build-System). The philosophy is similar: why learn
another language to build you language (like GNU Make for instance), rather than just writing it in an actual
programming language?

These are lofty goals that I have, but I think it's an interesting project to help me learn programming better.

---

# Platforms Supported
- Linux

---

# Install Guide

## Building
```shell
    $ sh ./scripts/build.sh
        OR
    $ chmod +x ./scipts/build.sh && ./scripts/build.sh
```

## Building and Installing
```shell
    $ sh ./scripts/install.sh
        OR
    $ chmod +x ./scipts/install.sh && ./scripts/build.sh
```

---

# Using

## Obelisk API (overview)

```c
/* include the library header file */
#include <obelisk/build.h>

void
build(Build *b)
{
    build_init(b, "Program Name");

    build_set(b, root_src, "src/main.c");

    build_set(b, source_path, "src");

    build_add(b, include_path, "src");

    build_add(b, src, "dependancy.c");

    build_compile(b);
}
```

---

# Plans for the Future

- Build an interface to install a program
- Support more platforms (i.e. Windows, OpenBSD, MacOS);
- Make sure to clean up all memory properly to avoid memory leaks;
- Add more flags to the Obelisk command.
