# === Project Name ===
NAME = minishell

# === Directories ===
SRC_DIR     = src
PARSER_DIR  = $(SRC_DIR)/parser
EXEC_DIR    = $(SRC_DIR)/executor
UTILS_DIR   = $(SRC_DIR)/utils
INC_DIR     = include
LIBFT_DIR   = libft

# === Libs ===
LIBFT       = $(LIBFT_DIR)/libft.a
 INCLUDES    = -I$(INC_DIR) -I/usr/include

# === Includes ===

INCLUDES    = -I$(INC_DIR)

# === Files by module ===
PARSER_SRC  = parser_lst.c tokenizer.c expand_env.c expand_arg.c \
              env_vars_init.c list_utils.c token_utils.c free.c error.c \
			  testing.c

EXEC_SRC    = bis1.c bis2.c bis3_cd.c bis_exec_check.c   \
				executor.c \
			split_buff_path.c helper.c helperbis2.c env_arr.c\
			 env_nodes.c path_access.c  \
			 redirects.c heredoc.c

UTILS_SRC   =         # <-- Add utils .c files here

# === Full source list with paths ===
SRC = \
	$(addprefix $(PARSER_DIR)/, $(PARSER_SRC)) \
	$(addprefix $(EXEC_DIR)/, $(EXEC_SRC)) \
	$(addprefix $(UTILS_DIR)/, $(UTILS_SRC)) \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/signals.c

# === Object files ===
OBJS = $(SRC:.c=.o)

# === Compiler flags ===
CC = cc
CFLAGS = -Wall -Wextra -g

# === Build rules ===
all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(LFLAGS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
