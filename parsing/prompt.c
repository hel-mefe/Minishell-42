#include "../include/parsing.h"

char	*get_prompt_path(t_env *head)
{
	while (head)
	{
		if (!ft_strcmp(head->name, "PWD"))
			return (ft_strdup(head->data));
		head = head->next;
	}
	return (NULL);
}

char	*show_prompt(t_env *head)
{
	char	*path;
	char	*input;

	path = get_prompt_path(head);
	printf(PATH_COLOR"(%s)$\n", path);
	free(path);
	input = readline(INPUT_COLOR"🧬 ➡️ ");
	return (input);
}
