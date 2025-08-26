# Compiler and flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g

# OS Detection
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
    MLX_DIR    = ./minilibx-linux
    MLX_FLAGS  = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
else ifeq ($(UNAME_S), Darwin)
    MLX_DIR    = ./minilibx_macos
    MLX_FLAGS  = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

# Includes
LIBFT     = ./libft/libft.a
INCLUDES  = -I./ -I./libft -I$(MLX_DIR)
RM        = rm -rf
NAME      = cub3d
OBJ_DIR   = obj

# Sources
SRCS = main.c \
       argument_validation.c \
       color_parsing.c \
       cub3d_parsing.c \
       data_init.c \
       element_parsing.c \
       map_parsing.c \
       parse_free.c \
       parsing_utils.c \
       validate_map.c \
       xpm_to_img.c \
       render/coll_utils.c \
       render/collisions.c \
       render/draw_walls.c \
       render/put_line.c \
       render/raycasting.c \
       render/render_keys.c \
       render/utils.c \
       render/movement.c \
       render/free_render.c

# Object files
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Color output
GREEN = \033[0;32m
YELLOW = \033[1;33m
RESET = \033[0m

# Default target
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@$(MAKE) -C ./libft > /dev/null
	@echo "$(YELLOW)Compiling MLX...$(RESET)"
	@$(MLX_BUILD)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)Build complete!$(RESET)"

# Compile .o files into obj/ folder
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Compiled $<"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@$(MAKE) clean -C ./libft > /dev/null
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "$(YELLOW)Removing executable...$(RESET)"
	@$(MAKE) fclean -C ./libft > /dev/null
	@$(RM) $(NAME)
	@echo "$(GREEN)Clean complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re