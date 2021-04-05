#include "minishell.h"
#include "tests.h"

static int	token_len(t_token *head)
{
	int	len;

	len = 1;
	head = head->next;
	while (head && head->type != executable && head->token)
	{
		head = head->next;
		len++;
	}
	return (len);
}

static void	split_test(t_state *state)
{
	t_token	*tokens;

	tokens = tokenizer(ft_strdup("arg1 \"arg2 $A arg2\" arg3"), state->env->env);
	uassert((token_len(tokens) == 3), "split_test: invalid amount of tokens");
	uassert((ft_strncmp(tokens->token, "arg1", 4) == 0),
		"split_test: arg1 mismatch");
	uassert((ft_strncmp(tokens->next->token, "arg2 arg2", 10) == 0),
		"split_test: arg2 mismatch");
	uassert((ft_strncmp(tokens->next->next->token, "arg3", 4) == 0),
		"split_test: arg3 mismatch");
	tokenizer_list_free(tokens);
	tokens = tokenizer(ft_strdup("arg1 \'arg2 $A arg2\' arg3"), state->env->env);
	uassert((token_len(tokens) == 3), "split_test: invalid amount of tokens");
	uassert((ft_strncmp(tokens->token, "arg1", 4) == 0),
		"split_test: arg1 mismatch");
	uassert((ft_strncmp(tokens->next->token, "arg2 $A arg2", 13) == 0),
		"split_test: arg2 mismatch");
	uassert((ft_strncmp(tokens->next->next->token, "arg3", 4) == 0),
		"split_test: arg3 mismatch");
	tokenizer_list_free(tokens);
}

static void	env_test(t_state *state)
{
	t_token	*tokens;

	tokens = tokenizer(ft_strdup("$SHELL"), state->env->env);
	uassert((token_len(tokens) == 1), "env_test: invalid amount of tokens");
	uassert((ft_strncmp(tokens->token, "test", 5) == 0),
		"env_test: basis subsitition fail");
	tokenizer_list_free(tokens);
	tokens = tokenizer(ft_strdup("\'$SHELL\'"), state->env->env);
	uassert((token_len(tokens) == 1), "env_test: invalid amount of tokens");
	uassert((ft_strncmp(tokens->token, "$SHELL", 7) == 0),
		"env_test: literal fail");
	tokenizer_list_free(tokens);
	tokens = tokenizer(ft_strdup("\'$SHELL\' \"$SHELL\" $SHELL"), state->env->env);
	uassert((token_len(tokens) == 3), "env_test: invalid amount of tokens");
	uassert((ft_strncmp(tokens->token, "$SHELL", 7) == 0),
		"env_test: literal fail");
	uassert((ft_strncmp(tokens->next->token, "test", 5) == 0),
		"env_test: doublequote fail");
	uassert((ft_strncmp(tokens->next->next->token, "test", 5) == 0),
		"env_test: combo fail");
	tokenizer_list_free(tokens);
}

void	test_tokenizer(void)
{
	t_state	state;

	state.env = env_init();
	env_populate(state.env, "test");
	split_test(&state);
	env_test(&state);
	env_free(state.env);
}
