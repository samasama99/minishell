#include "main.h"

void	dfl(int sig)
{
	g_data.g_heredoc_end = true;
	(void)sig;
	exit(1);
}

int	ft_fork(void)
{
	int	pid;

	g_data.g_forked = true;
	pid = fork();
	if (pid < 0)
	{
		perror("Error ");
		exit (1);
	}
	if (pid == 0)
	{
		signal(SIGINT, dfl);
		rl_catch_signals = 1;
	}
	return (pid);
}

int	ret_wait(int pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	return (status);
}

int	free_and_exit(char *s1, char *s2, int fd1, int fd2)
{
	free(s1);
	free(s2);
	safe_close_2(fd1, fd2);
	return (0);
}
