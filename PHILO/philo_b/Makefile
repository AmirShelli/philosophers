NAME = philo_bonus
BONUS = philo

SRCS =  $(shell find . -type f -name "*.c")
BONUS_SRCS =  $(shell find . -type f -name "*.c")

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

HEADER = $(wildcard ./inc/*.h)
HEADER_BONUS = $(wildcard ./inc/*.h)

CC = gcc -Wall -Werror -Wextra

$(NAME): $(OBJS) $(HEADER)
	@$(CC) -pthread -I ./inc $(OBJS) -o $(NAME)

bonus: $(BONUS_OBJS) $(HEADER_BONUS)
	@$(CC) -pthread  -I ./inc $(BONUS_OBJS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $< -c -o $@

clean:
	@rm -rf $(shell find . -type f -name "*.o")

fclean : clean
	@rm -rf $(NAME)
	@rm -rf $(BONUS)

re : fclean all

.PHONY: all libft clean fclean re