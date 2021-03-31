cmake_minimum_required(VERSION 3.17)
project(minishell2 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_COMPILER clang)
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-g -Wall -Wextra -Werror)

add_subdirectory(libft)

add_executable(minishell2 inc/minishell.h src/minishell.c inc/hashtable.h src/hashtable.c src/hashtable_resolver.c inc/env.h src/env.c src/hashtable_iter.c inc/config.h src/resolver.c src/init.c src/path_resolver.c src/prompt.c src/tokenizer.c src/tokenizer_utils.c src/tokenizer_list.c src/exec.c src/tokenizer_list_free.c src/builtins.c src/builtin_export.c src/builtin_unset.c src/builtin_echo.c src/builtin_pwd.c src/builtin_cd.c src/builtin_exit.c)
target_include_directories(minishell2 PUBLIC inc/)
target_link_libraries(minishell2 libft)
