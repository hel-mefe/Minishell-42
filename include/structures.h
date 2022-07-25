#ifndef STRUCTURES_H
# define STRUCTURES_H
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

#endif