# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/19 17:49:00 by ytijani           #+#    #+#              #
#    Updated: 2022/07/21 21:46:43 by ytijani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = builtins/cd.c builtins/echo.c builtins/ft_env.c builtins/ft_export.c builtins/ft_unset.c builtins/pwd.c builtins/ft_exit.c \
exec/ft_memcpy.c exec/ft_split.c exec/ft_strchr.c exec/ft_strlcpy.c exec/get_path.c exec/help_linkedlist.c exec/exec_cmd.c \
parsing/cmd.c parsing/destroy.c parsing/dollar_expansion.c parsing/errors.c parsing/here_doc.c parsing/parsing.c parsing/run_heredoc.c\
parsing/utils.c parsing/utils2.c parsing/utils3.c parsing/utils4.c parsing/get_next_line.c parsing/get_next_line_utils.c \
exec/main.c

CC = cc

# CFLAGS = -Wall -Wextra -Werror

OBJCT = ${SRC:.c=.o}

all : $(NAME)
$(NAME) : $(OBJCT)
	@$(CC)  -lreadline -fsanitize=address -L /Users/ytijani/.brew/opt/readline/lib -I /Users/ytijani/.brew/opt/readline/include $(SRC) -o $(NAME)

clean :
	@rm -f $(OBJCT)

fclean : clean
	@rm -f $(NAME)

re : fclean all