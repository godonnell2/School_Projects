# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/29 23:23:23 by gro-donn          #+#    #+#              #
#    Updated: 2025/01/25 18:01:01 by gro-donn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Iminilibx_macos 
#linker flags
# Define OS-specific flags
ifeq ($(shell uname), Darwin)  # macOS
    LDFLAGS = -L ./minilibx_macos \
              -l mlx -framework OpenGL -framework Appkit
else  # Assume Linux
    LDFLAGS = -L ./minilibx_macos \
              -l mlx -l X11 -l Xext -l Xrender -l GL -lm
endif

SRC = main.c \
      parse_map.c \
      keymouse_controls.c \
      prep_data_for_drawing.c \
      prep_data_for_drawing_two.c \
      draw.c \
      read_to_buffer.c \
      utils.c

OBJ = $(SRC:.c=.o)
NAME = fdf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all