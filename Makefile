SRC_DIR := src
INC_DIR := inc libft/inc
OUT_DIR := out
OBJ_DIR := obj

NAME := minishell2
VPATH := $(SRC_DIR)

CFLAGS := -Wall -Wextra -Werror -I inc -I libft/inc
LDFLAGS := -lreadline
ifeq ($(DEBUG), 1)
	CFLAGS	:= $(CFLAGS) -g
endif

SRCS := builtin_cd.c builtin_echo.c builtin_exit.c builtin_export.c \
		builtin_pwd.c builtin_unset.c builtins.c env.c exec.c \
		hashtable_iter.c hashtable_resolver.c hashtable.c \
		init.c io.c minishell.c path_resolver.c pipe.c prompt.c \
		resolver.c signals_interactive.c signals_noninteractive.c \
		tokenizer_copy.c tokenizer_len.c tokenizer_list_free.c \
		tokenizer_list.c tokenizer_res_env.c tokenizer_type.c \
		tokenizer_utils.c tokenizer.c
HDRS := inc/builtins.h inc/config.h inc/env.h inc/hashtable.h inc/io.h \
		inc/minishell.h inc/tokenizer.h libft/inc/libft.h \
		libft/inc/fd.h
OBJS := $(SRCS:.c=.o)

$(OBJ_DIR)/%.o : %.c $(HDRS) | $(OBJ_DIR)
	@echo CC $<
	@$(CC) $(CFLAGS) -c -o $@ $<

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR)/,$(OBJS)) libft/libft.a
	@echo LD $@
	@$(CC) $(LDFLAGS) -o $@ $^
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
	@echo LDFLAGS: $(LDFLAGS)
	@echo ---Start---
	@mkdir -p $(OBJ_DIR) $(OUT_DIR)

libft/libft.a:
	@echo Compiling dependency $@
	@make -C libft
