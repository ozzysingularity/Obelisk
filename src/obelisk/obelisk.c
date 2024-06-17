#include <obelisk.h>


typedef struct build Build;

typedef struct build_exe {
    Build *owner;
    
} BuildExe;

typedef struct build_step BuildStep;


/* Adds a build context into a BuildExe */
void
build_add(Build *b, BuildExe *be)
{
    
}

/* Adds items to a BuildExe */
void
build_exe_add(BuildExe *be, BuildFlag flag)
{
    
}

/*  */
void
build_exe_set(BuildExe *be, BuildExeSetFlag flag)
{

}

/*  */
void
build_exe_(BuildExe *be, const char *path)
{

}

/*  */
void
build_compile(BuildExe *be)
{

}

/*  */
void
build_command_add(
    Build *b,
    BuildStep *bs,
    char * command,
    char * description
)
{

}

/*  */
void
build_command_register(
    BuildStep *bs,
    BuildExe *be,
    BuildCommand cmd
)
{

}
