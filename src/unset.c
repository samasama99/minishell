#include "main.h"

bool	is_valid_key(char *key);

t_env	*remove_variable(t_env *env, char *variable)
{
	t_env	*tmp;
	t_env	*new_env;

	new_env = NULL;
	while (env)
	{
		tmp = env->next;
		env->next = NULL;
		if (is_equal_str(variable, env->key))
		{
			free(env->key);
			free(env->value);
			free(env);
		}
		else
			add_variable_back(&new_env, env);
		env = tmp;
	}
	return (new_env);
}

void	bunset(char **args, t_env **env)
{
	size_t	i;
	int		error;

	i = 0;
	error = 0;
	if (args == NULL)
		return ;
	while (args[i])
	{
		if (is_valid_key(args[i]) == false)
			error = printf ("export: not an identifier: %s\n", args[i]);
		else if (find_key(*env, args[i]))
			*env = remove_variable(*env, args[i]);
		i++;
	}
	if (error)
		g_data.g_last_return = 1;
}
