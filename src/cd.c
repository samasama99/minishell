#include "main.h"

int	ft_perror_ret(char *str)
{
	perror(str);
	return (1);
}

static void	update_paths_env(t_env **env)
{
	t_env		*pwd;
	t_env		*opwd;
	char		cwd[PATH_MAX];

	pwd = find_key(*env, "PWD");
	if (pwd == NULL)
		add_variable_back(env,
			create_variable(ft_strdup("PWD"),
				ft_strdup(getcwd(cwd, sizeof(cwd)))));
	else
	{
		opwd = find_key(*env, "OLDPWD");
		if (opwd == NULL && pwd != NULL)
			add_variable_back(env,
				create_variable(ft_strdup("OLDPWD"), pwd->value));
		else
		{
			free(opwd->value);
			opwd->value = pwd->value;
		}
		pwd->value = ft_strdup(getcwd(cwd, sizeof(cwd)));
	}
}

static void	cd_home(t_env	**env)
{
	char	*home_path;

	home_path = find_value(*env, "HOME");
	if (home_path == NULL)
		printf ("MINIShell :: home is not set\n");
	else if (chdir(home_path))
		perror("Error ");
	else
		update_paths_env(env);
}

void	bcd(char *path, t_env **env)
{
	char	cwd[PATH_MAX];

	if (path == NULL || is_equal_str(path, "~"))
		cd_home(env);
	else if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		g_data.g_last_return = ft_perror_ret("Error ");
		cd_home(env);
	}
	else
	{
		if (is_equal_str(path, "-"))
		{
			if (find_key(*env, "OLDPWD")
				&& find_key(*env, "OLDPWD")->value[0])
				bcd (find_key(*env, "OLDPWD")->value, env);
			else
				g_data.g_last_return = (printf ("MINIShell :: OLDPWD not set\n")
						&& 1);
		}
		else if (chdir(path))
			g_data.g_last_return = ft_perror_ret("Error ");
		else
			update_paths_env(env);
	}
}
