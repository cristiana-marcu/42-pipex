# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/25 15:00:27 by RAMON             #+#    #+#              #
#    Updated: 2021/08/31 14:40:50 by cmarcu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = pipex.c ft_split.c ft_strchr.c ft_strjoin.c ft_strnstr.c ft_substr.c \
	ft_strlen.c
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Werror -Wextra -Wall -g3 -fsanitize=address

RM = rm -f
NAME = pipex

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
