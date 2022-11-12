#include "main.h"
#define MAX_NAME 256
#define PROMPT_SIZE 8

void	cwd_prompt(char *cwd, char prom[])
{
	size_t	i;
	char	**tmp;

	i = 0;
	tmp = ft_split(cwd, '/');
	while (tmp && tmp[i] && tmp[i + 1])
		i++;
	ft_strlcat(prom, "➦ ",
		ft_strlen("➦ ") + ft_strlen(prom) + 1);
	ft_strlcat(prom, tmp[i],
		ft_strlen(tmp[i]) + ft_strlen(prom) + 1);
	ft_strlcat(prom, " : ",
		ft_strlen(" : ") + ft_strlen(prom) + 1);
	free_2d_array(tmp);
}

static char	*prompt(t_env *env, char prom[])
{
	char		*cwd_ptr;
	char		*home_path;
	char		cwd[PATH_MAX];

	prom[0] = '\0';
	if (env == NULL)
	{
		printf ("MINIShell : pls set environment\n");
		exit (1);
	}
	cwd_ptr = getcwd(cwd, sizeof(cwd));
	home_path = find_value(env, "HOME");
	if (cwd_ptr != NULL && home_path != NULL)
	{
		if (is_equal_str(home_path, cwd))
			return ("➦  ~ : ");
		if (cwd[0] == '/' && cwd[1] == '\0')
			return ("➦  / : ");
		if (cwd_ptr != NULL)
		{
			cwd_prompt(cwd, prom);
			return (prom);
		}
	}
	return ("➦  ? : ");
}

void	shell_loop(t_env **denv)
{
	t_seq		*seq;
	char		*line;
	char		prom[MAX_NAME + PROMPT_SIZE];

	while (1337)
	{
		seq = NULL;
		line = NULL;
		rl_catch_signals = 0;
		g_data.g_forked = false;
		line = readline(prompt(*denv, prom));
		if (line == NULL || is_equal_str("exit", line))
			bexit(NULL, NULL, *denv, line);
		if (*line == '\0')
		{
			free(line);
			line = NULL;
			continue ;
		}
		ft_add_history(line);
		seq = parsing(line, *denv);
		eval_seq(seq, denv);
		free(line);
		free_seq(seq);
	}
}
