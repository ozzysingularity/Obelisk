#ifndef OBELISK_API_H
#define OBELISK_API_H


#define PLACEHOLDER int x


typedef struct build Build;

typedef struct build_exe BuildExe;

typedef struct build_step BuildStep;

typedef struct build_option {
    void *p;
    unsigned int n;
} BuildOption;

typedef struct build_exe_option {
    void *p;
    unsigned int n;
} BuildExeOption;

typedef enum build_flag {
    OBELISK_EXE,
    OBELISK_SRC,
    OBELISK_SRCROOT,
    OBELISK_SRCDEP,
} BuildFlag;

typedef enum build_exe_set_flag {
    OBELISK_src,
    OBELISK_src_root,
    OBELISK_src_dep,
    OBELISK_obj,
    OBELISK_obj_shared,
    OBELISK_obj_archive,
} BuildExeSetFlag;

typedef enum build_command_type {
    OBELSIK_EXEC,
} BuildCommand;


/* Adds a build context into a BuildExe */
void build_add(Build *b, BuildExe *be);

/* Adds items to a BuildExe */
void build_exe_add(BuildExe *be, BuildFlag );

/*  */
void build_exe_set(BuildExe *be, BuildExeSetFlag sf);

/*  */
void build_exe_(BuildExe *be, const char *path);

/*  */
void build_compile(BuildExe *be);

/*  */
void build_command_add(Build *b, BuildStep *bs, char * command,
        char * description);

/*  */
void build_command_register(BuildStep *bs, BuildExe *be, BuildCommand cmd);


#endif
/*
 *  void
 *  build(Build *b)
 *  {
 *      BuildExe exe;
 *      BuildStep step;
 *      
 *      build_add(b,  &exe, OBELISK_EXE,        { 0 });
 *                                              
 *      build_exe_add(&exe, OBELISK_SRCROOT,    { .p = "src/main.c" });
 *      build_exe_add(&exe, OBELSIK_SRCDEP,     { .p = "src/obelisk.c" });
 *                                              
 *      build_exe_set(&exe, OBELISK_TARGET,     { .n = OBELISK_OSLINUX });
 *                                              
 *      build_exe_set(&exe, OBELISK_DEBUG,      { .n = OBELISK_TRUE });
 *
 *      build_exe_compile(&exe);
 *
 *      build_command_add(b, &step, "run", "Run the program");
 *      build_command_register(&step, &exe, OBELISK_EXEC);
 *  }
 */
