NAME = philo
CC = cc 
CFLAG = -Wall -Wextra -Werror -fsanitize=thread -g3

SRC = main.c \
	  utils.c \
	  routine.c \
	  init.c \
	  monitoring.c \
	  get_set.c

OBJ = $(SRC:.c=.o)

all:$(NAME)

%.o:%.c philo.h
	$(CC) $(CFLAG) -c $< -o $@

$(NAME):$(OBJ)
	$(CC) $(CFLAG) $(OBJ) -o $(NAME)

clean :
	rm -f $(OBJ)
fclean : clean
	rm -f $(NAME)

re : fclean all