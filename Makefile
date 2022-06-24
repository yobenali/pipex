# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yobenali <yobenali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/31 00:05:29 by yobenali          #+#    #+#              #
#    Updated: 2022/06/24 21:53:27 by yobenali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex
B_NAME	=	pipex_bonus
SRC	=	src/ft_calloc.c src/ft_split.c src/ft_strdup.c src/ft_strjoin.c src/ft_strlcpy.c src/ft_strlen.c src/ft_strncmp.c pipex.c \

B_SRCS = src_bs/ft_calloc_bonus.c  src_bs/ft_split_bonus.c src_bs/ft_strdup_bonus.c src_bs/ft_strjoin_bonus.c src_bs/ft_strlcpy_bonus.c src_bs/ft_strlen_bonus.c src_bs/ft_strncmp_bonus.c pipex_bonus.c \

CC 		= cc
FLAGS 	= -Wall -Wextra -Werror
$(NAME) :
	$(CC) $(FLAGS) $(SRC) -o $(NAME)
$(B_NAME) :
	$(CC) $(FLAGS) $(B_SRCS) -o $(B_NAME)
all : $(NAME)
bonus : $(B_NAME)
clean :
	rm -f $(NAME)
	rm -f $(B_NAME)
fclean : clean
	rm -f $(NAME)
	rm -f $(B_NAME)
re : clean fclean all

.PHONY : all clean fclean re
: