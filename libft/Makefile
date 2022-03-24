SRC_DIR := src src/str src/mem src/fd
INC_DIR := inc
OUT_DIR := out
OBJ_DIR := obj

NAME := libft.a
VPATH := $(SRC_DIR)

CFLAGS := -Wall -Wextra -Werror -I $(INC_DIR)
ifeq ($(DEBUG), 1)
	CFLAGS	:= $(CFLAGS) -g
endif

SRCS	:= $(addprefix ft_, \
			put_fd.c \
			bzero.c calloc.c memccpy.c memchr.c \
			memcmp.c memcpy.c memmove.c memset.c \
			realloc_safe.c atoi.c itoa.c split.c \
			str_case.c str_is.c strchr.c strdup.c \
			strjoin.c strlcat.c strlcpy.c strlen.c \
			strmapi.c strncmp.c strnstr.c strrchr.c \
			strtrim.c substr.c malloc.c \
			)
SRCS	:= $(SRCS) listappend.c listcreate.c \
			listfree.c listjoin.c listlen.c \
			ternary.c fd_control.c fd_reader.c 
HDRS	:= $(addprefix $(INC_DIR)/, libft.h str/list.h fd.h)
OBJS	:= $(SRCS:.c=.o)

$(OBJ_DIR)/%.o : %.c $(HDRS) | $(OBJ_DIR)
	@echo CC $<
	@$(CC) $(CFLAGS) -c -o $@ $<

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR)/,$(OBJS))
	@echo AR $@
	@$(AR) -rcs $@ $^
	@echo $@ Compiled successfully.

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo Build files cleaned.

fclean: clean
	@$(RM) $(NAME)
	@echo $(NAME) removed.

re: fclean all

$(OBJ_DIR):
	@echo Compiling $(NAME)...
	@echo Host: $$(uname -rms)
	@echo Compiler $$($(CC) --version | head -n1)
	@echo CFLAGS: $(CFLAGS)
	@echo ---Start---
	@mkdir -p $(OBJ_DIR) $(OUT_DIR)