/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 20:00:35 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/21 15:16:22 by ytijani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <fcntl.h>
# include <errno.h>
# include "structures.h"
# include "macros.h"

# define HERE_DOC_NAME "Minishell-42-heredoc"

/*** END DIAL MAIN STRUCTURE ***/

void		ft_putstr(char *s);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strjoin_free(char *s1, char *s2);
char		*ft_strdup(const char *s);
char		*slice(char *s, size_t a, size_t b);
char		*get_normal_string(char *s, t_cmd *cmd);
void		assign_string(char *s, int place, t_data *data, t_cmd *cmd);
char		*get_singly_string(char *s, t_cmd *cmd);
char		*get_doubly_string(char *s, t_cmd *cmd);
size_t		get_string(char *s, int place, t_data *data, t_cmd *cmd);
size_t		ft_strlen(const char *s);

int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(char *s1, char *s2, size_t n);
int			ft_isalpha(char c);
int			ft_isdigit(char c);
int			ft_isalnum(char c);
int			is_token(char c);
int			is_space(char c);
char		**get_args(t_cmd *cmd);

int			in_string(char *s, char c);
char		*remove_chars(char *s, char *r);
char		*remove_char(char *s, char c);
char		*remove_quotes(char *s);

t_queue		*new_queue_node(char *s);
t_queue		*get_last(t_queue *head);
void		push_back(t_queue **head, t_queue *new);
size_t		get_heredoc(char *s, t_data *data, t_cmd *cmd);
size_t		get_queue_size(t_queue *head);
t_cmd		*get_command_by_id(t_cmd *head, int id);

t_dollar	*new_dollar(char *var, char *val);
t_dollar	*get_last_dollar(t_dollar *head);
void		push_back_dollar(t_dollar **head, t_dollar *new);
char		*get_dollar_val(char *var, char **env, t_env *main_env);

int			is_dollar_char_valid(char c);
char		*get_dollar(char *s);
t_dollar	*get_all_dollars(char *s, char **env, t_env *main_env);
int			is_dollar_valid(char *s);
char		*expand_string(t_dollar *dollars, char **env, int *place, char *s);
void		mark_builtins(t_cmd *head);
int			is_builtin(char *cmd);

int			get_commands_size(t_cmd *head);
t_cmd   	*get_commands(t_data *data, char *s);
size_t		get_quote_end(char *s, char c);
void		push_command(t_cmd **head, t_cmd *new);
t_cmd		*new_command(t_cmd *head);
t_cmd		*get_last_command(t_cmd *head);

void		run_heredoc(t_data *data, t_queue *limiters, t_cmd *cmds);
void		init_env(t_env **env_v, char **env);

void        prepare_data(t_data *data);
void		destory_data(t_data **data);
void		free_commands(t_cmd *cmd);
void		free_dollars(t_dollar *head);
void		free_double_char_arr(char **arr);
void		free_double_int_arr(int **arr, int size);
void		free_queue(t_queue *head);

char		*ft_itoa(int n);
char		*get_next_line(int fd);
void		get_err(char *err, int is_exit);
void    	is_there_any_alpha(t_data *data, char *s, int is_heredoc);
int     	is_there_char(char *s);
void		catch_syntax_err(t_data *data, char *s);
int 		search_for_char(char *s, char c, char end);
void        get_pipe_err(t_data *data, char *s, int i);

void	put_infile(t_cmd *cmd, char *infile_name);
void	put_outfile(t_cmd *cmd, char *outfile_name);
void	put_heredoc(t_data *data, t_cmd *cmd, int place, char *limiter);
void	put_argument(t_cmd *cmd, char *argument);
void	put_command(t_cmd *cmd, char *cmd_name);

/***************handle_signals****************/
void		handle_signals(void);
void		handel_sigint(int sig);
#endif
