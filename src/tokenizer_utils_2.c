#include "main.h"

t_token	*create_token(char *elem, int type)
{
	t_token	*token;

	token = malloc (sizeof(t_token));
	if (token == NULL)
	{
		perror ("Error ");
		exit (1);
	}
	token->elem = ft_strdup(elem);
	token->type = type;
	token->next = NULL;
	return (token);
}

t_token	*get_last_token(t_token *token)
{
	if (token == NULL)
		return (NULL);
	while (token->next)
	{
		token = token->next;
	}
	return (token);
}

void	add_token_back(t_token **list, t_token *new_token)
{
	if (*list == NULL)
		*list = new_token;
	else
		(get_last_token(*list))->next = new_token;
}

void	free_token(t_token *token)
{
	free(token->elem);
	free(token);
}

/* void	delete_first_token(t_token **list) */
/* { */
/* 	t_token	*tmp; */
/* 	t_token	*current; */

/* 	current = *list; */
/* 	tmp = (*list)->next; */
/* 	free(current->elem); */
/* 	free(current); */
/* 	*list = tmp; */
/* } */

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->elem);
		free(token);
		token = tmp;
	}
}
