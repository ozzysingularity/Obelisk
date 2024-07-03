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

## Obelisk API

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

For more, look at the DOCUMENTATION file.

---

# Plans for the Future

- Build an interface to install a program aswell as install it;
- Support more platforms (i.e. Windows, OpenBSD, MacOS).
