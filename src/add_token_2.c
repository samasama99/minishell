#include "main.h"

void	add_word_token(t_token **head, char *start, char *end)
{
	char		*tmp;

	if (start != end)
	{
		tmp = ft_substr(start, 0, end - start);
		add_token_back(head,
			create_token(tmp, word));
		free(tmp);
	}
}

void	add_key_token(t_token **head, char *start, char *end)
{
	char		*tmp;

	if (start != end)
	{
		tmp = ft_substr(start, 0, end - start);
		add_token_back(head,
			create_token(tmp, key));
		free(tmp);
	}
}
