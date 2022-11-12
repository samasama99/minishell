#include "main.h"

char	**ft_split_paths(char **env)
{
	char	**paths;
	char	**path_key_value;

	if (env == NULL)
	{
		printf ("MINIShell : set environment\n");
		exit(1);
	}
	path_key_value = ft_split(env[find_in_2d_array(env, "PATH=")], '=');
	paths = ft_split(path_key_value[1], ':');
	free(path_key_value[0]);
	free(path_key_value[1]);
	return (paths);
}

char	*test_paths(char *cmd, char **paths)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = ft_strjoin("/", cmd);
	while (paths[i])
	{
		tmp2 = ft_strjoin(paths[i], tmp);
		if (access(tmp2, X_OK) == 0)
		{
			free(tmp);
			return (tmp2);
		}
		else
			free(tmp2);
		i++;
	}
	free(tmp);
	i = 0;
	return (NULL);
}

char	*find_in_path(char *cmd, char **env)
{
	char	**paths;
	char	*ret;

	ret = NULL;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	if (env && (find_in_2d_array(env, "PATH") != -1))
	{
		paths = ft_split_paths(env);
		if (paths == NULL)
		{
			printf ("MINIShell : command not found\n");
			return (cmd);
		}
		ret = test_paths(cmd, paths);
		free_2d_array(paths);
		if (ret == NULL)
		{
			g_data.g_last_return = 127;
			printf ("MINIShell : command not found\n");
		}
	}
	else
		printf ("MINIShell : command not found\n");
	return (ret);
}
