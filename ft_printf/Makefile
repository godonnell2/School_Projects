#Variables

NAME = libftprintf.a
LIBFTNAME = libft.a
LIBFTDIR = ./libft
CC = cc 
CFLAGS = -Wall -Wextra -Werror -g -I ./include  # As
SRC =	\
		ft_printf.c \
		ft_printchar.c \
		ft_printstring.c \
		ft_printlong.c \
		ft_printhex.c \
		ft_printpointer.c 
		
OBJS = $(SRC:.c=.o) #map

#Targets
all: $(NAME)

$(NAME): $(OBJS) $(LIBFTNAME) 
	cp $(LIBFTDIR)/$(LIBFTNAME) . 
	mv $(LIBFTNAME) $@ 
	ar -rs $@ $(OBJS)
#one .a file that contains all the libft files and all the printf files
#mv rename libft.a as libftprintf.a
# rm c because we're basing it on libft.a r adds
# we add the .o files printf to libftprintf.a

$(LIBFTNAME): 
	$(MAKE) -C $(LIBFTDIR) 
# Ensure libft is built -C option in the make command is used to change the 
#directory before executing the makefile.
#compiling our old library

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@ -I .

clean: 
	rm -f $(OBJS) 
	$(MAKE) -C $(LIBFTDIR) clean 

fclean : clean 
	rm -f $(NAME) 
	$(MAKE) -C $(LIBFTDIR) fclean 

re : fclean all

.PHONY : clean fclean all re 

#$(MAKE) is a built-in variable in Makefiles that represents the name of the 
#make program being used. It is particularly useful when you are calling make
#recursively (i.e., when a Makefile calls another Makefile). Using $(MAKE) 
#ensures that the correct version of make is used, which is especially important
 # in environments where multiple versions of make might be installed. 
 #Built-in Variable: $(MAKE) is built into the make utility, and y
 #make -B make verbose command