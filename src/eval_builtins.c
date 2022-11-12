#include "main.h"

int	is_builtin(char *cmd)
{
	size_t	i;

	i = 0;
	panic(cmd == NULL, "PARAM IS NULL", __func__);
	while (cmd[i])
	{
		cmd[i] = ft_tolower(cmd[i]);
		i++;
	}
	if (is_equal_str(cmd, "echo"))
		return (e_echo);
	else if (is_equal_str(cmd, "env"))
		return (e_env);
	else if (is_equal_str(cmd, "export"))
		return (e_export);
	else if (is_equal_str(cmd, "unset"))
		return (e_unset);
	else if (is_equal_str(cmd, "cd"))
		return (e_cd);
	else if (is_equal_str(cmd, "pwd"))
		return (e_pwd);
	else if (is_equal_str(cmd, "exit"))
		return (e_exit);
	return (-1);
}

void	exec_builtin(t_env **env, t_seq *seq, int builtin)
{
	if (builtin == e_echo)
		becho(seq->args + 1, seq->out);
	else if (builtin == e_cd)
		bcd(seq->args[1], env);
	else if (builtin == e_export)
		bexport(seq->args + 1, env, seq->out);
	else if (builtin == e_unset)
		bunset(seq->args + 1, env);
	else if (builtin == e_exit)
		bexit (seq->args + 1, seq, *env, NULL);
	else if (builtin == e_env)
		benv(*env, seq->out);
	else if (builtin == e_pwd)
		bpwd(seq->out);
	safe_close(seq->in);
	safe_close(seq->out);
}
