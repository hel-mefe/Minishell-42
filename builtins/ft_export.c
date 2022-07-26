/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:26:28 by marvin            #+#    #+#             */
/*   Updated: 2022/07/25 20:36:13 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

void	ft_sort(t_env **env_v)
{
	t_env	*tmp;
	int		size;
	char	*swap;

	size = ft_lstsize(*env_v);
	while (size)
	{
		tmp = (*env_v);
		while (tmp->next != NULL)
		{
			if (ft_strcmp(tmp->name, tmp->next->name) > 0)
			{
				swap = tmp->name;
				tmp->name = tmp->next->name;
				tmp->next->name = swap;
				swap = tmp->data;
				tmp->data = tmp->next->data;
				tmp->next->data = swap;
			}
			tmp = tmp->next;
		}
		size--;
	}
}

void	print_export(t_env **env_v)
{
	t_env	*new;

	ft_sort(env_v);
	new = *env_v;
	while (new)
	{
		printf("declare -x %s", new->name);
		if (new->data != NULL)
		{
			printf("=\"");
			printf("%s", new->data);
			printf("\"");
		}
		printf("\n");
		new = new->next;
	}
}

void	check_evr(t_env **env_v, char **spl, char **av, int i)
{
	t_env	*new;

	new = *env_v;
	if (av[i][ft_strlen(spl[0]) - 1] != '+')
	{
		new = search_element(env_v, spl[0]);
		if (new != NULL)
		{
			free(new->data);
			new->data = spl[1];
		}
		else
			add_to_list(env_v, spl);
	}
	else if (av[i][ft_strlen(spl[0]) - 1] == '+')
	{
		spl[0] = ft_substr(av[i], 0, ft_strlen(spl[0]) - 1);
		new = search_element(env_v, spl[0]);
		if (new)
			new->data = ft_strjoin(new->data, spl[1]);
		else
			add_to_list(env_v, spl);
	}
}

void	help_export(t_env **env_v, char *sig, char **av, int i)
{
	char	*spl[2];
	int		len;
	int		len1;

	len = ft_strlen(av[i]);
	len1 = ft_strlen(av[i]);
	if (sig)
	{
		spl[1] = ft_strdup(sig + 1);
		spl[0] = ft_substr(av[i], 0, ((len - 1) - ft_strlen(spl[1])));
		if (spl[1] != NULL && spl[0] != NULL)
			check_evr(env_v, spl, av, i);
	}
	else
	{
		if (search_element(env_v, av[i]) == NULL)
		{
			spl[1] = NULL;
			spl[0] = ft_substr(av[i], 0, (len - ft_strlen(spl[1])));
			check_evr(env_v, spl, av, 0);
			free(spl[0]);
		}
	}
}

void	ft_export(t_env **env_v, char **av)
{
	int		i;
	char	*sig;
	char	*res;
	t_env	*new;

	i = 1;
	if (av[i] == '\0')
		print_export(env_v);
	while (av[i])
	{
		g_global.get_nb_status = 0;
		sig = strstr(av[i], "=");
		if (!av[i][ft_strlen(sig)] ||
			(!ft_isalpha(av[i][0]) && av[i][0] != '_')
				|| check_oper(av))
		{
			res = ft_strjoin(av[i], " : not a valid identifier\n");
			ft_putstr_fd(res, 2);
			free(res);
			g_global.get_nb_status = 1;
		}
		else
			help_export(env_v, sig, av, i);
		i++;
	}
}
