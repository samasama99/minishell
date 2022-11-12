#include "main.h"

bool	is_num(char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (false);
	while (ft_isdigit(s[i]))
		i++;
	if (s[i])
		return (false);
	return (true);
}

void	bexit(char **args, t_seq *seq, t_env *denv, char *line)
{
	long	exit_value;

	exit_value = 0;
	if (args && size_of_2d_array(args) > 1)
	{
		g_data.g_last_return = 1;
		printf("MINIShell: exit: too many arguments\n");
		return ;
	}
	else if (args && size_of_2d_array(args) == 1)
	{
		if (is_num(args[0]))
			exit_value = ft_atoi(args[0]);
		else
		{
			printf("MINIShell: exit: a: numeric argument required\n");
			exit_value = 255;
		}
	}
	rl_clear_history();
	free(line);
	free_seq(seq);
	free_env(denv);
	exit(exit_value);
}
