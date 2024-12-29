# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/26 00:52:18 by gro-donn          #+#    #+#              #
#    Updated: 2024/12/29 08:34:45 by gro-donn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c \
 operations.c \
operations_two.c \
	  operations_three.c \
		stack_creation_change.c \
	  sorting.c \
	  sorting_two.c \
	  sorting_three.c \
	  sorting_four.c \
	 check_args.c \
	  helper_functions.c \
	  helper_functions_two.c 

OBJ = $(SRC:.c=.o)
NAME = push_swap

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