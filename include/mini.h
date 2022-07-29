/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:21:55 by marvin            #+#    #+#             */
/*   Updated: 2022/07/20 20:00:09 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# include "../include/parsing.h"

/*************builtins*******************/
void	ft_echo(t_env **env_v, char **av, int fd);
void	ft_cd(t_env **env_v, char **av);
void	ft_export(t_env **env_v, char **av);
void	ft_pwd(t_env **env_v);
void	ft_env(t_env **env_v, char **av);
void    ft_exit(char **av);
/**************Help->builtins*******************/
void	init_env(t_env **env_v, char **env);
void	ft_sort(t_env **env_v);
void	run_builtin(t_env **env_v, char **av, t_cmd *cmd);
void	print_export(t_env **env_v);
void	ft_unset(t_env **env_v, char **name);
void	remove_name(t_env **env_v, char *name);
void	help_cd(t_env **env_v, t_env *current_node, t_env *prev, char *name);
void	help_runbuilt(t_cmd *cmd, t_env **env, int res, char **str);
/*************help_linked_list*******************/
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstnew(char *name, char *data);
int		ft_lstsize(t_env *lst);
t_env	*search_element(t_env **env_v, char *name);
void	add_to_list(t_env **env_v, char **spl);
/*************Function*******************/
char	**ft_split(char const *s, char c);
int		ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
void	ft_putstr_fd(char *s, int fd);
/***************handle_signals****************/
void	handle_signals(int i);
void	handel_sigint(int sig);
void	handle_sig(int sig);
void	handel_sigint1(int sig);
void	handle_sigquit(int sig);
/***************Check_Error****************/
void	ft_error1(int code, char *str);
void	print_err(char **av);
void	check_err(t_cmd *cmd);
/****************OTHERS********************/
char	*get_command(t_env	**path, char *cmd);
t_data	*get_data(t_env	**env);
t_data	*parse_line(char *s, char **env, t_env *main_env);
void	free_queue(t_queue *head);
void	print_commands(t_cmd *head);
t_env	*search_element(t_env **env_v, char *name);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	run_cmd(t_env **env, t_data *data, t_cmd *cmd);
int		ft_lstsize(t_env *lst);
void	close_pipe(int **pipes, int a, int b, int n);
void	print_heredoc(t_queue *head);
void	ft_putstr_fd(char *s, int fd);
t_env	*add_env(char *name);
int		get_myid(t_env **env_v, char *name);
void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);
void	free_double_char_arr(char **arr);
void	run_cmd(t_env **env, t_data *data, t_cmd *cmd);
void	ever(char **cmd, t_env **env_v, char **env);
void    rl_replace_line(const char *, int);
char	*ft_strjoins(char *save, char *buffer);
char	*ft_strtrim(char *s1, char *set);
void	check_cmd(t_env *env_v, char *s, char	**env, t_data *data);
void	get_line(int history, char *s);
void	join_strcheckevr(t_env **env_v, char **spl, int i, char **av);
int	    check_export(char *str);
#endif
