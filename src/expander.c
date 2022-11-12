#include "main.h"

static t_token	*split_value(char *value)
{
	int		i;
	char	**sp;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
	sp = ft_split(value, ' ');
	if (sp == NULL)
		panic(sp == NULL, "split returned NULL", __func__);
	while (sp[i])
	{
		add_token_back(&tokens, create_token(sp[i], word));
		if (sp[i + 1] != NULL)
			add_token_back(&tokens, create_token(" ", space));
		free(sp[i]);
		i++;
	}
	free(sp);
	return (tokens);
}

static void	expand_key(t_token **token, t_token *key, t_env *env, bool open)
{
	char	*value;
	char	*rt_value;

	value = find_value(env, key->elem);
	if (is_equal_str(key->elem, "?"))
	{
		rt_value = ft_itoa(g_data.g_last_return);
		add_token_back(token, create_token(rt_value, word));
		free(rt_value);
	}
	else if (value)
	{
		if (value == NULL)
			return ;
		if (*token && get_last_token(*token)->type != d_quote)
			add_token_back(token,
				split_value(value));
		else
			add_token_back(token,
				create_token(value, word));
	}
	else if (open)
		add_token_back(token, create_token("", word));
	free(key->elem);
	free(key);
}

t_token	*expander(t_token *token, t_env *env)
{
	bool	open;
	t_token	*tmp;
	t_token	*new;

	new = NULL;
	open = false;
	while (token)
	{
		tmp = token->next;
		token->next = NULL;
		if (token->type == d_quote)
			open = !open;
		if (token->type == key)
			expand_key(&new, token, env, open);
		else
			add_token_back(&new, token);
		token = tmp;
	}
	return (new);
}
