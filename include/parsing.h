/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 20:00:35 by ytijani           #+#    #+#             */
/*   Updated: 2022/07/20 21:26:30 by ytijani          ###   ########.fr       */
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

# define SYNTAX_ERR "SYNTAX ERROR!";
# define MAX_HERE_DOC_EXCEEDED_ERR "MAX HEREDOC LIMITERS HAVE BEEN EXCEEDED!"
# define REDIRECTION_ERR "Unambiguous redirection error!"
# define UNEXPECTED_PIPE_TOKEN_ERR "Minishell_1337: unexpected pipe token '|'"
# define AMBIGUOUS_ERR "Minishell_1337: ambiguous redirect"
# define SYNTAX_ERR_NEAR_PIPE "Minishell_1337: syntax error near unexpected token `|'"

# define NONE_AMBIGUOUS -1
# define NONE 0
# define INFILE 1
# define OUTFILE 2
# define COMMAND 3
# define HERE_DOC 4
# define ARGUMENT 5
# define EXPANDED_HERE_DOC 6

# define HERE_DOC_MAX 16

# define BREAKING_POINT -1
# define HERE_DOC_NAME "Minishell-42-heredoc"
/***
 * Had Queue howa fin kaytstoraw limiters dial heredoc
 *  START OF THE QUEUE
 * ***/
typedef struct s_global
{
	int			get_nb_status;
	int			get_nb;
	int			new;
}	t_global;

t_global g_global;

typedef struct s_env
{
	char			*name;
	char			*data;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct queue
{
	char			*s;
	int				ex;
	int				cmd_id;
	struct queue	*next;
}	t_queue;

typedef struct heredoc
{
	t_queue			*limiters;
	struct heredoc	*next;
}	t_heredoc;

typedef struct dollar // only valid dollar names
{
	char			*var;
	char			*val;
	struct dollar	*next;
}	t_dollar;

typedef struct cmd
{
	char		*line;
	char		*cmd_name;
	char		*infile;
	char		*outfile;
	char		**main_args;
	char		**env;
	char		*syntax;
	int			cmd_id;
	int			error;
	int			outfile_mode;
	int			status;
	int			is_builtin;
	int			has_heredoc;
	int			heredoc_file;
	int			heredoc_pipe[2];
	int			write_end;
	int			read_end;
	t_queue		*args;
	t_queue		*heredoc;
	t_dollar	*vars;
	struct cmd	*next;
	struct cmd	*prev;
}	t_cmd;

/*** END OF STRUCTURE DIAL COMMAND ***/

/*** MAIN STRUCTURE DIAL PARSING LI FIHA DATA KAMLA ***/

typedef struct s_data
{
	t_cmd	*commands;
	t_queue	*heredoc;
	int		n_cmds;
	int		**pipes;
	int		is_syntax_valid;
	char	*err;
	char	**env;
	t_env	*main_env;
}	t_data;

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

void		destory_data(t_data **data);
void		free_commands(t_cmd *cmd);
void		free_dollars(t_dollar *head);
void		free_double_char_arr(char **arr);
void		free_double_int_arr(int **arr, int size);
void		free_queue(t_queue *head);

char		*ft_itoa(int n);
char		*get_next_line(int fd);
void		get_err(char *err, int is_exit);
void    is_there_any_alpha(t_data *data, char *s, int is_heredoc);
/***************handle_signals****************/
void		handle_signals(void);
void		handel_sigint(int sig);
#endif
