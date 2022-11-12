#include "main.h"

void	free_seq(t_seq *seq)
{
	t_seq	*tmp;

	while (seq)
	{
		tmp = seq->next;
		free_2d_array(seq->args);
		free(seq);
		safe_close(seq->in);
		safe_close(seq->out);
		seq = tmp;
	}
}

t_seq	*create_seq(char **args, int in, int out)
{
	t_seq	*seq;

	panic(args == NULL, "NULL PARAM", __func__);
	seq = malloc (sizeof(t_seq));
	if (seq == NULL)
	{
		perror ("Error\n");
		exit (1);
	}
	seq->args = args;
	seq->in = in;
	seq->out = out;
	seq->next = NULL;
	return (seq);
}

t_seq	*get_last_seq(t_seq *seq)
{
	if (seq == NULL)
		return (NULL);
	while (seq->next)
		seq = seq->next;
	return (seq);
}

void	add_seq_back(t_seq **list, t_seq *new_seq)
{
	panic(new_seq == NULL, "NULL PARAM", __func__);
	if (*list == NULL)
		*list = new_seq;
	else
		(get_last_seq(*list))->next = new_seq;
}
