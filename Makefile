SRC_DIR := src
INC_DIR := inc libft/inc
OUT_DIR := out
OBJ_DIR := obj

NAME := minishell
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
		tokenizer.c ipc.c exec_builtin.c \
		tokenizer_list.c tokenizer_action_whitespace.c \
		tokenizer_action_non_special.c ft_error.c tokenizer_utils.c \
		tokenizer_action_redirections.c tokenizer_action_pipe.c \
		tokenizer_substitute_env.c parent_child_ipc.c \
		fork_wrapper_utils.c heredoc.c heredoc_list.c heredoc_reader.c \
		exec_utils.c
HDRS := inc/builtins.h inc/config.h inc/env.h inc/hashtable.h inc/io.h \
		inc/minishell.h inc/tokenizer.h libft/inc/libft.h \
		libft/inc/fd.h inc/ipc.h inc/heredoc.h
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
	@$(MAKE) -C libft clean
	@echo Build files cleaned.

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean
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
	@$(MAKE) -C libft
