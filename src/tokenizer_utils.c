#include "main.h"

char	*return_token_type(int type)
{
	if (type == redirection)
		return ("redirection");
	else if (type == word)
		return ("word");
	else if (type == pip)
		return ("pipe");
	else if (type == space)
		return ("space");
	else if (type == d_quote)
		return ("d_quote");
	else if (type == s_quote)
		return ("s_quote");
	else if (type == key)
		return ("key");
	return (NULL);
}

bool	is_keyword(char c)
{
	if (c == '>'
		|| c == '<'
		|| c == '|'
		|| c == ' '
		|| (is_quote(c)))
		return (true);
	return (false);
}

bool	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}

char	*add_keyword_token(t_token **head, char *current, bool open)
{
	if ((*current == '>' || *current == '<'))
		redirection_token(head, current);
	else if (*current == '|')
		pip_token(head);
	else if (is_quote(*current))
		quote_token(head, current, open);
	else if (*current == ' ')
	{
		while (*(current + 1) == ' ')
			current++;
		if (*(current + 1) != '\0')
			space_token(head);
	}
	if (*current == *(current + 1)
		&& (*current == '>' || *current == '<'))
		current += 2;
	else
		current++;
	return (current);
}
