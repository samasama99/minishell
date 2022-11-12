#include "main.h"

int	heredoc(char *delimiter)
{
	char	*total;
	char	*line;
	int		fd[2];
	int		pid;

	pipe (fd);
	pid = ft_fork();
	if (pid == 0)
	{
		total = ft_strdup("");
		while (!g_data.g_heredoc_end)
		{
			line = readline("heredoc> ");
			if (line == NULL || is_equal_str(delimiter, line))
				break ;
			total = ft_strjoin_free(ft_strjoin_free(total, line), "\n");
			free(line);
			line = NULL;
		}
		write (fd[1], total, ft_strlen(total));
		exit (free_and_exit(total, line, fd[0], fd[1]));
	}
	if (ret_wait(pid) == 256)
		return (safe_close_2(fd[0], fd[1]), -2);
	return (safe_close (fd[1]), fd[0]);
}

void	eval_io(t_seq *seq, char *rederiction_type, char *file)
{
	panic(rederiction_type == NULL || file == NULL, "NULL PARAM", __func__);
	if (rederiction_type[0] == '<')
	{
		safe_close(seq->in);
		if (rederiction_type[1])
			seq->in = heredoc(file);
		else
			seq->in = open (file, O_RDONLY);
		if (seq->in == -1)
			perror("Error ");
	}
	else
	{
		safe_close(seq->out);
		if (rederiction_type[1])
			seq->out = open (file, O_APPEND | O_WRONLY | O_CREAT, 0644);
		else
			seq->out = open (file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (seq->out == -1)
			perror("Error ");
	}
}

t_token	*eval_redirection(t_seq *seq, t_token *token)
{
	char	*rederiction_type;

	rederiction_type = token->elem;
	token = token->next;
	if (token == NULL)
		printf("MINIShell: ambiguous redirect\n");
	if (token != NULL)
		eval_io(seq, rederiction_type, token->elem);
	if (token == NULL || seq->in < 0 || seq->out < 0)
	{
		while (token && token->type != pip)
			token = token->next;
		free_2d_array(seq->args);
		seq->args = NULL;
	}
	return (token);
}

void	eval_pipes(t_seq *seq)
{
	bool		first;
	bool		last;
	int			fd[2];

	first = true;
	last = false;
	if (seq == NULL || seq->next == NULL)
		return ;
	while (seq)
	{
		if (first == false)
			seq->in = fd[0];
		if (last == false)
		{
			pipe(fd);
			seq->out = fd[1];
			first = false;
		}
		seq = seq->next;
		last = (seq && seq->next == NULL);
	}
}

size_t	seq_size(t_seq *seq)
{
	size_t	size;

	size = 0;
	if (seq == NULL)
		return (0);
	while (seq)
	{
		size++;
		seq = seq->next;
	}
	return (size);
}
