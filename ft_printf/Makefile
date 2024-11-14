#Variables

NAME = libftprintf.a
CC = cc 
CFLAGS = -Wall -Wextra -Werror -g
SRC =	\
		ft_printf.c \
		ft_printchar.c \
		ft_printstring.c \
		ft_printlong.c \
		ft_printhex.c \
		ft_printptr.c \
		libft/ft_putchar_fd.c \
		libft/ft_strchr.c \
		libft/ft_strlen.c \
		libft/ft_putstr_fd.c
		
OBJS = $(SRC:.c=.o) #map

#Targets
all: $(NAME)

$(NAME): $(OBJS)
	ar -crs $@ $(OBJS)


%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJS) 

fclean : clean 
	rm -f $(NAME) 

re : fclean all

.PHONY : clean fclean all re

#$(MAKE) is a built-in variable in Makefiles that represents the name of the 
#make program being used. It is particularly useful when you are calling make
#recursively (i.e., when a Makefile calls another Makefile). Using $(MAKE) 
#ensures that the correct version of make is used, which is especially important
 # in environments where multiple versions of make might be installed. 
 #Built-in Variable: $(MAKE) is built into the make utility, and y
 #make -B make verbose command