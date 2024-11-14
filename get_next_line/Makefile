
NAME = libft_getnextline.a
CC = cc 
CFLAGS = -Wall -Wextra -Werror -g 
SRC =	\
		get_next_line.c\
		get_next_line_utils.c  

OBJS = $(SRC:.c=.o) 

#Targets
all: $(NAME)


%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@ 

clean: 
rm -f $(OBJS) 

fclean : clean 
	rm -f $(NAME) 
	
re : fclean all

.PHONY : clean fclean all re 