# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygbouri <ygbouri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/26 16:06:10 by momayaz           #+#    #+#              #
#    Updated: 2022/07/16 17:31:44 by ygbouri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCM =	src/utils1.c \
		src/utils2.c \
		src/utils3.c \
		src/utils4.c \
		src/utils5.c \
		src/split.c \
		src/garbage1.c \
		src/garbage2.c \
		src/garbage3.c \
		src/check_syntax1.c \
		src/check_syntax2.c \
		src/env_fct1.c \
		src/env_fct2.c \
		src/parsing1.c \
		src/parsing2.c \
		src/parsing3.c \
		src/files1.c \
		src/files2.c \
		src/split_echo.c \
		src/wild.c \
		src/wildcard.c \
		src/double_join.c \
		src/built_ins1.c \
		src/built_ins2.c \
		src/execution.c\
		src/execution1.c\
		minishell.c\
#src/signals.c \



NAME = minishell

CFLAGS = -Wall -Wextra -Werror -L$(shell brew --prefix readline)/lib -I$(shell brew --prefix readline)/include  -lreadline

all : $(NAME)

$(NAME) : $(SRCM) minishell.h
	$(CC) $(CFLAGS)  $(SRCM) -o $(NAME)

bonus : all

clean :
	rm -f $(NAME)

fclean : clean

re : fclean all

