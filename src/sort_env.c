#include "main.h"

void	print_a_sorted_env(t_env *env, int fd)
{
	char	c;
	t_env	*head;

	c = 32;
	head = env;
	while (c < 127)
	{
		while (env)
		{
			if (env->key[0] == c)
			{
				ft_putstr_fd("declare -x ", fd);
				ft_putstr_fd(env->key, fd);
				if (env->value[0])
					ft_putstr_fd("=", fd);
				ft_putstr_fd(env->value, fd);
				ft_putstr_fd("\n", fd);
			}
			env = env->next;
		}
		env = head;
		c++;
	}
}
