#include "main.h"

t_seq	*parsing(char *line, t_env *denv)
{
	t_token	*list;
	t_seq	*seq;

	list = NULL;
	seq = NULL;
	if (line)
		tokenizer(&list, line);
	if (list && syntax_analysis(list) == false)
	{
		list = expander(list, denv);
		if (list)
			list = corrector(list);
		if (list)
			seq = parser(list);
	}
	free_tokens(list);
	return (seq);
}
