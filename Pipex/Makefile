# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/30 21:15:32 by gro-donn          #+#    #+#              #
#    Updated: 2025/01/30 21:15:33 by gro-donn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRC = main.c \
	helper.c \
	helper_split.c \
	helper_new.c \
	helper_new_two.c \
	helper_path.c \
	my_printf.c \
	my_printf2.c

OBJ = $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c pushswap.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
