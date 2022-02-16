cmake_minimum_required(VERSION 3.17)
project(minishell2 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_COMPILER clang)
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-g -Wall -Wextra)

add_subdirectory(libft)

list(
  APPEND
  minishell_SOURCES
  inc/minishell.h
  inc/hashtable.h
  src/hashtable.c
  src/hashtable_resolver.c
  inc/env.h
  src/env.c
  src/hashtable_iter.c
  inc/config.h
  src/resolver.c
  src/init.c
  inc/io.h
  src/io.c
  src/path_resolver.c
  src/prompt.c
  src/tokenizer.c
  src/exec.c
  src/builtins.c
  src/builtin_export.c
  src/builtin_unset.c
  src/builtin_echo.c
  src/builtin_pwd.c
  src/builtin_cd.c
  src/builtin_exit.c
  src/signals_interactive.c
  src/signals_noninteractive.c
  src/pipe.c
src/ipc.c
inc/ipc.h)

list(APPEND test_SOURCES test/test_env.c test/tests.h test/uassert.c
     test/test_hashtable.c test/test_tokenizer.c)

add_executable(minishell2 ${minishell_SOURCES} src/minishell.c src/exec_builtin.c src/builtin_reader.c src/io_read_until_delimiter.c src/debug_options.c src/debug_tokenizer.c src/tokenizer_list.c src/tokenizer_action_whitespace.c src/tokenizer_action_non_special.c src/ft_error.c)
target_include_directories(minishell2 PUBLIC inc/ )
target_link_libraries(minishell2 libft readline)
