#include "main.h"

static int	is_flag(char *str)
{
	int		i;

	i = 0;
	panic(str == NULL, "NULL PARAM", __func__);
	if (str[0] != '-' || str[1] != 'n')
		return (0);
	++i;
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i])
		return (0);
	return (1);
}

void	becho(char **args, int fd)
{
	int	i;

	i = 0;
	if (fd != -1 && args != NULL && *args != NULL)
	{
		while (args[i] && is_flag(args[i]))
			++i;
		while (args[i])
		{
			ft_putstr_fd(args[i], fd);
			if (args[i + 1])
				ft_putstr_fd(" ", fd);
			i++;
		}
		if (is_flag(args[0]) != true)
			ft_putstr_fd("\n", fd);
	}
	else
		ft_putstr_fd("\n", fd);
}
