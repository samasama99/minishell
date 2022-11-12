#include "main.h"

t_token	*join_adjacent_words(t_token **new, t_token *token)
{
	char	*str;
	t_token	*tmp;

	str = ft_strdup("");
	while (token && token->type == word)
	{
		tmp = token->next;
		str = ft_strjoin_free(str, token->elem);
		free_token(token);
		token = tmp;
	}
	add_token_back(new, create_token(str, word));
	free (str);
	return (token);
}

t_token	*joiner(t_token *token)
{
	t_token	*new;
	t_token	*tmp;

	new = NULL;
	while (token)
	{
		if (token->type == word)
			token = join_adjacent_words(&new, token);
		if (token)
		{
			tmp = token->next;
			token->next = NULL;
			add_token_back(&new, token);
			token = tmp;
		}
	}
	return (new);
}

t_token	*remove_space(t_token *token)
{
	t_token	*new;
	t_token	*tmp;

	new = NULL;
	panic(token == NULL, "NULL PARAM", __func__);
	while (token)
	{
		tmp = token->next;
		token->next = NULL;
		if (token && token->type != space)
			add_token_back(&new, token);
		else if (token && token->type == space)
		{
			free(token->elem);
			free(token);
			token = NULL;
		}
		token = tmp;
	}
	return (new);
}

t_token	*remove_quotes(t_token *token)
{
	t_token	*new;
	t_token	*tmp;

	new = NULL;
	panic(token == NULL, "NULL PARAM", __func__);
	while (token)
	{
		tmp = token->next;
		token->next = NULL;
		if (token->type != s_quote
			&& token->type != d_quote)
			add_token_back(&new, token);
		else
		{
			free(token->elem);
			free(token);
			token = NULL;
		}
		token = tmp;
	}
	return (new);
}

t_token	*corrector(t_token *token)
{
	panic(token == NULL, "NULL PARAM", __func__);
	token = remove_quotes(token);
	token = joiner(token);
	token = remove_space(token);
	return (token);
}
