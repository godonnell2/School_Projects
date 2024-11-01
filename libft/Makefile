#VARIABLES
CC = cc #need to have this because will compile with gcc
HDR_FILES = libft.h
CFLAGS = -Wall -Wextra -Werror -g #need this because wont use flags otherwise
SRC = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_is_digit.c ft_strlen.c\
ft_tolower.c ft_toupper.c ft_strncmp.c ft_atoi.c ft_memcpy.c\
ft_strlcpy.c ft_strlcat.c ft_bzero.c ft_memmove.c ft_strchr.c ft_strrchr.c\
ft_strnstr.c ft_memchr.c ft_calloc.c ft_strdup.c ft_memset.c ft_memcmp.c \
ft_isprint.c ft_substr.c ft_strjoin.c
OBJS = $(SRC:.c=.o) #no spaces -spaces pattern rule
LIB = libft.a

#good to learn to use prefix will can remove src/ in SRC then 

#TARGETS/ DEPENDENCIES or PREREQUISITES/ RULES or SHELL COMMANDS
#reluctantly replacing libft.a with <all> because it was heavily suggested
#but i think it is less readable and dumber 

#first listed so its the default. when i say make it will run 
#no need to even say make all though its fine if i do
#the bottom line is our shell commands duh!

all: $(LIB)

#create lib if missing separator error need add colon!!
#need tab or wont work 
$(LIB): $(OBJS)
	ar rcs $(LIB) $^
# $(LIB) = @ $(OBJS) all dependencies =caret ^

#cant use $(SRC)because this is a list need the $< first prequisite/
#dependency to do it one fn at a time 
#will output in src foldercos youre just replacing thats what you told it to do
#cannot run make commands in subfolders need to be in the same folder as makefile
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HDR_FILES)
#dont need this rule as makefile has this INBUILT but i like making it explicit

clean:
	rm -f $(OBJS)


fclean: clean
	rm -f $(LIB)

re: fclean all

#test: all
#	$(CC) $(CFLAGS) $(LIB) && ./a.out

.PHONY: clean fclean all test




