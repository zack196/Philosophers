NAME = philo_bonus
CC = cc 
CFLAG = -Wall -Wextra -Werror #-fsanitize=thread -g3

SRC = main_bonus.c \
	  utils_bonus.c \
	  philo_routine_monitor_bonus.c 

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