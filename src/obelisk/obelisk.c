#include <limits.h>
#include <obelisk.h>

#if !defined(__linux__) || !defined(__gnu_linux__) || !defined(__unix__)

    #error "Platform not supported"

#endif


BuildError b_errno;

Arena _set_arena,
      _add_arena,
      *set_arena = &_set_arena,
      *add_arena = &_add_arena;

String _command, *command;

void
build_cleanUp(Build *b)
{
    arena_free(set_arena);
    arena_free(add_arena);

    arena_free(b->arena);
    string_free(command);
}

void
build_init(Build *b, char *name)
{
    b->arena = &b->_arena;
    arena_init(b->arena, 512);

    arena_init(set_arena, 512);
    arena_init(add_arena, 512);

    b->name = stringSlice(name);

    b->exe.compiler = stringSlice("cc");
    b->exe.root_src = (StringSlice){ 0 };
    b->exe.output_path = (StringSlice){ 0 };
    b->exe.source_path.path = (StringSlice){ 0 };
    b->exe.source_path.search = 0;

    b->exe.src_paths = stringSlice_vectorNew(b->arena, 16);

    b->exe.obj_paths = stringSlice_vectorNew(b->arena, 8);

    b->exe.sysobj_names = stringSlice_vectorNew(b->arena, 8);

    b->exe.include_path = stringSlice_vectorNew(b->arena, 4);

    b->exe.library_path = stringSlice_vectorNew(b->arena, 8);

    b->exe.flags = stringSlice_vectorNew(b->arena, 24);

    _command = string_alloc(0);
    command = &_command;

    if (s_errno > A_good) {
        b_errno = B_init_fail;
    }

    b_errno = B_ok;
}

void
build_set(Build *b, SetFlag sf, char *sv)
{
    StringSlice output_flag = stringSlice("-o"),
                setval = stringSlice(sv);

    String str;

    switch (sf) {
    case compiler:
        b->exe.compiler = setval;
        break;

    case root_src:
        b->exe.root_src = setval;
        break;

    case source_path:
        b->exe.source_path.search = 1;
        b->exe.source_path.path = setval;
        break;

    case output_path:
        str = arenaString_cat(set_arena, &output_flag, &setval);

        b->exe.output_path = string_slice(&str, 0, 0);
        break;

    default:
        fprintf(stderr, "Encountered a nonexistant or incorrect flag\n");
    }
}
    

void
build_add(Build *b, AddFlag af, char *av)
{
    String path;
    StringSlice sli,
                setval = stringSlice(av);

    switch (af) {
    case src:
        if (add_arena->cur->pos > 0) {
            arena_addChunk(add_arena);
        }

        if (b->exe.source_path.search) {
            path = arenaString_catWithDelimitChar(add_arena, &b->exe.source_path.path,
                    &setval, '/');
        } else {
            stringSlice_vectorPut(&b->exe.src_paths, setval);
            break;
        }

        stringSlice_vectorPut(&b->exe.src_paths, string_slice(&path, 0, 0));

        if (s_errno > S_good) {
            b_errno = B_add_fail;
        }

        break;

    case obj:
        stringSlice_vectorPut(&b->exe.obj_paths, setval);

        if (s_errno > S_good) {
            b_errno = B_add_fail;
            break;
        }

        break;

    case sysobj:
        if (add_arena->cur->pos > 0) {
            arena_addChunk(add_arena);
        }

        sli = stringSlice("-l");
        path = arenaString_cat(add_arena, &sli, &setval);

        stringSlice_vectorPut(&b->exe.sysobj_names, string_slice(&path, 0, 0));

        if (s_errno > S_good) {
            b_errno = B_add_fail;
            break;
        }

        break;

    case include_path:
        if (add_arena->cur->pos > 0) {
            arena_addChunk(add_arena);
        }

        if (a_errno > A_good) {
            b_errno = B_add_fail;
        }

        sli = stringSlice("-I");

        path = arenaString_cat(add_arena, &sli, &setval);

        stringSlice_vectorPut(&b->exe.src_paths, string_slice(&path, 0, 0));

        break;

    case library_path:
        if (add_arena->cur->pos > 0) {
            arena_addChunk(add_arena);
        }

        if (a_errno > A_good) {
            b_errno = B_add_fail;
        }

        sli = stringSlice("-L");

        path = arenaString_cat(add_arena, &sli, &setval);

        stringSlice_vectorPut(&b->exe.src_paths, string_slice(&path, 0, 0));

        break;

    case flag:
        stringSlice_vectorPut(&b->exe.flags, stringSlice(av));

        break;

    default:
        fprintf(stderr,
                "Encountered a nonexistant or incorrect flag: skipping\n");
        break;
    }

    b_errno = B_ok;
}
    
void
build_vAdd(Build *b, AddFlag af, ...)
{

}

void
build_command(Build *b)
{
    size_t i;

    _command = string_cat(command, &b->exe.compiler);

    for (i = 0; i < b->exe.flags.pos; i++) {
        _command = string_catWithDelimitChar(command, &b->exe.flags.slis[i], ' ');
    }

    for (i = 0; i < b->exe.include_path.pos; i++) {
        _command = string_catWithDelimitChar(command, &b->exe.include_path.slis[i], ' ');
    }
    
    for (i = 0; i < b->exe.library_path.pos; i++) {
        _command = string_catWithDelimitChar(command, &b->exe.library_path.slis[i], ' ');
    }

    StringSlice oflag = stringSlice("-o");
    String output = string_cat(&oflag, &b->name);

    _command = string_catWithDelimitChar(command, &output, ' ');
    
    _command = string_catWithDelimitChar(command, &b->exe.output_path, ' ');

    _command = string_catWithDelimitChar(command, &b->exe.root_src, ' ');

    for (i = 0; i < b->exe.src_paths.pos; i++) {
        _command = string_catWithDelimitChar(command, &b->exe.src_paths.slis[i], ' ');
    }

    for (i = 0; i < b->exe.obj_paths.pos; i++) {
        _command = string_catWithDelimitChar(command, &b->exe.obj_paths.slis[i], ' ');
    }

    for (i = 0; i < b->exe.sysobj_names.pos; i++) {
        _command = string_catWithDelimitChar(command, &b->exe.sysobj_names.slis[i], ' ');
    }

    char cmd[513];

    sprintf(cmd, "%.*s", (int) command->len, command->str);
    cmd[512] = 0;

    system(cmd);

    build_cleanUp(b);
}

