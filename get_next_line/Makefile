
NAME = get_next_line.a
CC = cc 
CFLAGS = -Wall -Wextra -Werror -g 
SRC =	\
		get_next_line.c\
		get_next_line_utils.c  

OBJS = $(SRC:.c=.o) 

#Targets
all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

get_next_line.o: get_next_line.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

get_next_line_utils.o: get_next_line_utils.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJS) 

fclean : clean 
	rm -f $(NAME) 
	
re : fclean all

.PHONY : clean fclean all re 

#This rule works well for compiling any .c file into a corresponding .o file. 
#However, it does not explicitly state that each object file depends on the
#header file (get_next_line.h). If you modify the header file, the Makefile
#won't automatically recompile the object files that depend on it unless 
#you specify those dependencies.