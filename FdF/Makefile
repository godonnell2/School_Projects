# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/29 23:23:23 by gro-donn          #+#    #+#              #
#    Updated: 2025/01/30 20:50:32 by gro-donn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

#linker flags
# Define OS-specific flags
ifeq ($(shell uname), Darwin)  # macOS
CFLAGS = -Wall -Wextra -Werror -g -Iminilibx_macos 
    LDFLAGS = -L ./minilibx_macos \
              -l mlx -framework OpenGL -framework Appkit
else  # Assume Linux
CFLAGS = -Wall -Wextra -Werror -g -Iminilibx-linux 
    LDFLAGS = -L./minilibx-linux \
              -l mlx_Linux -l X11 -l Xext -l Xrender -l GL -lm
endif

SRC = main.c \
      parse_map.c \
      keymouse_controls.c \
      prep_data_for_drawing.c \
      prep_data_for_drawing_two.c \
      draw.c \
      read_to_buffer.c \
      utils.c \
      utils_two.c \
      utils_three.c \
      error_handling.c 

NAME = fdf
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all