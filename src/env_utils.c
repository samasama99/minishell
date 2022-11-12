#include "main.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

t_env	*find_key(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp((env)->key, key, ft_strlen(key)) == 0
			&& (ft_strlen(key) == ft_strlen(env->key)))
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env	*create_variable(char *key, char *value)
{
	t_env	*variable;

	variable = malloc (sizeof(t_env));
	if (variable == NULL)
	{
		perror ("Error ");
		exit(1);
	}
	variable->key = key;
	variable->value = value;
	variable->next = NULL;
	return (variable);
}

t_env	*get_last_var(t_env *var)
{
	if (var == NULL)
		return (NULL);
	while (var->next != NULL)
		var = var->next;
	return (var);
}

void	add_variable_back(t_env **list, t_env *new_var)
{
	if (*list == NULL)
		*list = new_var;
	else
		(get_last_var(*list))->next = new_var;
}
