#include "main.h"

bool	check_quotes(t_token *token)
{
	bool		open_quotes;

	open_quotes = false;
	while (token)
	{
		if (token->type == d_quote || token->type == s_quote)
			open_quotes = !open_quotes;
		token = token->next;
	}
	if (open_quotes)
		return (true);
	return (false);
}

bool	check_redirection(t_token *token)
{
	bool		unfulfilled;

	unfulfilled = false;
	while (token)
	{
		if (token->type == redirection && unfulfilled == false)
			unfulfilled = true;
		else if (token->type == word || token->type == key
			|| token->type == d_quote || token->type == s_quote)
			unfulfilled = false;
		else if (token->type != space && unfulfilled == true)
			return (true);
		token = token->next;
	}
	if (unfulfilled)
		return (true);
	return (false);
}

bool	check_first_and_last(t_token *token)
{
	t_token	*last;
	t_token	*first;

	if (token == NULL)
		return (true);
	first = token;
	last = get_last_token(token);
	if (first->type == pip)
		return (true);
	if (last->type == pip)
		return (true);
	return (false);
}

bool	check_pip(t_token *token)
{
	size_t	words;
	size_t	type;

	words = 0;
	if (token == NULL)
		return (true);
	while (token)
	{
		type = token->type;
		if (type == word || type == key)
			words++;
		else if (type == pip)
		{
			if (words == 0)
				return (true);
			else if (words != 0)
				words = 0;
		}
		token = token->next;
	}
	return (false);
}

bool	syntax_analysis(t_token *tokens)
{
	if (check_quotes(tokens)
		|| check_redirection(tokens)
		|| check_first_and_last(tokens)
		|| check_pip(tokens))
	{
		printf ("MiniSHELL : syntax error\n");
		return (true);
	}
	return (false);
}
