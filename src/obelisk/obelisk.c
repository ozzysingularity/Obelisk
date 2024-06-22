#include <obelisk.h>


typedef struct build_step BuildStep;


void
build_add(Build *b, BuildExe *be)
{
}

void
build_exe_add(BuildExe *be, BuildExeFlag flag)
{
}

void
build_exe_set(BuildExe *be, BuildExeFlag flag)
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

