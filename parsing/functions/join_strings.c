#include "../../include/parsing.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	len;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	if (!s1 && s2)
		return (ft_strdup(s2));
	else if (!s2 && s1)
		return (ft_strdup(s1));
	else if (!s1 && !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len = len1 + len2;
	res = (char *) malloc ((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < len1 && s1[i])
		res[i] = s1[i];
	j = 0;
	while (i < len && s2[j])
		res[i++] = s2[j++];
	res[i] = 0;
	return (res);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;
	size_t	len;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	if (!s1 && s2)
		return (s2);
	else if (!s2 && s1)
		return (s1);
	else if (!s1 && !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len = len1 + len2;
	res = (char *) malloc ((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < len1 && s1[i])
		res[i] = s1[i];
	j = 0;
	while (i < len && s2[j])
		res[i++] = s2[j++];
	res[i] = 0;
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (res);
}
