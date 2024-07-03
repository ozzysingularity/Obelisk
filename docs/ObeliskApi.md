# 1. Introduction to the Obelisk API

To access the symbols for the Obelisk Build System, you must include the
library.

```c
#include <obelisk/build.h>
```

After that, you must write the build system entry point:

```c
void
build(Build *b) { ... }
```

To do so, you need a Build pointer type, similar to Zig's build entry:

```zig
fn build(b: *std.Build) void { ... }
```

Next, you need to initialize the build instance using `build_init`.

`build_init` is defined as such:

```c
void build_init(Build *b, char *output_path);
```

So, for instance, if I want to make an executable in the `./bin` directory, I
do:

```c
// In build(...):
build_init(b, "./bin/executable_name");
```

Next, you want to set a compiler. You do that by using the `build_set` function:

```c
build_set(b, compiler, "gcc"); // sets the compiler to gcc
```

There is a default compiler option set, which is `cc`.


Now, set a root source file:

```c
build_set(b, root_src, "main.c");
```

NOTE: this does not adhere to the `source_path` flag, so you would have to put
the full path to the root souce file; for instance `./src/main.c`.


To set a directory to look for all of the source files without having to prefix
it explicitly, you would do this:

```c
build_set(b source_path, "./src");
```

A pattern that would emerge in a modular project is setting the source path
for each directory for each module as such:

```c
build_set(b, source_path, "./src/mod1");
build_add(b, src, "modfile.c");

build_set(b, source_path, "./src/mod2");
build_add(b, src, "modfile.c");
build_add(b, src, "modfile2.c");

// etc...
```


# 2. Obelisk API Function Index

```c
// User defined entry point to the build system
void build(Build *);

// Initializes the build instance
void build_init(Build *, char *output_path);

// Adds a value to the vector coresponding with the AddFlag
void build_add(Build *, AddFlag, char *value);

// Sets a build instance value coresponding with the SetFlag
void build_set(Build *, SetFlag, char *value);

// Generates a command to compile the project
void build_compile(Build *);

typedef enum add_flag {
    // adds a source file to the source list
    src,

    // adds an object to the obj list
    obj,

    /* adds a link flag to the sysobj list; takes an input and converts it to
     * the compiler accepted flag, for instance, build_add(b, sysobj, "GL")
     * is converted to the flag `-lGL`
     */
    sysobj,

    // converts input to `-I[input]`
    include_path,

    // converts input to `-L[input]`
    library,
} AddFlag;

typedef enum set_flag {
    // sets the compiler to use
    compiler,
    
    // sets the root source file; this would the one with the entry point function in it
    root_src,

    // sets the path that contains all of the source files
    source_path
} SetFlag;
```

For more information, please feel obliged to look at the documentation in the
`obelisk.h` header file, which contains all of the stuff for the build system
in particular.
