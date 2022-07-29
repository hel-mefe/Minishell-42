#include "../../include/parsing.h"

void	set_quotes(char c, int *singly, int *doubly)
{
	if (c == '\'' && !(*doubly))
		*singly = !(*singly);
	if (c == '\"' && !(*singly))
		*doubly = !(*doubly);
}

char	*digit_after_dollar(char *s, char *old_res, size_t *i, size_t *j)
{
	size_t	a;
	size_t	b;
	char	*part;
	char	*res;

	a = *j;
	b = *i;
	part = slice(s, a, b);
	res = ft_strjoin_free(old_res, part);
	*i += 1;
	*j = b + 1;
	return (res);
}

char	*j_different_than_i(char *s, char *old_res, size_t i, size_t j)
{
	char	*part;
	char	*res;

	part = slice(s, j, i);
	res = ft_strjoin_free(old_res, part);
	return (res);
}

char	*add_variable(size_t *i, size_t *j, char *old_res, t_dollar **dollars)
{
	char	*res;

	res = ft_strjoin(old_res, (*dollars)->val);
	*i += ft_strlen((*dollars)->var);
	*j = (*i) + 1;
	*dollars = (*dollars)->next;
	if (old_res)
		free(old_res);
	return (res);
}

char	*get_status(char *old_res, size_t *i, size_t *j)
{
	char	*res;
	char	*part;

	part = ft_itoa(g_global.get_nb_status);
	res = ft_strjoin_free(old_res, part);
	*i += 1;
	*j = (*i) + 1;
	return (res);
}
