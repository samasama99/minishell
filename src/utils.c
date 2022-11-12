#include "main.h"

void	safe_close(int fd)
{
	if (fd != 0 && fd != 1 && fd != -1)
		close (fd);
}

void	safe_close_2(int in, int out)
{
	safe_close(in);
	safe_close(out);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}

void	panic(bool con, char *msg, const char *func)
{
	if (con == true)
	{
		printf ("Panic attack [%s] : %s\n", msg, func);
		exit (1);
	}
}

bool	is_equal_str(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len != s2_len)
		return (false);
	return (ft_strncmp(s1, s2, s1_len) == 0);
}
