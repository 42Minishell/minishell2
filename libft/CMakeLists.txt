cmake_minimum_required(VERSION 3.17)

add_library(
  libft STATIC
  src/ft_put_fd.c
  src/ternary.c
  src/fd/fd_control.c
  src/fd/fd_reader.c
  src/mem/ft_bzero.c
  src/mem/ft_calloc.c
  src/mem/ft_memccpy.c
  src/mem/ft_memchr.c
  src/mem/ft_memcmp.c
  src/mem/ft_memcpy.c
  src/mem/ft_memmove.c
  src/mem/ft_memset.c
  src/mem/ft_realloc_safe.c
  src/str/ft_atoi.c
  src/str/ft_itoa.c
  src/str/ft_split.c
  src/str/ft_str_case.c
  src/str/ft_str_is.c
  src/str/ft_strchr.c
  src/str/ft_strdup.c
  src/str/ft_strjoin.c
  src/str/ft_strlcat.c
  src/str/ft_strlcpy.c
  src/str/ft_strlen.c
  src/str/ft_strmapi.c
  src/str/ft_strncmp.c
  src/str/ft_strnstr.c
  src/str/ft_strrchr.c
  src/str/ft_strtrim.c
  src/str/ft_substr.c
  src/str/listappend.c
  src/str/listcreate.c
  src/str/listfree.c
  src/str/listjoin.c
  src/str/listlen.c src/mem/ft_malloc.c)
target_include_directories(libft PUBLIC inc/)
