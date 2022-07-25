/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 12:30:03 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/20 19:18:54 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

int	ft_length_word(const char *str, char c)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		if (str[i] != c && str[i] != '\0')
			j++;
		while (str[i] != '\0' && str[i] != c)
			i++;
	}
	return (j);
}

char	**allocate_memory(char const *s, char c)
{
	char	**res;
	int		n;

	n = ft_length_word(s, c);
	res = (char **) malloc(n * sizeof(char *) + sizeof(NULL));
	if (!res)
		return (NULL);
	res[n] = 0;
	return (res);
}

/* Signals[0] Where to start from
 * Signals[1] Where to end
 * Signals[2] How much memory to allocate
 */
int	*where_to_start_from(const char *res, char c, int index)
{
	int	*signals;
	int	i;

	i = index;
	while (res[i] == c)
		i++;
	signals = (int *) malloc (3 * sizeof(int));
	signals[0] = i;
	while (res[i] != c && res[i])
		i++;
	signals[1] = i;
	signals[2] = signals[1] - signals[0] + 1;
	return (signals);
}	

void	fulfill_str(char const *s, char *res, int *signals)
{
	int	a;
	int	b;
	int	i;

	a = signals[0];
	b = signals[1];
	i = 0;
	while (a < b)
	{
		res[i] = s[a];
		a++;
		i++;
	}
	res[i] = 0;
}

char	**ft_split(char const *s, char c)
{
	char			**str;
	int				*signals;
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	str = allocate_memory(s, c);
	if (!str)
		return (NULL);
	while (i < ft_length_word(s, c))
	{
		signals = where_to_start_from(s, c, j);
		str[i] = (char *) malloc (signals[2] * sizeof(char));
		if (!str[i])
			return (NULL);
		fulfill_str(s, str[i], signals);
		j = signals[1];
		i++;
		free(signals);
	}
	return (str);
}
/*int main()
{
	char str[] = "	hello	meme lolo	tiik	";

	char c = ' ';
	char **res = ft_split(str, ' ');
	int	i = 0;

	while (res[i])
	{
		printf("%s \n", res[i]);
		i++;
	}
}*/
