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
  src/tokenizer_copy.c
  src/tokenizer_len.c
  src/tokenizer_utils.c
  src/tokenizer_list.c
  src/tokenizer_type.c
  src/exec.c
  src/tokenizer_list_free.c
  src/tokenizer_res_env.c
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

add_executable(minishell2 ${minishell_SOURCES} src/minishell.c src/exec_builtin.c src/io_delim.c src/builtin_reader.c)
target_include_directories(minishell2 PUBLIC inc/ )
target_link_libraries(minishell2 libft readline)

# add_executable(minishell2_test ${minishell_SOURCES} ${test_SOURCES}
#                                test/test_entry.c)
# target_include_directories(minishell2_test PUBLIC inc/)
# target_link_libraries(minishell2_test libft)
# target_link_libraries(minishell2_test LIBREADLINE)
