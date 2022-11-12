#include "main.h"

static char	**add_element_to_last_2d_array(char **array, char *elem,
			size_t index, size_t size)
{
	char		**new_array;
	size_t		i;
	size_t		j;

	(void)index;
	i = 0;
	j = 0;
	new_array = malloc(sizeof(char *) * (size + 2));
	if (new_array == NULL)
		return (NULL);
	i = 0;
	while (array[j])
		new_array[i++] = array[j++];
	new_array[i] = elem;
	new_array[i + 1] = NULL;
	free(array);
	return (new_array);
}

static char	**add_element_not_last_2d_array(char **array, char *elem,
			size_t index, size_t size)
{
	char		**new_array;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	new_array = malloc(sizeof(char *) * (size + 2));
	if (new_array == NULL)
		return (NULL);
	i = 0;
	while (array[j])
	{
		if (i == index)
		{
			new_array[i] = elem;
			i++;
		}
		new_array[i++] = array[j++];
	}
	new_array[i] = NULL;
	free(array);
	return (new_array);
}

char	**add_element_2d_array(char **array, char *elem, size_t index)
{
	size_t		size;

	size = 0;
	if (array == NULL)
		return (NULL);
	while (array[size])
		size++;
	if (index > size)
		return (NULL);
	if (index == size)
		return (add_element_to_last_2d_array(array, elem, index, size));
	else
		return (add_element_not_last_2d_array(array, elem, index, size));
}
