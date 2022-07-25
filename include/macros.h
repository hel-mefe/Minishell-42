#ifndef MACROS_H
# define MACROS_H

# define RED 

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

# define SYNTAX_ERR_NEAR_INFILE "minishell_1337: syntax error near unexpected token '<'"
# define SYNTAX_ERR_NEAR_OUTFILE "minishell_1337: syntax error near unexpected token '>'"
# define SYNTAX_ERR_NEAR_OUTFILE_APPEND "minishell_1337: ssyntax error near unexpected token '>>'"
# define SYNTAX_ERR_NEAR_HEREDOC "minishell_1337: syntax error near unexpected token '<<'"
# define SYNTAX_ERR_NEAR_NEWLINE "minishell_1337: syntax error near unexpected token 'newline'"
# define UNCLOSED_PIPE_ERR "minishell_1337: syntax error pipes are not closed properly"
# define SYNTAX_ERR "minishell_1337: syntax error";
# define MAX_HERE_DOC_EXCEEDED_ERR "minishell_1337: max heredoc limiters have been exceeded"
# define REDIRECTION_ERR "minishell_1337: ambiguous redirect"
# define UNEXPECTED_PIPE_TOKEN_ERR "minishell_1337: unexpected pipe token '|'"
# define AMBIGUOUS_ERR "minishell_1337: ambiguous redirect"
# define SYNTAX_ERR_NEAR_PIPE "minishell_1337: syntax error near unexpected token `|'"

# endif