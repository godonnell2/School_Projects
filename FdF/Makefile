# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/29 23:23:23 by gro-donn          #+#    #+#              #
#    Updated: 2025/01/24 18:06:08 by gro-donn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Iminilibx_macos 
#linker flags
LDFLAGS = -L ./minilibx_macos \
    -l mlx -framework OpenGL -framework Appkit
SRC = main.c parse_map.c keymouse_controls.c prep_data_for_drawing.c
		
	

OBJ = $(SRC:.c=.o)
NAME = fdf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c pushswap.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all