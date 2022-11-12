#include "main.h"

char	*find_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0
			&& (ft_strlen(key) == ft_strlen(env->key)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

t_env	*dup_env(char **env)
{
	size_t	i;
	t_env	*head;
	char	*key;
	char	*value;

	i = 0;
	head = NULL;
	panic(env == NULL, "NULL pointer as param", __func__);
	while (env[i])
	{
		key = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		if (ft_strncmp(key, "OLDPWD", ft_strlen(key)) == 0)
			value = ft_strdup("");
		else if (ft_strncmp(key, "SHLVL", ft_strlen(key)) == 0)
			value = ft_itoa(ft_atoi(ft_strchr(env[i], '=') + 1) + 1);
		else
			value = ft_strdup(ft_strchr(env[i], '=') + 1);
		add_variable_back(&head, create_variable(key, value));
		i++;
	}
	return (head);
}

char	**t_env_to_2d_array(t_env *denv)
{
	char	**env;
	char	*tmp;

	if (denv == NULL)
		printf("MINIShell : set environment\n");
	env = init_2d_array();
	while (denv)
	{
		tmp = ft_strjoin_free(ft_strjoin(denv->key, "="), denv->value);
		env = add_element_2d_array_last(env, tmp);
		denv = denv->next;
	}
	return (env);
}

void	benv(t_env *env, int fd)
{
	panic(env == NULL, "environment is NULL", __func__);
	while (env)
	{
		if (env->value[0])
		{
			ft_putstr_fd (env->key, fd);
			ft_putstr_fd ("=", fd);
			ft_putstr_fd (env->value, fd);
			ft_putstr_fd ("\n", fd);
		}
			env = env->next;
	}
}
