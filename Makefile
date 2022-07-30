# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytijani <ytijani@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/19 17:49:00 by ytijani           #+#    #+#              #
#    Updated: 2022/07/30 17:09:45 by ytijani          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = builtins/cd.c builtins/echo.c builtins/ft_env.c builtins/ft_export.c builtins/ft_unset.c builtins/pwd.c builtins/ft_exit.c builtins/utils.c builtins/utils2.c \
exec/ft_memcpy.c exec/ft_split.c exec/ft_strchr.c exec/ft_strlcpy.c exec/get_path.c exec/help_linkedlist.c exec/exec_cmd.c exec/utils.c  exec/handle_signals.c exec/ft_atoi.c \
parsing/data_structures/commands.c parsing/data_structures/dollars.c parsing/data_structures/heredocs.c parsing/data_structures/queue.c \
parsing/functions/builtins.c parsing/functions/compare.c parsing/functions/conditions.c parsing/functions/conditions2.c parsing/functions/itoa.c parsing/functions/join_strings.c \
parsing/functions/quotes.c parsing/functions/search.c parsing/functions/strings.c parsing/variables/expansion.c parsing/variables/get_dollars.c parsing/buckets.c parsing/help_destroy.c\
get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
parsing/cmd.c parsing/destroy.c parsing/errors.c parsing/expressions1.c parsing/expressions2.c parsing/here_doc.c parsing/parsing.c parsing/redirect.c parsing/run_heredoc.c \
exec/main.c parsing/prompt.c parsing/variables/expansion1.c

CC = gcc

LOGO = "\
\033[1;36m    __  ___ ____ _   __ ____ _____  __  __ ______ __     __       ___ _____ _____ _____\n\
\033[2;36m   /  |/  //  _// | / //  _// ___/ / / / // ____// /    / /      <  /|__  /|__  //__  /\n\
\033[2;36m  / /|_/ / / / /  |/ / / /  \__ \ / /_/ // __/  / /    / /       / /  /_ <  /_ <   / / \n\
\033[0;36m / /  / /_/ / / /|  /_/ /  ___/ // __  // /___ / /___ / /___    / / ___/ /___/ /  / /  \n\
\033[0;36m/_/  /_//___//_/ |_//___/ /____//_/ /_//_____//_____//_____/   /_/ /____//____/  /_/   \n\
                                                                                       \n\
\t\t\t\t\t\t\t \033[1;36mmade by hel-mefe and ytijani\n"

SUCCESS = "\033[1;32m \n\t\t\t 👽 MINISHELL HAVE BEEN CREATED SUCCESSFULLY! 👽  \n\n"

CFLAGS = -Wall -Wextra -Werror

OBJCT = ${SRC:.c=.o}

$(NAME): $(OBJCT)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)
$(NAME) : $(OBJCT)
	@$(CC)  $(CFALGS) -lreadline -L /Users/ytijani/.brew/opt/readline/lib -I /Users/ytijani/.brew/opt/readline/include $(SRC) -o $(NAME)
	@printf $(SUCCESS)
	@printf $(LOGO)
clean :
	@rm -f $(OBJCT)

fclean : clean
	@rm -f $(NAME)

re : fclean all