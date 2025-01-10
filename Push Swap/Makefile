# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/26 00:52:18 by gro-donn          #+#    #+#              #
#    Updated: 2025/01/08 17:18:19 by gro-donn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = gcc 
CFLAGS = -Wall -Wextra -Werror -g -DVERBOSE=1
SRC = 	main.c \
		operations.c \
		operations_two.c \
		operations_three.c \
		stack_creation_change.c \
	  	sorting.c \
	  	sorting_two.c \
	  	sorting_three.c \
	  	sorting_four.c \
	 	check_args.c \
	 	check_args_two.c \
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