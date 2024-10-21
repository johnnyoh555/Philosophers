CC= cc
CFLAGS= -Wall -Wextra -Werror
SRCS= main_bonus.c atoi_bonus.c parsing_bonus.c thread_bonus.c utils_bonus.c end_seq_bonus.c 
OBJ= $(SRCS:.c=.o)
NAME= philo_bonus

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