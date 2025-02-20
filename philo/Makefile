CC = cc
CFLAGS = -Wall -Wextra -Werror -g 

SRC = main.c \
	utils.c 
   
NAME = philo
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS)  -o $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
