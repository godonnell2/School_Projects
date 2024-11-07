#VARIABLES
CC = cc #need to have this because will compile with gcc 
CFLAGS = -Wall -Wextra -Werror -g #need this because wont use flags otherwise
SRC = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_strlen.c\
ft_tolower.c ft_toupper.c ft_strncmp.c ft_atoi.c ft_memcpy.c\
ft_strlcpy.c ft_strlcat.c ft_bzero.c ft_memmove.c ft_strchr.c ft_strrchr.c\
ft_strnstr.c ft_memchr.c ft_calloc.c ft_strdup.c ft_memset.c ft_memcmp.c\
ft_isprint.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_putchar_fd.c\
ft_itoa.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strmapi.c \
ft_striteri.c 

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstclear.c \
ft_lstdelone.c ft_lstadd_back.c ft_lstiter.c ft_lstmap.c
NAME = libft.a
OBJS = $(SRC:.c=.o) #no spaces pattern rule 																			
BONUS_OBJS = $(BONUS:.c=.o) #no spaces pattern rule
LIB_SO = libft.so																												
#good to learn to use prefix will can remove src / in SRC then

#TARGETS / DEPENDENCIES or PREREQUISITES / RULES or SHELL COMMANDS
#reluctantly replacing libft.a with < all> because it was heavily suggested
#but i think it is less readable and dumber

#first listed so its the default.when i say make it will run
#no need to even say make all though its fine if i do
#the bottom line is our shell commands duh !

all: $(NAME)

#create lib if missing separator error need add colon !!
#r modify libft.a #insert the objs into libft.a s creates an index
#need tab or wont work
$(NAME): $(OBJS) $(BONUS_OBJS)
	ar rcs $@ $^
#$(LIB) = @$(OBJS) all dependencies = caret ^

#cant use $(SRC) because this is a list need the $ < first prequisite /
#dependency to do it one fn at a time
#will output in src foldercos youre just replacing thats what you told it to do
#cannot run make commands in subfolders need to be in the same folder as makefile
%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@ -I .
#dont need this rule as makefile has this INBUILT but i like making it explicit 
#-I includes my libft.h

bonus: $(NAME)
	echo yes

so: $(OBJS) $(BONUS_OBJS)
	gcc -shared -o $(LIB_SO) $(OBJS) $(BONUS_OBJS) -fPIC

clean: 
	rm -f $(OBJS) $(BONUS_OBJS)

#fclean : clean
#	rm -f $(NAME) 

fclean : clean
	rm -f $(NAME) #$(LIB_SO)

re : fclean all

#test : all
#$(CC) $(CFLAGS) $(LIB) &&./ a.out

.PHONY : clean fclean all bonus re
