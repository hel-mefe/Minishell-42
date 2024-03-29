/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 18:31:44 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/30 15:07:10 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini.h"

//***************************Help_cd*****************************************//
void	help_cd(t_env **env_v, t_env *current_node, t_env *prev, char *name)
{
	prev = *env_v;
	current_node = (*env_v)->next;
	while (current_node != NULL && ft_strcmp(current_node->name, name))
	{
		prev = prev->next;
		current_node = current_node->next;
	}
	if (current_node)
	{
		prev->next = current_node->next;
		free(current_node->name);
		free(current_node->data);
		free(current_node);
	}
	else
			prev->next = NULL;
}

void	remove_name(t_env **env_v, char *name)
{
	t_env	*new;
	t_env	*prev;
	t_env	*current_node;

	current_node = NULL;
	prev = NULL;
	new = NULL;
	if (!ft_strcmp((*env_v)->name, name))
	{
		new = *env_v;
		*env_v = (*env_v)->next;
		free(new);
	}
	else
		help_cd(env_v, current_node, prev, name);
}

//***************************Help_export*******************//
void	print_err(char **av)
{
	char	*res;

	res = NULL;
	res = ft_strjoin(av[1], " : not a valid identifier\n");
	ft_putstr_fd(res, 2);
	free(res);
	g_global.get_nb_status = 1;
}
//**************************LIbft_Function******************//

char	*ft_strtrim(char *s1, char *set)
{
	int	start;
	int	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr (set, s1[start]))
		start++;
	while (end >= 0 && ft_strchr (set, s1[end]))
		end--;
	if (start > end)
		return (ft_strdup(""));
	return (ft_substr(s1, start, end - start + 1));
}

//************Help_Export****************************?/

void	join_strcheckevr(t_env **env_v, char **spl, int i, char **av)
{
	t_env	*new;
	int		len;
	char	*res;

	new = *env_v;
	len = ft_strlen(spl[0]);
	free(spl[0]);
	spl[0] = ft_substr(av[i], 0, len - 1);
	new = search_element(env_v, spl[0]);
	if (new)
	{
		res = new->data;
		new->data = ft_strjoin(new->data, spl[1]);
		if (res)
			free(res);
	}
	else
		add_to_list(env_v, spl);
}
