/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-mefe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:12:34 by hel-mefe          #+#    #+#             */
/*   Updated: 2022/07/30 18:12:35 by hel-mefe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define PATH_COLOR "\033[1;36m("
# define INPUT_COLOR ")$\n \033[1;37m🐙 -> ​"
# define ERROR_COLOR "\033[1;33m"
# define WHITE "\033[1m"

# define NONE_AMBIGUOUS -1
# define NONE 0
# define INFILE 1
# define OUTFILE 24
# define COMMAND 3
# define HERE_DOC 4
# define ARGUMENT 5
# define EXPANDED_HERE_DOC 6
# define HERE_DOC_MAX 16
# define BREAKING_POINT -1

# define SYNTAX_ERR_NEAR_INFILE "\033[1;33mminishell_1337: \
syntax error near unexpected token '<'"
# define SYNTAX_ERR_NEAR_OUTFILE "\033[1;33mminishell_1337: \
syntax error near unexpected token '>'"
# define SYNTAX_ERR_NEAR_OUTFILE_APPEND "\033[1;33mminishell_1337: \
syntax error near unexpected token '>>'"
# define SYNTAX_ERR_NEAR_HEREDOC "\033[1;33mminishell_1337: s\
yntax error near unexpected token '<<'"
# define SYNTAX_ERR_NEAR_NEWLINE "\033[1;33mminishell_1337: \
syntax error near unexpected token 'newline'"
# define UNCLOSED_PIPE_ERR "\033[1;33mminishell_1337: \
syntax error pipes are not closed properly"
# define SYNTAX_ERR "\033[1;33mminishell_1337: \
syntax error";
# define MAX_HERE_DOC_EXCEEDED_ERR "\033[1;33mminishell_1337: \
max heredoc limiters have been exceeded"
# define REDIRECTION_ERR "\033[1;33mminishell_1337: \
ambiguous redirect"
# define UNEXPECTED_PIPE_TOKEN_ERR "\033[1;33mminishell_1337: \
unexpected pipe token '|'"
# define AMBIGUOUS_ERR "\033[1;33mminishell_1337: \
ambiguous redirect"
# define SYNTAX_ERR_NEAR_PIPE "\033[1;33mminishell_1337: \
syntax error near unexpected token `|'"

#endif
