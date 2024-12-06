# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dde-carv <dde-carv@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/23 10:20:42 by dde-carv          #+#    #+#              #
#    Updated: 2024/11/21 12:11:37 by dde-carv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex
NAME_B	=	pipex_bonus

LIBFT	=	./libft/libft.a
INC		=	inc/
SRC_DIR	=	src/
OBJ_DIR	=	obj/
SRCB_DIR	=	src_b/
OBJB_DIR	=	obj_b/

CC	=	@cc
CFLAGS	=	-Wall -Werror -Wextra -g -I
RM	=	@rm -f

PPX_UTILS_DIR	=	$(SRC_DIR)pipex_utils/path_utils.c \
					$(SRC_DIR)pipex_utils/exit.c \
					$(SRC_DIR)pipex_utils/family.c \

MAIN_PPX_DIR	=	$(SRC_DIR)main_ppx/main.c

BONUS_DIR		=	$(SRCB_DIR)bonus_ppx/here_doc.c \
					$(SRCB_DIR)bonus_ppx/main.c \

SRCS	=	$(PPX_UTILS_DIR) $(MAIN_PPX_DIR)
SRCS_B	=	$(PPX_UTILS_DIR) $(BONUS_DIR)

OBJS	=	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
OBJS_B	=	$(patsubst $(SRCB_DIR)%/*.c,$(OBJB_DIR)%/*.o,$(SRCS_B))

all:	$(NAME)

$(NAME):	$(OBJS) $(LIBFT)
		@echo "\33[1;32mMake .o and executable.\033[0m"
		@$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIBFT) -o $(NAME)

$(NAME_B):	$(OBJS_B) $(LIBFT)
		@echo "\33[1;32mMake .o and executable.\033[0m"
		@$(CC) $(CFLAGS) $(INC) $(OBJS_B) $(LIBFT) -o $(NAME_B)

$(LIBFT):
		@make -s -C ./libft

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(INC) -c $< -o $@

bonus:		$(NAME_B)

clean:
		$(RM) -r $(OBJ_DIR)
		@make -s clean -C ./libft
		@echo "\33[1;31mClean .o files.\033[0m"

fclean:		clean
		$(RM) $(NAME)
		$(RM) $(NAME_B)
		@make -s fclean -C ./libft
		@echo "\33[1;31mClean executable/s.\033[0m"

re:		fclean all

.PHONY:		bonus clean fclean re
