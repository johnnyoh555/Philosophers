CC= cc
CFLAGS= -Wall -Wextra -Werror
SRCS= main.c atoi.c parsing.c thread.c eating.c time.c utils.c
OBJ= $(SRCS:.c=.o)
NAME= philo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -pthread -o $(NAME) 

$(OBJ): $(SRCS)
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re