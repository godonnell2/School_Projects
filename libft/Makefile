#VARIABLES
CC = cc #need to have this because will compile with gcc
CFLAGS = -Wall -Wextra -Werror -g #need this because wont use flags otherwise
SRC = src/ft_isalnum.c src/ft_isalpha.c src/ft_isascii.c src/ft_is_digit.c \
src/ft_strlen.c src/ft_tolower.c src/ft_toupper.c src/ft_strncmp.c src/ft_atoi.c \
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
	ar rcs $@ $^
# $(LIB) = @ $(OBJS) all dependencies =caret ^

#cant use $(SRC)because this is a list need the $< first prequisite/
#dependency to do it one fn at a time 
#will output in src foldercos youre just replacing thats what you told it to do
#cannot run make commands in subfolders need to be in the same folder as makefile
# %.o: %.c
# 	cc -Wall -Werror -Wextra -c $< -o $@
#dont need this rule as makefile has this INBUILT 

clean:
	rm -f $(OBJS)


fclean: clean
	rm -f $(LIB)

re: fclean all

.PHONY: clean fclean all 




