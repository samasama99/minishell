#include "main.h"

void	bpwd(int fd)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	ft_putstr_fd(cwd, fd);
	ft_putstr_fd("\n", fd);
}
