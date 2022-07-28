#ifndef MACROS_H
# define MACROS_H

# define PATH_COLOR "\033[1;36m"
// # define INPUT_COLOR "\033[1;32m"
# define INPUT_COLOR "\033[1;37m"
# define ERROR_COLOR "\033[1;33m"
# define WHITE "\033[1m"

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

# define SYNTAX_ERR_NEAR_INFILE ERROR_COLOR"minishell_1337: syntax error near unexpected token '<'"
# define SYNTAX_ERR_NEAR_OUTFILE ERROR_COLOR"minishell_1337: syntax error near unexpected token '>'"
# define SYNTAX_ERR_NEAR_OUTFILE_APPEND ERROR_COLOR"minishell_1337: ssyntax error near unexpected token '>>'"
# define SYNTAX_ERR_NEAR_HEREDOC ERROR_COLOR"minishell_1337: syntax error near unexpected token '<<'"
# define SYNTAX_ERR_NEAR_NEWLINE ERROR_COLOR"minishell_1337: syntax error near unexpected token 'newline'"
# define UNCLOSED_PIPE_ERR ERROR_COLOR"minishell_1337: syntax error pipes are not closed properly"
# define SYNTAX_ERR ERROR_COLOR"minishell_1337: syntax error";
# define MAX_HERE_DOC_EXCEEDED_ERR ERROR_COLOR"minishell_1337: max heredoc limiters have been exceeded"
# define REDIRECTION_ERR ERROR_COLOR"minishell_1337: ambiguous redirect"
# define UNEXPECTED_PIPE_TOKEN_ERR ERROR_COLOR"minishell_1337: unexpected pipe token '|'"
# define AMBIGUOUS_ERR ERROR_COLOR"minishell_1337: ambiguous redirect"
# define SYNTAX_ERR_NEAR_PIPE ERROR_COLOR"minishell_1337: syntax error near unexpected token `|'"

# endif
