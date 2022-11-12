#include "main.h"

t_seq	*pre_parser(t_token *list)
{
	t_seq	*tmp;
	t_seq	*head;

	head = NULL;
	while (list)
	{
		tmp = create_seq(init_2d_array(), 0, 1);
		tmp->args[0] = NULL;
		while (list && list->type != pip)
			list = list->next;
		add_seq_back(&head, tmp);
		if (list && list->type == pip)
			list = list->next;
	}
	eval_pipes(head);
	return (head);
}

t_seq	*parser(t_token *list)
{
	t_seq	*head;
	t_seq	*tmp;

	head = pre_parser(list);
	tmp = head;
	while (list)
	{
		while (list && list->type != pip)
		{
			if (list->type == redirection)
				list = eval_redirection(tmp, list);
			else
				tmp->args = add_element_2d_array_last(tmp->args,
						ft_strdup(list->elem));
			if (list && list->type != pip)
				list = list->next;
		}
		if (list && list->type == pip)
		{
			tmp = tmp->next;
			list = list->next;
		}
	}
	return (head);
}
