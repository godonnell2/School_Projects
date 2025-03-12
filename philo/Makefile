CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-O3optimisation

SRC = main.c \
	utils.c \
	routine.c \
	die.c \
	eat.c \
	init_checks.c 
   
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
